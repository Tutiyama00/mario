#include"Nokonoko.h"
#include"Player.h"
#include"Animation.h"
#include"TextureData.h"
#include"SoundData.h"
#include"ScoreManager.h"

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="size">�T�C�Y</param>
Nokonoko::Nokonoko(Vector3 pos, Vector2 size) : Enemy(pos, size)
{
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_pMainTextureResource = TextureData::Instance()->GetNOKONOKO1_TR();
	m_pMainTextureSRV = TextureData::Instance()->GetNOKONOKO1_TSRV();

	m_InputFlag.Set(InputFlagCode::INPUT_LEFT);

	m_pWalkAnimation = new Animation();
	m_pWalkAnimation->AddAnimResource(TextureData::Instance()->GetNOKONOKO1_TR(), TextureData::Instance()->GetNOKONOKO1_TSRV());
	m_pWalkAnimation->AddAnimResource(TextureData::Instance()->GetNOKONOKO2_TR(), TextureData::Instance()->GetNOKONOKO2_TSRV());
	m_pWalkAnimation->SetAnimIntervalFlame(25);

	m_DieScorePoint = NOKONOKO_SCORE;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Nokonoko::~Nokonoko()
{
	if (m_pWalkAnimation != nullptr) { delete m_pWalkAnimation; m_pWalkAnimation = nullptr; }
}

/*-------------------------------------         ----------------------------------*/
/*-------------------------------------  Enemy  ----------------------------------*/
/*-------------------------------------         ----------------------------------*/

/// <summary>
/// ����
/// </summary>
void Nokonoko::Move()
{
	/*�����Ă��Ȃ���Ԃ������烊�^�[�����ē������Ȃ�*/
	if (!m_LivingFlag)
	{
		if (m_RenderFlag)
		{
			/*�ʏ�̎��ɕ������Ă��邩�ǂ���*/
			if (m_StanderdDieFlag)
			{
				/*�ʏ펀�S���o*/
				StandardDie();

				return;
			}
		}
	}

	switch (m_MoveObjState)
	{
	case MoveObjState::CHECK_GROUND:
		m_MoveObjState = MoveObjState::FALL;

	case MoveObjState::ON_THE_GROUND:

		if (m_JumpLevelCount != m_MaxJumpLevel)
		{
			m_JumpLevelCount = m_MaxJumpLevel;
		}

		break;

	case MoveObjState::FALL:

		Fall();

		break;
	}

	/* �b�����~�܂��Ă����Ԃ������獶�E�ɓ����Ȃ����� */
	if (m_NokonokoState == NokonokoState::KOURA_STOP)
	{
		m_InputFlag.ReSet(InputFlagCode::INPUT_LEFT);
		m_InputFlag.ReSet(InputFlagCode::INPUT_RIGHT);
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_RIGHT))
	{
		if (m_NokonokoState == NokonokoState::KOURA_RUN)
		{
			m_NowWalkSpeed = m_MaxWalkSpeed * 7;
		}
		else
		{
			m_NowWalkSpeed = m_MaxWalkSpeed;
		}
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_LEFT))
	{
		if (m_NokonokoState == NokonokoState::KOURA_RUN)
		{
			m_NowWalkSpeed = -m_MaxWalkSpeed * 7;
		}
		else
		{
			m_NowWalkSpeed = -m_MaxWalkSpeed;
		}
	}

	if (m_NokonokoState != NokonokoState::KOURA_STOP)
	{
		Walk(m_NowWalkSpeed);
	}

	if (m_MoveObjState == MoveObjState::ON_THE_GROUND)
	{
		m_MoveObjState = MoveObjState::CHECK_GROUND;
	}
}

/// <summary>
/// �v���C���[�̃`�F�b�N
/// </summary>
/// <param name="pPlayer">�`�F�b�N����v���C���[�̃|�C���^�[</param>
/// <param name="pInputFlag">���͏��</param>
void Nokonoko::CheckPlayer(Player* pPlayer)
{
	if (!m_LivingFlag) { return; }
	if (!pPlayer->GetLivibgFlag()) { return; }

	/* �v���C���[�ƏՓ˂��Ă����� */
	if (CollisionCheck(pPlayer, -(pPlayer->GetxSize() / 3)))
	{
		switch (m_NokonokoState)
		{
		case NokonokoState::NORMAL:

			if (m_StateKeepFlag)
			{
				StateKeepFlame();
				break;
			}

			/* �ォ��Փ˂��Ă���̂��ǂ��� */
			if (UpCheck(pPlayer))
			{
				SoundData::Instance()->GetSTOMPsoundBuffer()->SetCurrentPosition(0);
				SoundData::Instance()->GetSTOMPsoundBuffer()->Play(0, 0, 0);

				pPlayer->MiniJumpStart();
				m_NokonokoState = NokonokoState::KOURA_STOP;
				m_InputFlag.AllReSet();
				StateKeepFlameStart();
			}
			else
			{
				/* �v���C���[���E�� */
				pPlayer->Die();
			}

			break;

		case NokonokoState::KOURA_STOP:

			if (m_StateKeepFlag)
			{
				StateKeepFlame();
				break;
			}

			StateKeepFlameStart();
			m_NokonokoState = NokonokoState::KOURA_RUN;

			SoundData::Instance()->GetKICKsoundBuffer()->SetCurrentPosition(0);
			SoundData::Instance()->GetKICKsoundBuffer()->Play(0, 0, 0);

			/* ���E�ǂ��瑤�ɏՓ˂��Ă��邩 */
			if (pPlayer->GetxPos() <= GetxPos())
			{
				m_InputFlag.Set(InputFlagCode::INPUT_RIGHT);
			}
			else
			{
				m_InputFlag.Set(InputFlagCode::INPUT_LEFT);
			}

			break;

		case NokonokoState::KOURA_RUN:


			if (m_StateKeepFlag)
			{
				StateKeepFlame();
				break;
			}

			if (UpCheck(pPlayer))
			{
				SoundData::Instance()->GetSTOMPsoundBuffer()->SetCurrentPosition(0);
				SoundData::Instance()->GetSTOMPsoundBuffer()->Play(0, 0, 0);

				pPlayer->MiniJumpStart();
				m_NokonokoState = NokonokoState::KOURA_STOP;
				m_InputFlag.AllReSet();
				StateKeepFlameStart();
			}
			else
			{
				pPlayer->Die();
			}

			break;
		}
	}
}

