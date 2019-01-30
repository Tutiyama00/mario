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
/// �v���C���[�̃`�F�b�N
/// </summary>
/// <param name="pPlayer">�Ώۂ̃v���C���[�̃|�C���^</param>
void Block::CheckPlayer(Player* pPlayer)
{
	if (!pPlayer->GetLivibgFlag()) { return; }

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
				/*�v���C���[�����̃u���b�N�̍�X���W�Ɉړ�*/
				float xAmount = m_pVertexArray[0].pos.x - pPlayer->m_pVertexArray[1].pos.x;
				pPlayer->VertexMove(xAmount, 0);
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
				/*�v���C���[�����̃u���b�N�̉EX���W�Ɉړ�*/
				float xAmount = m_pVertexArray[1].pos.x - pPlayer->m_pVertexArray[0].pos.x;
				pPlayer->VertexMove(xAmount, 0);
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
				/*�v���C���[�����̃u���b�N�̏�Y���W�Ɉړ�*/
				float yAmount = m_pVertexArray[0].pos.y - pPlayer->m_pVertexArray[1].pos.y;
				pPlayer->VertexMove(0, yAmount);
				//���������Ȃ�X�e�[�g��ڒn���ɕς���
				pPlayer->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		//�X�V��̃C���v�b�g�t���O�𓯊�
		pPlayer->SetInputFlag(playerInput);
	}
}

/// <summary>
/// �G�l�~�[�̃`�F�b�N
/// </summary>
/// <param name="pEnemy">�Ώۂ̃G�l�~�[�̃|�C���^</param>
void Block::CheckEnemy(Enemy* pEnemy)
{
	if (CollisionCheck(pEnemy))
	{
		//�G�l�~�[�̃C���v�b�g�t���O�̎擾
		InputFlag enemyInput = pEnemy->GetInputFlag();

		//�G�l�~�[���E�ɐi�����Ƃ��Ă��邩�ǂ���
		if (enemyInput.Check(InputFlagCode::INPUT_RIGHT))
		{
			//���̃G�l�~�[�����̃u���b�N�̍����ɏՓ˂��Ă��邩
			if (LeftCheck(pEnemy))
			{
				//���������Ȃ獶�ɐi�܂���
				enemyInput.ReSet(InputFlagCode::INPUT_RIGHT);
				enemyInput.Set(InputFlagCode::INPUT_LEFT);
			}
		}

		//�G�l�~�[�����ɐi�����Ƃ��Ă��邩�ǂ���
		if (enemyInput.Check(InputFlagCode::INPUT_LEFT))
		{
			//���̃G�l�~�[�����̃u���b�N�̉E���ɏՓ˂��Ă��邩
			if (RightCheck(pEnemy))
			{
				//���������Ȃ�E�ɐi�܂���
				enemyInput.ReSet(InputFlagCode::INPUT_LEFT);
				enemyInput.Set(InputFlagCode::INPUT_RIGHT);
			}
		}

		//�G�l�~�[��FALL�����ǂ���
		if (pEnemy->GetMoveObjState() == MoveObjState::FALL || pEnemy->GetMoveObjState() == MoveObjState::CHECK_GROUND)
		{
			if (UpCheck(pEnemy))
			{
				/*�v���C���[�����̃u���b�N�̏�Y���W�Ɉړ�*/
				float yAmount = m_pVertexArray[0].pos.y - pEnemy->m_pVertexArray[1].pos.y;
				pEnemy->VertexMove(0, yAmount);
				//���������Ȃ�X�e�[�g��ڒn���ɕς���
				pEnemy->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		//�X�V��̃C���v�b�g�t���O�𓯊�
		pEnemy->SetInputFlag(enemyInput);
	}
}