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
GameOverScene::GameOverScene()
{
	m_NextGameState = GameState::GAMEOVER;

	m_pCamera = new Camera();

	Vector3 pos  = { -0.275f,0.0f,0.0f };
	Vector2 size = { 0.07f,0.07f };

	m_pTextCharacters = new TextCharacters(pos, size, "GAME OVER", TPS_WHITE);
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
/// <returns></returns>
GameState GameOverScene::UpDateScene(InputFlag inputFlag)
{
	m_NextGameState = GameState::GAMEOVER;

	UpDateGame(inputFlag);
	Draw();

	return m_NextGameState;
}

/// <summary>
/// ゲームの更新
/// </summary>
void GameOverScene::UpDateGame(InputFlag inputFlag)
{
	/* 指定したフレーム数だけシーンを継続する */
	if (m_FlameCount >= M_CHANGE_FLAME_COUNT)
	{
		/* フレーム数カウントのリセット */
		m_FlameCount = 0;
		/* シーンの変更 */
		m_NextGameState = GameState::TITLE;
	}
	else
	{
		/* フレーム数カウント */
		m_FlameCount++;
	}
}

/// <summary>
/// 描画
/// </summary>
void GameOverScene::Draw()
{
	m_pCamera->Shoot(0.0f);
	m_pTextCharacters->Render();
}