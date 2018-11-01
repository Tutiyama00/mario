#include"ParameterScene.h"
#include"Flag.h"
#include"Timer.h"
#include"TextCharacters.h"
#include"Enum.h"
#include"Dx11.h"

ParameterScene::ParameterScene(ID3D11Device* pDevice,GameState nowGameState)
{
	m_NextGameState = nowGameState;

	Vector3 pos  = { -0.8f,0.85f,0.0f };
	Vector2 size = { 0.07f,0.07f };

	m_pTimer       = new Timer();
	m_pTextOfMARIO = new TextCharacters(pos, size, "MARIO", pDevice, TPS_WHITE);

	pos.x = 0.125f;
	m_pTextOfWORLD = new TextCharacters(pos, size, "WORLD", pDevice, TPS_WHITE);

	pos.x = 0.6f;
	m_pTextOfTIME  = new TextCharacters(pos, size, "TIME",  pDevice, TPS_WHITE);
}

ParameterScene::~ParameterScene()
{
	if (m_pTimer       != nullptr) { delete m_pTimer;       m_pTimer       = nullptr; }
	if (m_pTextOfMARIO != nullptr) { delete m_pTextOfMARIO; m_pTextOfMARIO = nullptr; }
	if (m_pTextOfTIME  != nullptr) { delete m_pTextOfTIME;  m_pTextOfTIME  = nullptr; }
	if (m_pTextOfWORLD != nullptr) { delete m_pTextOfWORLD; m_pTextOfWORLD = nullptr; }
}

GameState ParameterScene::UpDateScene(InputFlag inputFlag, Dx11* pDx11)
{
	UpDateGame(inputFlag);
	Draw(pDx11);

	return m_NextGameState;
}

void ParameterScene::UpDateGame(InputFlag inputFlag)
{

}

void ParameterScene::Draw(Dx11* pDx11)
{
	m_pTextOfMARIO->Render(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	m_pTextOfTIME ->Render(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	m_pTextOfWORLD->Render(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
}