/// <summary>
/// Enemy�̃`�F�b�N
/// </summary>
/// <param name="pEnemy">�`�F�b�N����Ώ�</param>
void Nokonoko::CheckEnemy(Enemy* pEnemy)
{
	if (!m_LivingFlag) { return; }
	if (!pEnemy->GetLivingFlag()) { return; }

	if (CollisionCheck(pEnemy))
	{
		/* �G�l�~�[�̃C���v�b�g�t���O�̎擾 */
		InputFlag enemyInput = pEnemy->GetInputFlag();

		switch (m_NokonokoState)
		{
		case NokonokoState::KOURA_RUN:

			/*�m�R�m�R���ǂ��瑤�œG�ɂԂ�������*/
			if (m_xPos < pEnemy->GetxPos())
			{
				/*�E�ɔ�΂�*/
				pEnemy->StartStandardDie(true);
			}
			else
			{
				/*���ɔ�΂�*/
				pEnemy->StartStandardDie(false);
			}
			break;

		default:
			/* �G�l�~�[���E�ɐi�����Ƃ��Ă��邩�ǂ��� */
			if (enemyInput.Check(InputFlagCode::INPUT_RIGHT))
			{
				/* ���̃v���C���[�����̃u���b�N�̍����ɏՓ˂��Ă��邩 */
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
				/* ���̃v���C���[�����̃u���b�N�̉E���ɏՓ˂��Ă��邩 */
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
				}
			}

			break;
		}

		/* �X�V��̃C���v�b�g�t���O�𓯊� */
		pEnemy->SetInputFlag(enemyInput);
	}
}

/// <summary>
/// �`��
/// </summary>
void Nokonoko::ThisObjRender()
{
	/*�`�悵�Ă��悢���ǂ���*/
	if (!m_RenderFlag) { return; }

	/*�����Ă��邩�ǂ���*/
	if (m_LivingFlag)
	{
		/*�m�R�m�R�̃X�e�[�g���m�[�}����Ԃ��ǂ���*/
		if (m_NokonokoState == NokonokoState::NORMAL)
		{
			/*�����A�j���[�V������������*/
			m_pWalkAnimation->AnimPlay();
			m_pMainTextureResource = m_pWalkAnimation->GetAnimTextureResource();
			m_pMainTextureSRV = m_pWalkAnimation->GetAnimTextureSRV();

			/* �E�ƍ��ǂ���Ɍ����Ă���̂��̔��� */
			if (m_NowWalkSpeed > 0 && m_ParallelInvertedFlag)
			{
				ParallelInverted();
			}
			else if (m_NowWalkSpeed < 0 && !m_ParallelInvertedFlag)
			{
				ParallelInverted();
			}
		}
		else
		{
			/*�e�N�X�`�����b���ɂ���*/
			m_pMainTextureResource = TextureData::Instance()->GetKOURA1_TR();
			m_pMainTextureSRV = TextureData::Instance()->GetKOURA1_TSRV();
		}
	}

	/*�`��*/
	Render(m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// �ʏ펀�S�������o�̊J�n
/// </summary>
/// <param name="direction"></param>
void Nokonoko::StartStandardDie(bool direction)
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

	/*�b����Ԃɂ���*/
	m_pMainTextureResource = TextureData::Instance()->GetKOURA1_TR();
	m_pMainTextureSRV = TextureData::Instance()->GetKOURA1_TSRV();

	/*�e�N�X�`�����������܂ɂ���*/
	m_pVertexArray[0].tex.x = 0;  m_pVertexArray[0].tex.y = 1;
	m_pVertexArray[1].tex.x = 1;  m_pVertexArray[1].tex.y = 0;
	m_pVertexArray[2].tex.x = 0;  m_pVertexArray[2].tex.y = 0;
	m_pVertexArray[3].tex.x = 1;  m_pVertexArray[3].tex.y = 1;
}

/*#####################################           #####################################*/
/*#####################################  PRIVATE  #####################################*/
/*#####################################           #####################################*/

void Nokonoko::StateKeepFlameStart()
{
	m_StateKeepFlag = true;
	m_StateKeepFlameCount = 0;
}

void Nokonoko::StateKeepFlame()
{
	if (m_StateKeepFlameCount <= M_STATE_KEEP_FLAME)
	{
		m_StateKeepFlameCount++;
	}
	else
	{
		m_StateKeepFlag = false;
	}
}