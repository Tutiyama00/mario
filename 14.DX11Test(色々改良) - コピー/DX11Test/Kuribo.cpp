#include"Kuribo.h"
#include"Animation.h"
#include"TextureData.h"
#include"ScoreManager.h"

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="size">サイズ</param>
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
/// デストラクタ
/// </summary>
Kuribo::~Kuribo()
{
	if (m_pWalkAnimation != nullptr) { delete m_pWalkAnimation; m_pWalkAnimation = nullptr; }
}

/*-------------------------------------         ----------------------------------*/
/*-------------------------------------  Enemy  ----------------------------------*/
/*-------------------------------------         ----------------------------------*/

/// <summary>
/// 動作
/// </summary>
void Kuribo::Move()
{
	/*生きていない状態だったらリターンして動かさない*/
	if (!m_LivingFlag){ return; }

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
	if (!m_LivingFlag) { return; }

	m_pWalkAnimation->AnimPlay();
	m_pMainTextureResource = m_pWalkAnimation->GetAnimTextureResource();
	m_pMainTextureSRV = m_pWalkAnimation->GetAnimTextureSRV();

	/* 右と左どちらに向いているのかの判定 */
	if (m_NowWalkSpeed > 0 && m_ParallelInvertedFlag)
	{
		ParallelInverted();
	}
	else if (m_NowWalkSpeed < 0 && !m_ParallelInvertedFlag)
	{
		ParallelInverted();
	}

	Render(m_pVertexArray, m_IndexArraySize);
}