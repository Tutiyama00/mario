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
#include"DeathChecker.h"
#include"TitleScene.h"
#include"PlayScene.h"

GameManager::GameManager(HWND hwnd)
{
	m_pFlag     = new InputFlag();
	m_pDx11     = new Dx11();
	m_pDsound   = new Dsound(hwnd);
	m_GameState = GameState::TITLE;

	m_pDx11->Create(hwnd);
	m_pTitleScene = new TitleScene(m_pDx11->m_pDevice);
	m_pPlayScene = new PlayScene(m_pDx11->m_pDevice);
}

GameManager::~GameManager()
{
	if (m_pDx11       != nullptr) { delete m_pDx11;        m_pDx11       = nullptr; }
	if (m_pDsound     != nullptr) { delete m_pDsound;      m_pDsound     = nullptr; }
	if (m_pFlag       != nullptr) { delete m_pFlag;        m_pFlag       = nullptr; }
	if (m_pTitleScene != nullptr) { delete m_pTitleScene;  m_pTitleScene = nullptr; }
	if (m_pPlayScene  != nullptr) { delete m_pPlayScene;   m_pPlayScene  = nullptr; }
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

		m_GameState = m_pTitleScene->UpDateScene(*m_pFlag, m_pDx11);

		break;

	case GameState::PLAY:

		m_GameState = m_pPlayScene->UpDateScene(*m_pFlag, m_pDx11);

		break;

	case GameState::GAMEOVER:
		break;

	case GameState::GAMECLEAR:
		break;
	}
}

void GameManager::Draw()
{
	
}