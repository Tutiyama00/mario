#include"Block.h"
#include"Player.h"
#include"Flag.h"
#include"Enum.h"
#include"Enemy.h"


/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/


Block::Block(Vector3 pos, Vector2 size) : NotPlayer(pos, size)
{
	m_ColAdjustedValue = 0.01f;
}


/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  NotPlayer  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// プレイヤーのチェック
/// </summary>
/// <param name="pPlayer">対象のプレイヤーのポインタ</param>
void Block::CheckPlayer(Player* pPlayer)
{
	if (!pPlayer->GetLivibgFlag()) { return; }

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
				/*プレイヤーをこのブロックの左X座標に移動*/
				float xAmount = m_pVertexArray[0].pos.x - pPlayer->m_pVertexArray[1].pos.x;
				pPlayer->VertexMove(xAmount, 0);
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
				/*プレイヤーをこのブロックの右X座標に移動*/
				float xAmount = m_pVertexArray[1].pos.x - pPlayer->m_pVertexArray[0].pos.x;
				pPlayer->VertexMove(xAmount, 0);
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
				/*プレイヤーをこのブロックの上Y座標に移動*/
				float yAmount = m_pVertexArray[0].pos.y - pPlayer->m_pVertexArray[1].pos.y;
				pPlayer->VertexMove(0, yAmount);
				//もしそうならステートを接地中に変える
				pPlayer->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		//更新後のインプットフラグを同期
		pPlayer->SetInputFlag(playerInput);
	}
}

/// <summary>
/// エネミーのチェック
/// </summary>
/// <param name="pEnemy">対象のエネミーのポインタ</param>
void Block::CheckEnemy(Enemy* pEnemy)
{
	if (CollisionCheck(pEnemy))
	{
		//エネミーのインプットフラグの取得
		InputFlag enemyInput = pEnemy->GetInputFlag();

		//エネミーが右に進もうとしているかどうか
		if (enemyInput.Check(InputFlagCode::INPUT_RIGHT))
		{
			//このエネミーがこのブロックの左側に衝突しているか
			if (LeftCheck(pEnemy))
			{
				//もしそうなら左に進ませる
				enemyInput.ReSet(InputFlagCode::INPUT_RIGHT);
				enemyInput.Set(InputFlagCode::INPUT_LEFT);
			}
		}

		//エネミーが左に進もうとしているかどうか
		if (enemyInput.Check(InputFlagCode::INPUT_LEFT))
		{
			//このエネミーがこのブロックの右側に衝突しているか
			if (RightCheck(pEnemy))
			{
				//もしそうなら右に進ませる
				enemyInput.ReSet(InputFlagCode::INPUT_LEFT);
				enemyInput.Set(InputFlagCode::INPUT_RIGHT);
			}
		}

		//エネミーがFALL中かどうか
		if (pEnemy->GetMoveObjState() == MoveObjState::FALL || pEnemy->GetMoveObjState() == MoveObjState::CHECK_GROUND)
		{
			if (UpCheck(pEnemy))
			{
				/*プレイヤーをこのブロックの上Y座標に移動*/
				float yAmount = m_pVertexArray[0].pos.y - pEnemy->m_pVertexArray[1].pos.y;
				pEnemy->VertexMove(0, yAmount);
				//もしそうならステートを接地中に変える
				pEnemy->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		//更新後のインプットフラグを同期
		pEnemy->SetInputFlag(enemyInput);
	}
}