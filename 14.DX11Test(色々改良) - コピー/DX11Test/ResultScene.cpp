#include"ResultScene.h"
#include"Image.h"
#include"Enum.h"
#include"Flag.h"
#include"Dx11.h"
#include"TextCharacters.h"

ResultScene::ResultScene(UINT playerLife)
{
	m_NextGameState = GameState::RESULT;

	Vector3 pos  = { -0.14f,0.0f,0.0f };
	Vector2 size = { 0.1f,0.1f };

	m_pImageOfMario = new Image(pos, size, L"Texture/Mario.png");

	pos.x  = 0.0f;
	size.x = size.y = 0.07f;
	m_pTextOfMarioLife = new TextCharacters(pos, size, "*  " + std::to_string(playerLife), TPS_WHITE);

	pos.x  = -0.25f;
	pos.y  = 0.2f;
	size.x = size.y = 0.07f;
	m_pTextOfWORLD = new TextCharacters(pos, size, "WORLD", TPS_WHITE);

	pos.x = 0.15f;
	m_pTextOfWorldNamber = new TextCharacters(pos, size, "1-1", TPS_WHITE);
}

ResultScene::~ResultScene()
{
	if (m_pImageOfMario      != nullptr) { delete m_pImageOfMario;      m_pImageOfMario      = nullptr; }
	if (m_pTextOfWORLD       != nullptr) { delete m_pTextOfWORLD;       m_pTextOfWORLD       = nullptr; }
	if (m_pTextOfMarioLife   != nullptr) { delete m_pTextOfMarioLife;   m_pTextOfMarioLife   = nullptr; }
	if (m_pTextOfWorldNamber != nullptr) { delete m_pTextOfWorldNamber; m_pTextOfWorldNamber = nullptr; }
}

GameState ResultScene::UpDateScene(InputFlag inputFlag)
{
	m_NextGameState = GameState::RESULT;

	UpDateGame(inputFlag);
	Draw();

	return m_NextGameState;
}

void ResultScene::UpDateGame(InputFlag inputFlag)
{
	if (inputFlag.Check(InputFlagCode::INPUT_LEFT))
	{
		m_NextGameState = GameState::PLAY;
	}
}

void ResultScene::Draw()
{
	m_pImageOfMario     ->ThisObjRender();
	m_pTextOfWORLD      ->Render       ();
	m_pTextOfMarioLife  ->Render       ();
	m_pTextOfWorldNamber->Render       ();
}

void ResultScene::ChangeWorldNamber(int worldNamber, int stageNamber)
{
	std::string filePas = std::to_string(worldNamber) + "-" + std::to_string(stageNamber);  //ステージのファイルパス

	m_pTextOfWorldNamber->ChangeText(filePas);
}

void ResultScene::ChangeMarioLife(UINT playerLife)
{
	m_pTextOfMarioLife->ChangeText("*  " + std::to_string(playerLife));
}