#include"Block.h"
#include"Player.h"
#include"Flag.h"
#include"Enum.h"

Block::Block(float xPos, float yPos, float zPos, float xSize, float ySize) : Square::Square(xPos, yPos, zPos, xSize, ySize){}

Block::~Block() {}

void Block::CheckPlayer(Player* pPlayer, InputFlag* pInputFlag)
{
	if (CollisionCheck(pPlayer))
	{
		//�v���C���[���E�ɐi�����Ƃ��Ă��邩�ǂ���
		if (pInputFlag->Check(InputFlagCode::INPUT_RIGHT))
		{
			//���̃v���C���[�����̃u���b�N�̍����ɏՓ˂��Ă��邩
			if (LeftCheck(pPlayer, pInputFlag))
			{
				//���������Ȃ�E�ɐi�߂Ȃ�����
				pInputFlag->ReSet(InputFlagCode::INPUT_RIGHT);
				pPlayer->m_NowWalkSpeed = 0.0f;
			}
		}

		//�v���C���[�����ɐi�����Ƃ��Ă��邩�ǂ���
		if (pInputFlag->Check(InputFlagCode::INPUT_LEFT))
		{
			//���̃v���C���[�����̃u���b�N�̉E���ɏՓ˂��Ă��邩
			if (RightCheck(pPlayer, pInputFlag))
			{
				//���������Ȃ獶�ɐi�߂Ȃ�����
				pInputFlag->ReSet(InputFlagCode::INPUT_LEFT);
				pPlayer->m_NowWalkSpeed = 0.0f;
			}
		}

		//�v���C���[���W�����v�����ǂ���
		if (pPlayer->m_PlayerState == MoveObjState::JUMP)
		{
			if (DownCheck(pPlayer, pInputFlag))
			{
				//���������Ȃ�X�e�[�g��FALL�ɕς���
				pPlayer->m_PlayerState = MoveObjState::FALL;
				pPlayer->m_JumpFlag = false;

				return;
			}
		}

		//�v���C���[��FALL�����ǂ���
		if (pPlayer->m_PlayerState == MoveObjState::FALL || pPlayer->m_PlayerState == MoveObjState::CHECK_GROUND)
		{
			if (UpCheck(pPlayer, pInputFlag))
			{
				//���������Ȃ�X�e�[�g��ڒn���ɕς���
				pPlayer->m_PlayerState = MoveObjState::ON_THE_GROUND;

				return;
			}
		}
	}
}

bool Block::LeftCheck(Player* pPlayer, InputFlag* pInputFlag)
{
	//�v���C���[�����̃u���b�N�̍����ɂ��邩
	if (pPlayer->m_xPos <= m_xPos)
	{
		//�v���C���[�̉E�ォ�E���̒��_�����̃u���b�N�̍���A�����̊Ԃɂ��邩
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
	//�v���C���[�����̃u���b�N�̉E���ɂ��邩
	if (pPlayer->m_xPos >= m_xPos)
	{
		//�v���C���[�̍��ォ�����̒��_�����̃u���b�N�̉E��A�E���̊Ԃɂ��邩
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
	//�v���C���[�����̃u���b�N�̉��ɂ��邩
	if (pPlayer->m_yPos <= m_yPos)
	{
		//�v���C���[�̍��ォ�E��̒��_�����̃u���b�N�̍����A�E���̊Ԃɂ��邩
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
	//�v���C���[�����̃u���b�N�̏�ɂ��邩
	if (pPlayer->m_yPos >= m_yPos)
	{
		//�v���C���[�̍������E���̒��_�����̃u���b�N�̍���A�E��̊Ԃɂ��邩
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