#include"Block.h"
#include"Player.h"
#include"Flag.h"
#include"Enum.h"
#include"Enemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="size">�T�C�Y</param>
Block::Block(Vector3 pos, Vector2 size) : Square::Square(pos, size){}

void Block::CheckPlayer(Player* pPlayer)
{
	if (CollisionCheck(pPlayer))
	{
		//�v���C���[�̃C���v�b�g�t���O�̎擾
		InputFlag playerInput = pPlayer->GetInputFlag();

		//�v���C���[���E�ɐi�����Ƃ��Ă��邩�ǂ���
		if (playerInput.Check(InputFlagCode::INPUT_RIGHT))
		{
			//���̃v���C���[�����̃u���b�N�̍����ɏՓ˂��Ă��邩
			if (LeftCheck(pPlayer))
			{
				//���������Ȃ�E�ɐi�߂Ȃ�����
				playerInput.ReSet(InputFlagCode::INPUT_RIGHT);
				pPlayer->SetNowWalkSpeed(0.0f);
			}
		}

		//�v���C���[�����ɐi�����Ƃ��Ă��邩�ǂ���
		if (playerInput.Check(InputFlagCode::INPUT_LEFT))
		{
			//���̃v���C���[�����̃u���b�N�̉E���ɏՓ˂��Ă��邩
			if (RightCheck(pPlayer))
			{
				//���������Ȃ獶�ɐi�߂Ȃ�����
				playerInput.ReSet(InputFlagCode::INPUT_LEFT);
				pPlayer->SetNowWalkSpeed(0.0f);
			}
		}

		//�v���C���[���W�����v�����ǂ���
		if (pPlayer->GetMoveObjState() == MoveObjState::JUMP)
		{
			if (DownCheck(pPlayer))
			{
				//���������Ȃ�X�e�[�g��FALL�ɕς���
				pPlayer->SetMoveObjState(MoveObjState::FALL);
				pPlayer->SetJumpFlag(false);

				return;
			}
		}

		//�v���C���[��FALL�����ǂ���
		if (pPlayer->GetMoveObjState() == MoveObjState::FALL || pPlayer->GetMoveObjState() == MoveObjState::CHECK_GROUND)
		{
			if (UpCheck(pPlayer))
			{
				//���������Ȃ�X�e�[�g��ڒn���ɕς���
				pPlayer->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		//�X�V��̃C���v�b�g�t���O�𓯊�
		pPlayer->SetInputFlag(playerInput);
	}
}

void Block::CheckEnemy(Enemy* pEnemy)
{
	if (CollisionCheck(pEnemy))
	{
		//�G�l�~�[�̃C���v�b�g�t���O�̎擾
		InputFlag enemyInput = pEnemy->GetInputFlag();

		//�v���C���[���E�ɐi�����Ƃ��Ă��邩�ǂ���
		if (enemyInput.Check(InputFlagCode::INPUT_RIGHT))
		{
			//���̃v���C���[�����̃u���b�N�̍����ɏՓ˂��Ă��邩
			if (LeftCheck(pEnemy))
			{
				//���������Ȃ獶�ɐi�܂���
				enemyInput.ReSet(InputFlagCode::INPUT_RIGHT);
				enemyInput.Set(InputFlagCode::INPUT_LEFT);
			}
		}

		//�v���C���[�����ɐi�����Ƃ��Ă��邩�ǂ���
		if (enemyInput.Check(InputFlagCode::INPUT_LEFT))
		{
			//���̃v���C���[�����̃u���b�N�̉E���ɏՓ˂��Ă��邩
			if (RightCheck(pEnemy))
			{
				//���������Ȃ�E�ɐi�܂���
				enemyInput.ReSet(InputFlagCode::INPUT_LEFT);
				enemyInput.Set(InputFlagCode::INPUT_RIGHT);
			}
		}

		//�v���C���[��FALL�����ǂ���
		if (pEnemy->GetMoveObjState() == MoveObjState::FALL || pEnemy->GetMoveObjState() == MoveObjState::CHECK_GROUND)
		{
			if (UpCheck(pEnemy))
			{
				//���������Ȃ�X�e�[�g��ڒn���ɕς���
				pEnemy->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		//�X�V��̃C���v�b�g�t���O�𓯊�
		pEnemy->SetInputFlag(enemyInput);
	}
}

bool Block::LeftCheck(Square* pSquare)
{
	//�v���C���[�����̃u���b�N�̍����ɂ��邩
	if (pSquare->GetxPos() <= m_xPos)
	{
		//�v���C���[�̉E�ォ�E���̒��_�����̃u���b�N�̍���A�����̊Ԃɂ��邩
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
	//�v���C���[�����̃u���b�N�̉E���ɂ��邩
	if (pSquare->GetxPos() >= m_xPos)
	{
		//�v���C���[�̍��ォ�����̒��_�����̃u���b�N�̉E��A�E���̊Ԃɂ��邩
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
	//�v���C���[�����̃u���b�N�̉��ɂ��邩
	if (pSquare->GetyPos() <= m_yPos)
	{
		//�v���C���[�̍��ォ�E��̒��_�����̃u���b�N�̍����A�E���̊Ԃɂ��邩
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
	//�v���C���[�����̃u���b�N�̏�ɂ��邩
	if (pSquare->GetyPos() >= m_yPos)
	{
		//�v���C���[�̍������E���̒��_�����̃u���b�N�̍���A�E��̊Ԃɂ��邩
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