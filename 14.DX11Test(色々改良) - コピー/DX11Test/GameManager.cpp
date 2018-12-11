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
#include"TitleScene.h"
#include"PlayScene.h"
#include"GameOverScene.h"
#include"ParameterScene.h"
#include"ResultScene.h"
#include"TextureData.h"

/*デストラクタ*/
GameManager::~GameManager()
{
	if (m_pDsound         != nullptr) { delete m_pDsound;          m_pDsound         = nullptr; }
	if (m_pFlag           != nullptr) { delete m_pFlag;            m_pFlag           = nullptr; }
	if (m_pTitleScene     != nullptr) { delete m_pTitleScene;      m_pTitleScene     = nullptr; }
	if (m_pPlayScene      != nullptr) { delete m_pPlayScene;       m_pPlayScene      = nullptr; }
	if (m_pGameOverScene  != nullptr) { delete m_pGameOverScene;   m_pGameOverScene  = nullptr; }
	if (m_pParameterScene != nullptr) { delete m_pParameterScene;  m_pParameterScene = nullptr; }
	if (m_pResultScene    != nullptr) { delete m_pResultScene;     m_pResultScene    = nullptr; }
}

/// <summary>
/// 初期化関数
/// </summary>
/// <param name="hwnd"></param>
void GameManager::Initialize(HWND hwnd)
{
	if (!m_InitializedFlag)
	{
		/* Dx11の初期化 */
		Dx11::Instance()->Initialize(hwnd);

		TextureData::Instance()->Initialize();

		m_pFlag     = new InputFlag();
		m_pDsound   = new Dsound(hwnd);
		m_GameState = GameState::TITLE;

		m_pTitleScene     = new TitleScene();
		m_pParameterScene = new ParameterScene(m_GameState);
		m_pPlayScene      = new PlayScene();
		m_pResultScene    = new ResultScene(m_pPlayScene->GetPlayer()->GetSTART_LIFE());
		m_pGameOverScene  = new GameOverScene();

		m_InitializedFlag = true;
	}
}

/// <summary>
/// 入力の取得
/// </summary>
void GameManager::InputGet()
{
	if (!m_InitializedFlag) { MessageBox(NULL, "NotInitialize GameManager", "ERROR", MB_OK); return; }

	m_pFlag->AllReSet();

	if (GetAsyncKeyState(VK_SPACE)) { m_pFlag->Set(InputFlagCode::INPUT_SPACE); }
	if (GetAsyncKeyState(VK_LEFT))  { m_pFlag->Set(InputFlagCode::INPUT_LEFT);  }
	if (GetAsyncKeyState(VK_RIGHT)) { m_pFlag->Set(InputFlagCode::INPUT_RIGHT); }
}

/// <summary>
/// ゲームの更新
/// </summary>
void GameManager::UpDateGame()
{
	if (!m_InitializedFlag) { MessageBox(NULL, "NotInitialize GameManager", "ERROR", MB_OK); return; }

	/*レンダリングを開始状態にする*/
	Dx11::Instance()->RenderStart();

	/*比較用に今のゲームステートを保存する*/
	GameState oldGameState = m_GameState;

	/*パラメーターシーンの更新*/
	m_pParameterScene->UpDateScene(*m_pFlag);

	/*ステートに合わせて、対応したシーンの更新*/
	switch (m_GameState)
	{
    /*タイトルシーン*/
	case GameState::TITLE:

		/*シーンの更新*/
		m_GameState = m_pTitleScene->UpDateScene(*m_pFlag);

		/*更新の結果ゲームステートが変化しているか*/
		if (m_GameState != oldGameState)
		{
			m_pParameterScene->SetTimer(m_pPlayScene->GetStageTime());
			m_pParameterScene->StartTimer();
		}

		break;

	/*プレイシーン*/
	case GameState::PLAY:

		/*シーンの更新*/
		m_GameState = m_pPlayScene->UpDateScene(*m_pFlag);

		if (m_pParameterScene->GetNowTime() <= 0)
		{
			m_pPlayScene->KillPlayer();
		}

		/*更新の結果ゲームステートが変化しているか*/
		if (m_GameState != oldGameState)
		{
			/*変化していた場合
			 *変化先のシーンによってやることが変わる*/
			switch (m_GameState)
			{
			case GameState::RESULT:
				m_pResultScene->ChangeWorldNamber(m_pPlayScene->GetNowWorldLevel(), m_pPlayScene->GetNowStageLevel());
				m_pParameterScene->ChangeWorldNamber(m_pPlayScene->GetNowWorldLevel(), m_pPlayScene->GetNowStageLevel());	
				m_pResultScene->ChangeMarioLife(m_pPlayScene->GetPlayer()->GetLife());
				break;
			}
		}

		break;

	/*ゲームオーバーシーン*/
	case GameState::GAMEOVER:

		/*シーンの更新*/
		m_GameState = m_pGameOverScene->UpDateScene(*m_pFlag);

		/*更新の結果ゲームステートが変化しているか*/
		if (m_GameState != oldGameState)
		{
			m_pResultScene->ChangeWorldNamber(1, 1);
			m_pResultScene->ChangeMarioLife(m_pPlayScene->GetPlayer()->GetSTART_LIFE());
			m_pParameterScene->ChangeWorldNamber(1, 1);
		}

		break;

	/*リザルトシーン*/
	case GameState::RESULT:

		/*シーンの更新*/
		m_GameState = m_pResultScene->UpDateScene(*m_pFlag);

		/*更新の結果ゲームステートが変化しているか*/
		if (m_GameState != oldGameState)
		{
			m_pParameterScene->SetTimer(m_pPlayScene->GetStageTime());
			m_pParameterScene->StartTimer();
		}

		break;
	}

	/*レンダリングを終了する*/
	Dx11::Instance()->RenderEnd();
}