#include"GameOverScene.h"
#include"Camera.h"
#include"TextCharacters.h"
#include"Math.h"
#include"Enum.h"
#include"Flag.h"
#include"Dx11.h"

using namespace OriginalMath;

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
GameOverScene::~GameOverScene()
{
	if (m_pCamera         != nullptr) { delete m_pCamera;         m_pCamera = nullptr; }
	if (m_pTextCharacters != nullptr) { delete m_pTextCharacters; m_pTextCharacters = nullptr; }
}

/// <summary>
/// �V�[���̍X�V
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
/// �Q�[���̍X�V
/// </summary>
void GameOverScene::UpDateGame(InputFlag inputFlag)
{
	if (inputFlag.Check(InputFlagCode::INPUT_RIGHT))
	{
		m_NextGameState = GameState::TITLE;
	}
}

/// <summary>
/// �`��
/// </summary>
void GameOverScene::Draw()
{
	m_pCamera->Shoot(0.0f);
	m_pTextCharacters->Render();
}