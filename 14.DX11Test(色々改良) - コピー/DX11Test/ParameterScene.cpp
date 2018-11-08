#include"ParameterScene.h"
#include"Flag.h"
#include"Timer.h"
#include"TextCharacters.h"
#include"Enum.h"
#include"Dx11.h"
#include"Image.h"
#include<string>

ParameterScene::ParameterScene(ID3D11Device* pDevice,GameState nowGameState)
{
	m_NextGameState = nowGameState;

	Vector3 pos  = { -0.8f,0.85f,0.0f };
	Vector2 size = { 0.07f,0.07f };
	m_pTextOfMARIO = new TextCharacters(pos, size, "MARIO", pDevice, TPS_WHITE);

	pos.y = 0.775f;
	m_pTextOfScoreNamber = new TextCharacters(pos, size, "000000", pDevice, TPS_WHITE);

	pos.x = 0.125f;
	pos.y = 0.85f;
	m_pTextOfWORLD = new TextCharacters(pos, size, "WORLD", pDevice, TPS_WHITE);

	pos.x = 0.19f;
	pos.y = 0.775f;
	m_pTextOfWorldNamber = new TextCharacters(pos, size, "1-1", pDevice, TPS_WHITE);

	pos.x = 0.6f;
	pos.y = 0.85f;
	m_pTextOfTIME  = new TextCharacters(pos, size, "TIME",  pDevice, TPS_WHITE);

	pos.x = 0.675f;
	pos.y = 0.775f;
	m_pTextOfTimeNamber = new TextCharacters(pos, size, "   ", pDevice, TPS_WHITE);

	pos.x = -0.275f;
	m_pImageOfCoin = new Image(pos, size, pDevice, L"Texture/COIN1.png");

	pos.x = -0.225f;
	m_pTextOfCoinNamber = new TextCharacters(pos, size, "*00", pDevice, TPS_WHITE);

	m_pTimer = new Timer();
	m_pTimer->SetTimeRemaining(110);
	int time = m_pTimer->CountStart();

	m_pTextOfTimeNamber->ChangeText(std::to_string(time), pDevice);
}

ParameterScene::~ParameterScene()
{
	if (m_pTimer             != nullptr) { delete m_pTimer;             m_pTimer             = nullptr; }
	if (m_pTextOfMARIO       != nullptr) { delete m_pTextOfMARIO;       m_pTextOfMARIO       = nullptr; }
	if (m_pTextOfTIME        != nullptr) { delete m_pTextOfTIME;        m_pTextOfTIME        = nullptr; }
	if (m_pTextOfWORLD       != nullptr) { delete m_pTextOfWORLD;       m_pTextOfWORLD       = nullptr; }
	if (m_pTextOfTimeNamber  != nullptr) { delete m_pTextOfTimeNamber;  m_pTextOfTimeNamber  = nullptr; }
	if (m_pImageOfCoin       != nullptr) { delete m_pImageOfCoin;       m_pImageOfCoin       = nullptr; }
	if (m_pTextOfCoinNamber  != nullptr) { delete m_pTextOfCoinNamber;  m_pTextOfCoinNamber  = nullptr; }
	if (m_pTextOfScoreNamber != nullptr) { delete m_pTextOfScoreNamber; m_pTextOfScoreNamber = nullptr; }
	if (m_pTextOfWorldNamber != nullptr) { delete m_pTextOfWorldNamber; m_pTextOfWorldNamber = nullptr; }
}

GameState ParameterScene::UpDateScene(InputFlag inputFlag, Dx11* pDx11)
{
	UINT time = m_pTimer->GetCount();
	if (time < 100)
	{
		m_pTextOfTimeNamber->ChangeText("0" + std::to_string(time), pDx11->m_pDevice);
	}
	else
	{
		m_pTextOfTimeNamber->ChangeText(std::to_string(time), pDx11->m_pDevice);
	}
	

	UpDateGame(inputFlag,pDx11->m_pDevice);
	Draw(pDx11);

	return m_NextGameState;
}

void ParameterScene::UpDateGame(InputFlag inputFlag, ID3D11Device* pDevice)
{
	
}

void ParameterScene::Draw(Dx11* pDx11)
{
	m_pTextOfMARIO      ->Render       (pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
	m_pTextOfTIME       ->Render       (pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
	m_pTextOfWORLD      ->Render       (pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
	m_pTextOfTimeNamber ->Render       (pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
	m_pTextOfScoreNamber->Render       (pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
	m_pTextOfCoinNamber ->Render       (pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
	m_pImageOfCoin      ->ThisObjRender(pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
	m_pTextOfWorldNamber->Render       (pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
}

void ParameterScene::ChangeWorldNamber(int worldNamber, int stageNamber,ID3D11Device* pDevice)
{
	std::string filePas = std::to_string(worldNamber) + "-" + std::to_string(stageNamber);  //ステージのファイルパス

	m_pTextOfWorldNamber->ChangeText(filePas,pDevice);
}