#include"Nokonoko.h"
#include"Player.h"
#include"Animation.h"

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
	LoadTexture(L"Texture/NOKONOKO1.png");
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_InputFlag.Set(InputFlagCode::INPUT_LEFT);

	m_pWalkAnimation = new Animation();
	m_pWalkAnimation->AddAnimResource(L"Texture/NOKONOKO1.png");
	m_pWalkAnimation->AddAnimResource(L"Texture/NOKONOKO2.png");
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
	if (!m_LivingFlag) { return; }

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
			Walk(m_MaxWalkSpeed * 7);
		}
		else
		{
			Walk(m_MaxWalkSpeed);
		}
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_LEFT))
	{
		if (m_NokonokoState == NokonokoState::KOURA_RUN)
		{
			Walk(-m_MaxWalkSpeed * 7);
		}
		else
		{
			Walk(-m_MaxWalkSpeed);
		}
	}

	if (m_MoveObjState == MoveObjState::ON_THE_GROUND)
	{
		m_MoveObjState = MoveObjState::CHECK_GROUND;
	}

	if (m_NokonokoState == NokonokoState::NORMAL)
	{
		AnimResource animResource;
		animResource = m_pWalkAnimation->AnimPlay();

		m_pMainTextureResource = animResource.m_pAnimTextureResource;
		m_pMainTextureSRV      = animResource.m_pAnimTextureSRV;
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

	/* �v���C���[�ƏՓ˂��Ă����� */
	if (CollisionCheck(pPlayer))
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
				pPlayer->MiniJumpStart();
				LoadTexture(L"Texture/KOURA1.png");
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

	if (CollisionCheck(pEnemy))
	{
		/* �G�l�~�[�̃C���v�b�g�t���O�̎擾 */
		InputFlag enemyInput = pEnemy->GetInputFlag();

		switch (m_NokonokoState)
		{
		case NokonokoState::KOURA_RUN:
			pEnemy->Die();
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