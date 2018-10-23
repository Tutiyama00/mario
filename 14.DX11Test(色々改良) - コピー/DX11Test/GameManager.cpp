#include<Windows.h>
#include"GameManager.h"
#include"Flag.h"
#include"Enum.h"
#include"Player.h"
#include"Sound.h"
#include"Dx11.h"
#include"Stage.h"
#include"Block.h"
#include"Camera.h"
#include"CharacterManager.h"
#include"Characters.h"

GameManager::GameManager(HWND hwnd)
{
	m_pFlag     = new InputFlag();
	m_pDx11     = new Dx11();
	m_pDsound   = new Dsound(hwnd);
	m_pStage    = new Stage("STAGE_1.txt", hwnd);
	m_GameState = GameState::TITLE;

	m_pDx11->Create(hwnd);
	m_pCamera           = new Camera(m_pDx11->m_pDevice);
	m_pCharacterManager = new CharacterManager(m_pStage->m_pStageDataArray, m_pStage->GetStageHeight(), m_pStage->GetStageWidth(), m_pDx11->m_pDevice);
}

GameManager::~GameManager()
{
	if (m_pDx11     != nullptr) { delete m_pDx11;     m_pDx11     = nullptr; }
	if (m_pDsound   != nullptr) { delete m_pDsound;   m_pDsound   = nullptr; }
	if (m_pFlag     != nullptr) { delete m_pFlag;     m_pFlag     = nullptr; }
}

void GameManager::GetInput()
{
	m_pFlag->AllReSet();

	if (GetAsyncKeyState(VK_SPACE)) { m_pFlag->Set(InputFlagCode::INPUT_SPACE); }
	if (GetAsyncKeyState(VK_LEFT))  { m_pFlag->Set(InputFlagCode::INPUT_LEFT);  }
	if (GetAsyncKeyState(VK_RIGHT)) { m_pFlag->Set(InputFlagCode::INPUT_RIGHT); }
}

void GameManager::UpDateGame()
{
	switch (m_GameState)
	{
	case GameState::TITLE:
		if (m_pFlag->Check(InputFlagCode::INPUT_SPACE))
		{
			m_GameState = GameState::PLAY;
		}
		break;

	case GameState::PLAY:
	
		for (int i = 0; i < m_pCharacterManager->m_pCharacters_Block->m_ObjectVector.size(); i++)
		{
			m_pCharacterManager->m_pCharacters_Block->m_ObjectVector[i]->CheckPlayer(m_pCharacterManager->m_pPlayer, m_pFlag);
		}

		m_pCharacterManager->m_pPlayer->Move(m_pFlag);
		break;
	}
}

void GameManager::Draw()
{
	m_pDx11->Render(m_pCamera,m_GameState,m_pCharacterManager);
}