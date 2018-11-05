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
#include"Characters.h"
#include"DeathChecker.h"
#include"TitleScene.h"
#include"PlayScene.h"
#include"GameOverScene.h"
#include"ParameterScene.h"
#include"ResultScene.h"

GameManager::GameManager(HWND hwnd)
{
	m_pFlag     = new InputFlag();
	m_pDx11     = new Dx11();
	m_pDsound   = new Dsound(hwnd);
	m_GameState = GameState::TITLE;

	m_pDx11->Create(hwnd);
	m_pTitleScene    = new TitleScene(m_pDx11->m_pDevice);
	m_pParameterScene = new ParameterScene(m_pDx11->m_pDevice, m_GameState);
}

GameManager::~GameManager()
{
	if (m_pDx11           != nullptr) { delete m_pDx11;            m_pDx11           = nullptr; }
	if (m_pDsound         != nullptr) { delete m_pDsound;          m_pDsound         = nullptr; }
	if (m_pFlag           != nullptr) { delete m_pFlag;            m_pFlag           = nullptr; }
	if (m_pTitleScene     != nullptr) { delete m_pTitleScene;      m_pTitleScene     = nullptr; }
	if (m_pPlayScene      != nullptr) { delete m_pPlayScene;       m_pPlayScene      = nullptr; }
	if (m_pGameOverScene  != nullptr) { delete m_pGameOverScene;   m_pGameOverScene  = nullptr; }
	if (m_pParameterScene != nullptr) { delete m_pParameterScene;  m_pParameterScene = nullptr; }
	if (m_pResultScene    != nullptr) { delete m_pResultScene;     m_pResultScene    = nullptr; }
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
	m_pDx11->RenderStart();

	GameState oldGameState = m_GameState;

	m_pParameterScene->UpDateScene(*m_pFlag, m_pDx11);

	switch (m_GameState)
	{
	case GameState::TITLE:

		m_GameState = m_pTitleScene->UpDateScene(*m_pFlag, m_pDx11);

		if (m_GameState != oldGameState)
		{
			delete m_pTitleScene; 
			m_pTitleScene = nullptr;

			m_pPlayScene = new PlayScene(m_pDx11->m_pDevice);
			m_pResultScene = new ResultScene(m_pDx11->m_pDevice, m_pPlayScene->GetPlayer()->GetLife(),GameState::RESULT_RESTART);
		}

		break;

	case GameState::PLAY:

		m_GameState = m_pPlayScene->UpDateScene(*m_pFlag, m_pDx11);

		if (m_GameState != oldGameState)
		{
			switch (m_GameState)
			{
			case GameState::GAMEOVER:
				delete m_pPlayScene;
				m_pPlayScene = nullptr;

				m_pGameOverScene = new GameOverScene(m_pDx11->m_pDevice);
				break;

			case GameState::RESULT_RESTART:
				m_pResultScene = new ResultScene(m_pDx11->m_pDevice,m_pPlayScene->GetPlayer()->GetLife(),GameState::RESULT_RESTART);
				m_pPlayScene->ReStart(m_pDx11->m_pDevice);
				break;
			}
		}

		break;

	case GameState::GAMEOVER:

		m_GameState = m_pGameOverScene->UpDateScene(*m_pFlag, m_pDx11);

		if (m_GameState != oldGameState)
		{
			delete m_pGameOverScene;
			m_pGameOverScene = nullptr;

			m_pTitleScene = new TitleScene(m_pDx11->m_pDevice);
		}

		break;

	case GameState::RESULT_RESTART:
		m_GameState = m_pResultScene->UpDateScene(*m_pFlag, m_pDx11);

		if (m_GameState != oldGameState)
		{
			delete m_pResultScene;
			m_pResultScene = nullptr;
		}

		break;
	}

	m_pDx11->RenderEnd();
}