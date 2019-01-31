#include"Enemy.h"
#include"Player.h"
#include"SoundData.h"
#include"ScoreManager.h"
#include<string>

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// ���S����
/// </summary>
void Enemy::Die()
{
	if (!m_LivingFlag) { return; }

	ScoreManager::Instance()->AddScore(m_DieScorePoint);
	m_LivingFlag = false;
}

/// <summary>
/// �ʏ�̎��S�������o
/// </summary>
/// <param name="direction">��ԕ����itrue=�E�Afalse=���j</param>
void Enemy::StartStandardDie(bool direction)
{
	/*���S����*/
	Die();
	/*�ʏ�̎��S�������n�܂�̂Ńt���O�𗧂Ă�*/
	m_StanderdDieFlag = true;

	/*�����������ǂ���*/
	if (!direction)
	{
		/*X���̈ړ��ʂ̕����𕉂ɂ���*/
		m_S_DieMoveXMoveAmount *= -1;
	}

	m_pVertexArray[0].tex.x = 0;  m_pVertexArray[0].tex.y = 1;
	m_pVertexArray[1].tex.x = 1;  m_pVertexArray[1].tex.y = 0;
	m_pVertexArray[2].tex.x = 0;  m_pVertexArray[2].tex.y = 0;
	m_pVertexArray[3].tex.x = 1;  m_pVertexArray[3].tex.y = 1;
}

/*#####################################             #####################################*/
/*#####################################  protected  #####################################*/
/*#####################################             #####################################*/

/// <summary>
/// �ʏ�̎��S�������o
/// </summary>
void Enemy::StandardDie()
{
	/*�܂����S�����ɂ�����t���[���������ǂ���*/
	if (m_S_DieMoveFrameCounter < M_S_DIE_MOVE_FRAME)
	{
		if (std::abs(m_S_DieMoveNowSpeed) <= M_S_DIE_MOVE_SPEED_MAX)
		{
			m_S_DieMoveNowSpeed -= m_S_DieMoveChangeAmount;
		}
		else
		{
			if (m_S_DieMoveNowSpeed < 0)
			{
				m_S_DieMoveNowSpeed = -M_S_DIE_MOVE_SPEED_MAX;
			}
			else
			{
				m_S_DieMoveNowSpeed = M_S_DIE_MOVE_SPEED_MAX;
			}
		}

		/* �ړ� */
		VertexMove(m_S_DieMoveXMoveAmount, m_S_DieMoveNowSpeed);
	}
	else
	{
		m_RenderFlag = false;
	}
}

/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  NotPlayer  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// �v���C���[�̃`�F�b�N
/// </summary>
/// <param name="pPlayer">�`�F�b�N����v���C���[�̃|�C���^�[</param>
/// <param name="pInputFlag">���͏��</param>
void Enemy::CheckPlayer(Player* pPlayer)
{
	if (!m_LivingFlag) { return; }
	if (!pPlayer->GetLivibgFlag()) { return; }

	/* �v���C���[�ƏՓ˂��Ă����� */
	if (CollisionCheck(pPlayer, -(pPlayer->GetxSize() / 2)))
	{
		if (UpCheck(pPlayer))
		{
			SoundData::Instance()->GetSTOMPsoundBuffer()->SetCurrentPosition(0);
			SoundData::Instance()->GetSTOMPsoundBuffer()->Play(0,0,0);
			pPlayer->MiniJumpStart();
			Die();
		}
		else
		{
			/* �v���C���[���E�� */
			pPlayer->Die();
		}
	}
}

/// <summary>
/// Enemy�̃`�F�b�N
/// </summary>
/// <param name="pEnemy">�`�F�b�N����Ώ�</param>
void Enemy::CheckEnemy(Enemy* pEnemy)
{
	if (!m_LivingFlag) { return; }
	if (!pEnemy->GetLivingFlag()) { return; }

	if (CollisionCheck(pEnemy))
	{
		/* �G�l�~�[�̃C���v�b�g�t���O�̎擾 */
		InputFlag enemyInput = pEnemy->GetInputFlag();

		/* �G�l�~�[���E�ɐi�����Ƃ��Ă��邩�ǂ��� */
		if (enemyInput.Check(InputFlagCode::INPUT_RIGHT))
		{
			/* ���̃G�l�~�[�����̃u���b�N�̍����ɏՓ˂��Ă��邩 */
			if (LeftCheck(pEnemy))
			{
				/* ���������Ȃ獶�ɐi�܂��� */
				enemyInput.ReSet(InputFlagCode::INPUT_RIGHT);
				enemyInput.Set(InputFlagCode::INPUT_LEFT);
			}
		}

		/* �G�l�~�[�����ɐi�����Ƃ��Ă��邩�ǂ��� */
		if (enemyInput.Check(InputFlagCode::INPUT_LEFT))
		{
			/* ���̃G�l�~�[�����̃u���b�N�̉E���ɏՓ˂��Ă��邩 */
			if (RightCheck(pEnemy))
			{
				/* ���������Ȃ�E�ɐi�܂��� */
				enemyInput.ReSet(InputFlagCode::INPUT_LEFT);
				enemyInput.Set(InputFlagCode::INPUT_RIGHT);
			}
		}

		/* �G�l�~�[��FALL�����ǂ��� */
		if (pEnemy->GetMoveObjState() == MoveObjState::FALL || pEnemy->GetMoveObjState() == MoveObjState::CHECK_GROUND)
		{
			if (UpCheck(pEnemy))
			{
				/* ���������Ȃ�X�e�[�g��ڒn���ɕς��� */
				pEnemy->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		/* �X�V��̃C���v�b�g�t���O�𓯊� */
		pEnemy->SetInputFlag(enemyInput);
	}
}



/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// ���̃I�u�W�F�N�g�̃o�b�t�@�̍쐬
/// </summary>
void Enemy::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/// <summary>
/// ���̃I�u�W�F�N�g�̕`��
/// </summary>
void Enemy::ThisObjRender()
{
	if (!m_RenderFlag) { return; }

	Render(m_pVertexArray, m_IndexArraySize);
}


/*#####################################             #####################################*/
/*#####################################  PROTECTED  #####################################*/
/*#####################################             #####################################*/

/*-------------------------------------            ----------------------------------*/
/*-------------------------------------  IMoveObj  ----------------------------------*/
/*-------------------------------------            ----------------------------------*/

/// <summary>
/// ����
/// </summary>
/// <param name="xAmount">�ړ��ʁiX���j</param>
void Enemy::Walk(float xAmount)
{
	if (!m_LivingFlag) { return; }

	VertexMove(xAmount, 0);
}

/// <summary>
/// �W�����v(�}���I��)
/// </summary>
/// <returns>�W�����v�ł������ǂ����@true=�ł����@false=�ł��Ȃ�����</returns>
bool Enemy::Jump(const unsigned int MAX_FRAME)
{
	if (!m_LivingFlag) { return false; }

	if (m_JumpLevelCount > 0)
	{
		float jumpAmount = m_JumpPower * (m_JumpLevelCount / m_JumpAbjustPoint);

		VertexMove(0, jumpAmount);

		m_JumpLevelCount--;

		return true;
	}

	return false;
}

/// <summary>
/// �����i�}���I���j
/// </summary>
void Enemy::Fall()
{
	if (!m_LivingFlag) { return; }

	float fallAmount = m_JumpPower * (m_JumpLevelCount / m_JumpAbjustPoint);

	VertexMove(0, -fallAmount);

	if (m_JumpLevelCount < m_MaxJumpLevel)
	{
		m_JumpLevelCount++;
	}
}