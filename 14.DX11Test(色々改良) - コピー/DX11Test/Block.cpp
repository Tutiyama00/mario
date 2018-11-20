#include"Block.h"
#include"Player.h"
#include"Flag.h"
#include"Enum.h"
#include"Enemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="size">サイズ</param>
Block::Block(Vector3 pos, Vector2 size) : Square::Square(pos, size){}

void Block::CheckPlayer(Player* pPlayer)
{
	if (CollisionCheck(pPlayer))
	{
		//プレイヤーのインプットフラグの取得
		InputFlag playerInput = pPlayer->GetInputFlag();

		//プレイヤーが右に進もうとしているかどうか
		if (playerInput.Check(InputFlagCode::INPUT_RIGHT))
		{
			//このプレイヤーがこのブロックの左側に衝突しているか
			if (LeftCheck(pPlayer))
			{
				//もしそうなら右に進めなくする
				playerInput.ReSet(InputFlagCode::INPUT_RIGHT);
				pPlayer->SetNowWalkSpeed(0.0f);
			}
		}

		//プレイヤーが左に進もうとしているかどうか
		if (playerInput.Check(InputFlagCode::INPUT_LEFT))
		{
			//このプレイヤーがこのブロックの右側に衝突しているか
			if (RightCheck(pPlayer))
			{
				//もしそうなら左に進めなくする
				playerInput.ReSet(InputFlagCode::INPUT_LEFT);
				pPlayer->SetNowWalkSpeed(0.0f);
			}
		}

		//プレイヤーがジャンプ中かどうか
		if (pPlayer->GetMoveObjState() == MoveObjState::JUMP)
		{
			if (DownCheck(pPlayer))
			{
				//もしそうならステートをFALLに変える
				pPlayer->SetMoveObjState(MoveObjState::FALL);
				pPlayer->SetJumpFlag(false);

				return;
			}
		}

		//プレイヤーがFALL中かどうか
		if (pPlayer->GetMoveObjState() == MoveObjState::FALL || pPlayer->GetMoveObjState() == MoveObjState::CHECK_GROUND)
		{
			if (UpCheck(pPlayer))
			{
				//もしそうならステートを接地中に変える
				pPlayer->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		//更新後のインプットフラグを同期
		pPlayer->SetInputFlag(playerInput);
	}
}

void Block::CheckEnemy(Enemy* pEnemy)
{
	if (CollisionCheck(pEnemy))
	{
		//エネミーのインプットフラグの取得
		InputFlag enemyInput = pEnemy->GetInputFlag();

		//プレイヤーが右に進もうとしているかどうか
		if (enemyInput.Check(InputFlagCode::INPUT_RIGHT))
		{
			//このプレイヤーがこのブロックの左側に衝突しているか
			if (LeftCheck(pEnemy))
			{
				//もしそうなら左に進ませる
				enemyInput.ReSet(InputFlagCode::INPUT_RIGHT);
				enemyInput.Set(InputFlagCode::INPUT_LEFT);
			}
		}

		//プレイヤーが左に進もうとしているかどうか
		if (enemyInput.Check(InputFlagCode::INPUT_LEFT))
		{
			//このプレイヤーがこのブロックの右側に衝突しているか
			if (RightCheck(pEnemy))
			{
				//もしそうなら右に進ませる
				enemyInput.ReSet(InputFlagCode::INPUT_LEFT);
				enemyInput.Set(InputFlagCode::INPUT_RIGHT);
			}
		}

		//プレイヤーがFALL中かどうか
		if (pEnemy->GetMoveObjState() == MoveObjState::FALL || pEnemy->GetMoveObjState() == MoveObjState::CHECK_GROUND)
		{
			if (UpCheck(pEnemy))
			{
				//もしそうならステートを接地中に変える
				pEnemy->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		//更新後のインプットフラグを同期
		pEnemy->SetInputFlag(enemyInput);
	}
}

bool Block::LeftCheck(Square* pSquare)
{
	//プレイヤーがこのブロックの左側にあるか
	if (pSquare->GetxPos() <= m_xPos)
	{
		//プレイヤーの右上か右下の頂点がこのブロックの左上、左下の間にあるか
		if (pSquare->m_pVertexArray[3].pos[1] - m_Threshold <= m_pVertexArray[0].pos[1] && pSquare->m_pVertexArray[3].pos[1] - m_Threshold >= m_pVertexArray[2].pos[1])
		{
			return true;
		}
		else if (pSquare->m_pVertexArray[1].pos[1] + m_Threshold <= m_pVertexArray[0].pos[1] && pSquare->m_pVertexArray[1].pos[1] + m_Threshold >= m_pVertexArray[2].pos[1])
		{
			return true;
		}
	}

	return false;
}

bool Block::RightCheck(Square* pSquare)
{
	//プレイヤーがこのブロックの右側にあるか
	if (pSquare->GetxPos() >= m_xPos)
	{
		//プレイヤーの左上か左下の頂点がこのブロックの右上、右下の間にあるか
		if (pSquare->m_pVertexArray[0].pos[1] - m_Threshold <= m_pVertexArray[3].pos[1] && pSquare->m_pVertexArray[3].pos[1] - m_Threshold >= m_pVertexArray[1].pos[1])
		{
			return true;
		}
		else if (pSquare->m_pVertexArray[2].pos[1] + m_Threshold <= m_pVertexArray[3].pos[1] && pSquare->m_pVertexArray[1].pos[1] + m_Threshold >= m_pVertexArray[1].pos[1])
		{
			return true;
		}
	}

	return false;
}

bool Block::DownCheck(Square* pSquare)
{
	//プレイヤーがこのブロックの下にあるか
	if (pSquare->GetyPos() <= m_yPos)
	{
		//プレイヤーの左上か右上の頂点がこのブロックの左下、右下の間にあるか
		if (pSquare->m_pVertexArray[0].pos[0] + m_Threshold >= m_pVertexArray[2].pos[0] && pSquare->m_pVertexArray[0].pos[0] + m_Threshold <= m_pVertexArray[1].pos[0])
		{
			return true;
		}
		else if (pSquare->m_pVertexArray[3].pos[0] - m_Threshold >= m_pVertexArray[2].pos[0] && pSquare->m_pVertexArray[3].pos[0] - m_Threshold <= m_pVertexArray[1].pos[0])
		{
			return true;
		}
	}

	return false;
}

bool Block::UpCheck(Square* pSquare)
{
	//プレイヤーがこのブロックの上にあるか
	if (pSquare->GetyPos() >= m_yPos)
	{
		//プレイヤーの左下か右下の頂点がこのブロックの左上、右上の間にあるか
		if (pSquare->m_pVertexArray[2].pos[0] + m_Threshold >= m_pVertexArray[0].pos[0] && pSquare->m_pVertexArray[2].pos[0] + m_Threshold <= m_pVertexArray[3].pos[0])
		{
			return true;
		}
		else if (pSquare->m_pVertexArray[1].pos[0] - m_Threshold >= m_pVertexArray[0].pos[0] && pSquare->m_pVertexArray[1].pos[0] - m_Threshold <= m_pVertexArray[3].pos[0])
		{
			return true;
		}
	}

	return false;
}