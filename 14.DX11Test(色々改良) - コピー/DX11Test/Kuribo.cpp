#include"Kuribo.h"
#include"Animation.h"

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
	LoadTexture(L"Texture/KURIBO1.png");
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_InputFlag.Set(InputFlagCode::INPUT_LEFT);

	m_pWalkAnimation = new Animation();
	m_pWalkAnimation->AddAnimResource(L"Texture/KURIBO1.png");
	m_pWalkAnimation->AddAnimResource(L"Texture/KURIBO2.png");
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
		Walk(m_MaxWalkSpeed);
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_LEFT))
	{
		Walk(-m_MaxWalkSpeed);
	}

	if (m_MoveObjState == MoveObjState::ON_THE_GROUND)
	{
		m_MoveObjState = MoveObjState::CHECK_GROUND;
	}

   /* AnimResource pAnimResource;
	pAnimResource = m_pWalkAnimation->AnimPlay();

	m_pMainTextureResource = pAnimResource->m_pAnimTextureResource;
	m_pMainTextureSRV = pAnimResource->m_pAnimTextureSRV;*/
}

void Kuribo::ThisObjRender()
{
	if (!m_LivingFlag) { return; }

	const AnimResource* pAnimResource = nullptr;

	/*pAnimResource          = m_pWalkAnimation->AnimPlay();

	m_pMainTextureResource = pAnimResource->m_pAnimTextureResource;
	m_pMainTextureSRV      = pAnimResource->m_pAnimTextureSRV;*/

	Render(m_pVertexArray, m_IndexArraySize);

	if (pAnimResource != nullptr)
	{
		delete pAnimResource;
		pAnimResource = nullptr;
	}
}