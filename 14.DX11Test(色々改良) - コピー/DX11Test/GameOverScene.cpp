#include"GameOverScene.h"
#include"Camera.h"
#include"TextCharacters.h"
#include"Math.h"
#include"Enum.h"
#include"Flag.h"
#include"Dx11.h"

using namespace OriginalMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pDevice"></param>
GameOverScene::GameOverScene(ID3D11Device* pDevice)
{
	m_NextGameState = GameState::GAMEOVER;

	m_pCamera = new Camera(pDevice);

	Vector3 pos  = { -0.275f,0.0f,0.0f };
	Vector2 size = { 0.07f,0.07f };

	m_pTextCharacters = new TextCharacters(pos, size, "GAME OVER", pDevice, TPS_WHITE);
}

/// <summary>
/// デストラクタ
/// </summary>
GameOverScene::~GameOverScene()
{
	if (m_pCamera         != nullptr) { delete m_pCamera;         m_pCamera = nullptr; }
	if (m_pTextCharacters != nullptr) { delete m_pTextCharacters; m_pTextCharacters = nullptr; }
}

/// <summary>
/// シーンの更新
/// </summary>
/// <param name="inputFlag"></param>
/// <param name="pDx11"></param>
/// <returns></returns>
GameState GameOverScene::UpDateScene(InputFlag inputFlag, Dx11* pDx11)
{
	m_NextGameState = GameState::GAMEOVER;

	UpDateGame(inputFlag,pDx11->m_pDevice);
	Draw(pDx11);

	return m_NextGameState;
}

/// <summary>
/// ゲームの更新
/// </summary>
/// <param name="inputFlag"></param>
/// <param name="pDevice"></param>
void GameOverScene::UpDateGame(InputFlag inputFlag, ID3D11Device* pDevice)
{
	if (inputFlag.Check(InputFlagCode::INPUT_RIGHT))
	{
		m_NextGameState = GameState::TITLE;
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="pDx11"></param>
void GameOverScene::Draw(Dx11* pDx11)
{
	m_pCamera->Shoot(pDx11->m_pDeviceContext, &pDx11->GetViewPort(), 0.0f);
	m_pTextCharacters->Render(pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
}