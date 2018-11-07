#include"Block.h"
#include"Player.h"
#include"Flag.h"
#include"Enum.h"


Block::Block(Vector3 pos, Vector2 size) : Square::Square(pos, size){}

Block::~Block() {}

void Block::CheckPlayer(Player* pPlayer, InputFlag* pInputFlag)
{
	if (CollisionCheck(pPlayer))
	{
		//プレイヤーが右に進もうとしているかどうか
		if (pInputFlag->Check(InputFlagCode::INPUT_RIGHT))
		{
			//このプレイヤーがこのブロックの左側に衝突しているか
			if (LeftCheck(pPlayer, pInputFlag))
			{
				//もしそうなら右に進めなくする
				pInputFlag->ReSet(InputFlagCode::INPUT_RIGHT);
				pPlayer->SetNowWalkSpeed(0.0f);
			}
		}

		//プレイヤーが左に進もうとしているかどうか
		if (pInputFlag->Check(InputFlagCode::INPUT_LEFT))
		{
			//このプレイヤーがこのブロックの右側に衝突しているか
			if (RightCheck(pPlayer, pInputFlag))
			{
				//もしそうなら左に進めなくする
				pInputFlag->ReSet(InputFlagCode::INPUT_LEFT);
				pPlayer->SetNowWalkSpeed(0.0f);
			}
		}

		//プレイヤーがジャンプ中かどうか
		if (pPlayer->GetMoveObjState() == MoveObjState::JUMP)
		{
			if (DownCheck(pPlayer, pInputFlag))
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
			if (UpCheck(pPlayer, pInputFlag))
			{
				//もしそうならステートを接地中に変える
				pPlayer->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}
	}
}

bool Block::LeftCheck(Player* pPlayer, InputFlag* pInputFlag)
{
	//プレイヤーがこのブロックの左側にあるか
	if (pPlayer->GetxPos() <= m_xPos)
	{
		//プレイヤーの右上か右下の頂点がこのブロックの左上、左下の間にあるか
		if (pPlayer->m_pVertexArray[3].pos[1] - m_Threshold <= m_pVertexArray[0].pos[1] && pPlayer->m_pVertexArray[3].pos[1] - m_Threshold >= m_pVertexArray[2].pos[1])
		{
			return true;
		}
		else if (pPlayer->m_pVertexArray[1].pos[1] + m_Threshold <= m_pVertexArray[0].pos[1] && pPlayer->m_pVertexArray[1].pos[1] + m_Threshold >= m_pVertexArray[2].pos[1])
		{
			return true;
		}
	}

	return false;
}

bool Block::RightCheck(Player* pPlayer, InputFlag* pInputFlag)
{
	//プレイヤーがこのブロックの右側にあるか
	if (pPlayer->GetxPos() >= m_xPos)
	{
		//プレイヤーの左上か左下の頂点がこのブロックの右上、右下の間にあるか
		if (pPlayer->m_pVertexArray[0].pos[1] - m_Threshold <= m_pVertexArray[3].pos[1] && pPlayer->m_pVertexArray[3].pos[1] - m_Threshold >= m_pVertexArray[1].pos[1])
		{
			return true;
		}
		else if (pPlayer->m_pVertexArray[2].pos[1] + m_Threshold <= m_pVertexArray[3].pos[1] && pPlayer->m_pVertexArray[1].pos[1] + m_Threshold >= m_pVertexArray[1].pos[1])
		{
			return true;
		}
	}

	return false;
}

bool Block::DownCheck(Player* pPlayer, InputFlag* pInputFlag)
{
	//プレイヤーがこのブロックの下にあるか
	if (pPlayer->GetyPos() <= m_yPos)
	{
		//プレイヤーの左上か右上の頂点がこのブロックの左下、右下の間にあるか
		if (pPlayer->m_pVertexArray[0].pos[0] + m_Threshold >= m_pVertexArray[2].pos[0] && pPlayer->m_pVertexArray[0].pos[0] + m_Threshold <= m_pVertexArray[1].pos[0])
		{
			return true;
		}
		else if (pPlayer->m_pVertexArray[3].pos[0] - m_Threshold >= m_pVertexArray[2].pos[0] && pPlayer->m_pVertexArray[3].pos[0] - m_Threshold <= m_pVertexArray[1].pos[0])
		{
			return true;
		}
	}

	return false;
}

bool Block::UpCheck(Player* pPlayer, InputFlag* pInputFlag)
{
	//プレイヤーがこのブロックの上にあるか
	if (pPlayer->GetyPos() >= m_yPos)
	{
		//プレイヤーの左下か右下の頂点がこのブロックの左上、右上の間にあるか
		if (pPlayer->m_pVertexArray[2].pos[0] + m_Threshold >= m_pVertexArray[0].pos[0] && pPlayer->m_pVertexArray[2].pos[0] + m_Threshold <= m_pVertexArray[3].pos[0])
		{
			return true;
		}
		else if (pPlayer->m_pVertexArray[1].pos[0] - m_Threshold >= m_pVertexArray[0].pos[0] && pPlayer->m_pVertexArray[1].pos[0] - m_Threshold <= m_pVertexArray[3].pos[0])
		{
			return true;
		}
	}

	return false;
}