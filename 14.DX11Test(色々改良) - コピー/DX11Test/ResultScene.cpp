#include"ResultScene.h"
#include"Image.h"
#include"Enum.h"
#include"Flag.h"
#include"Dx11.h"
#include"TextCharacters.h"

ResultScene::ResultScene(ID3D11Device* pDevice, UINT playerLife,GameState gameState)
{
	m_NextGameState = gameState;

	Vector3 pos = { -0.14f,0.0f,0.0f };
	Vector2 size = { 0.1f,0.1f };

	m_pImageOfMario = new Image(pos, size, pDevice, L"Texture/Mario.png");

	pos.x = 0.0f;
	size.x = size.y = 0.07f;
	m_pTextOfMarioLife = new TextCharacters(pos, size, "*  " + std::to_string(playerLife) , pDevice, TPS_WHITE);

	pos.x = -0.25f;
	pos.y = 0.2f;
	size.x = size.y = 0.07f;
	m_pTextOfWORLD = new TextCharacters(pos, size, "WORLD", pDevice, TPS_WHITE);
}

ResultScene::~ResultScene()
{
	if (m_pImageOfMario != nullptr) { delete m_pImageOfMario; m_pImageOfMario = nullptr; }
	if (m_pTextOfWORLD != nullptr) { delete m_pTextOfWORLD; m_pTextOfWORLD = nullptr; }
	if (m_pTextOfMarioLife != nullptr) { delete m_pTextOfMarioLife; m_pTextOfMarioLife = nullptr; }
}

GameState ResultScene::UpDateScene(InputFlag inputFlag, Dx11* pDx11)
{
	UpDateGame(inputFlag);
	Draw(pDx11);

	return m_NextGameState;
}

void ResultScene::UpDateGame(InputFlag inputFlag)
{
	if (inputFlag.Check(InputFlagCode::INPUT_LEFT))
	{
		m_NextGameState = GameState::PLAY;
	}
}

void ResultScene::Draw(Dx11* pDx11)
{
	m_pImageOfMario->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	m_pTextOfWORLD->Render(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	m_pTextOfMarioLife->Render(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
}