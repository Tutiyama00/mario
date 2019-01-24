#include"Kuribo.h"
#include"Animation.h"
#include"TextureData.h"
#include"ScoreManager.h"
#include"Player.h"
#include"SoundData.h"

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="size">�T�C�Y</param>
Kuribo::Kuribo(Vector3 pos, Vector2 size) : Enemy(pos,size)
{
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_pMainTextureResource = TextureData::Instance()->GetKURIBO1_TR();
	m_pMainTextureSRV      = TextureData::Instance()->GetKURIBO1_TSRV();

	m_InputFlag.Set(InputFlagCode::INPUT_LEFT);

	m_pWalkAnimation = new Animation();
	m_pWalkAnimation->AddAnimResource(TextureData::Instance()->GetKURIBO1_TR(), TextureData::Instance()->GetKURIBO1_TSRV());
	m_pWalkAnimation->AddAnimResource(TextureData::Instance()->GetKURIBO2_TR(), TextureData::Instance()->GetKURIBO2_TSRV());
	m_pWalkAnimation->SetAnimIntervalFlame(25);

	m_DieScorePoint = KURIBO_SCORE;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Kuribo::~Kuribo()
{
	if (m_pWalkAnimation != nullptr) { delete m_pWalkAnimation; m_pWalkAnimation = nullptr; }
}

/*-------------------------------------         ----------------------------------*/
/*-------------------------------------  Enemy  ----------------------------------*/
/*-------------------------------------         ----------------------------------*/

/// <summary>
/// ����
/// </summary>
void Kuribo::Move()
{
	/*�����Ă��Ȃ���Ԃ������烊�^�[�����ē������Ȃ�*/
	if (!m_LivingFlag)
	{
		/*�`�悳���Ă��邩�ǂ���*/
		if (m_RenderFlag)
		{
			/*���܂�Ď���ł��邩*/
			if (m_StompDieFlag)
			{
				if (m_StompRenderFrameCounter < M_STOMP_RENDER_FRAME)
				{
					m_StompRenderFrameCounter++;
				}
				else
				{
					m_RenderFlag = false;
				}

				return;
			}
			
			/*�ʏ�̎��ɕ������Ă��邩�ǂ���*/
			if (m_StanderdDieFlag)
			{
				/*�ʏ펀�S���o*/
				StandardDie();

				return;
			}
		}

		return;
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

	if (m_InputFlag.Check(InputFlagCode::INPUT_RIGHT))
	{
		m_NowWalkSpeed = m_MaxWalkSpeed;
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_LEFT))
	{
		m_NowWalkSpeed = -m_MaxWalkSpeed;
	}

	Walk(m_NowWalkSpeed);

	if (m_MoveObjState == MoveObjState::ON_THE_GROUND)
	{
		m_MoveObjState = MoveObjState::CHECK_GROUND;
	}
}

void Kuribo::ThisObjRender()
{
	if (m_LivingFlag)
	{
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

	Render(m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// ���S����
/// </summary>
void Kuribo::Die()
{
	if (!m_LivingFlag) { return; }

	ScoreManager::Instance()->AddScore(m_DieScorePoint);
	m_LivingFlag = false;
}

/// <summary>
/// �v���C���[�̃`�F�b�N
/// </summary>
/// <param name="pPlayer">�`�F�b�N����v���C���[�̃|�C���^�[</param>
/// <param name="pInputFlag">���͏��</param>
void Kuribo::CheckPlayer(Player* pPlayer)
{
	if (!m_LivingFlag) { return; }
	if (!pPlayer->GetLivibgFlag()) { return; }

	/* �v���C���[�ƏՓ˂��Ă����� */
	if (CollisionCheck(pPlayer))
	{
		if (UpCheck(pPlayer))
		{
			SoundData::Instance()->GetSTOMPsoundBuffer()->SetCurrentPosition(0);
			SoundData::Instance()->GetSTOMPsoundBuffer()->Play(0, 0, 0);
			m_pMainTextureResource = TextureData::Instance()->GetKURIBO_DEAD_TR();
			m_pMainTextureSRV = TextureData::Instance()->GetKURIBO_DEAD_TSRV();
			m_StompDieFlag = true;
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