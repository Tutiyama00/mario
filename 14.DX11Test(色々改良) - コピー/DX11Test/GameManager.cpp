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

/*�R���X�g���N�^*/
GameManager::GameManager(HWND hwnd)
{
	m_pFlag     = new InputFlag();
	m_pDx11     = new Dx11();
	m_pDsound   = new Dsound(hwnd);
	m_GameState = GameState::TITLE;

	m_pDx11->Create(hwnd);
	m_pTitleScene     = new TitleScene    (m_pDx11->m_pDevice);
	m_pParameterScene = new ParameterScene(m_pDx11->m_pDevice, m_GameState);
	m_pPlayScene      = new PlayScene     (m_pDx11->m_pDevice);
	m_pResultScene    = new ResultScene   (m_pDx11->m_pDevice, m_pPlayScene->GetPlayer()->GetSTART_LIFE());
	m_pGameOverScene  = new GameOverScene (m_pDx11->m_pDevice);
}

/*�f�X�g���N�^*/
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

/*���͂̎擾*/
void GameManager::InputGet()
{
	m_pFlag->AllReSet();

	if (GetAsyncKeyState(VK_SPACE)) { m_pFlag->Set(InputFlagCode::INPUT_SPACE); }
	if (GetAsyncKeyState(VK_LEFT))  { m_pFlag->Set(InputFlagCode::INPUT_LEFT);  }
	if (GetAsyncKeyState(VK_RIGHT)) { m_pFlag->Set(InputFlagCode::INPUT_RIGHT); }
}

/*�Q�[���̍X�V*/
void GameManager::UpDateGame()
{
	/*�����_�����O���J�n��Ԃɂ���*/
	m_pDx11->RenderStart();

	/*��r�p�ɍ��̃Q�[���X�e�[�g��ۑ�����*/
	GameState oldGameState = m_GameState;

	/*�p�����[�^�[�V�[���̍X�V*/
	m_pParameterScene->UpDateScene(*m_pFlag, m_pDx11);

	/*�X�e�[�g�ɍ��킹�āA�Ή������V�[���̍X�V*/
	switch (m_GameState)
	{
    /*�^�C�g���V�[��*/
	case GameState::TITLE:

		/*�V�[���̍X�V*/
		m_GameState = m_pTitleScene->UpDateScene(*m_pFlag, m_pDx11);

		break;

	/*�v���C�V�[��*/
	case GameState::PLAY:

		/*�V�[���̍X�V*/
		m_GameState = m_pPlayScene->UpDateScene(*m_pFlag, m_pDx11);

		/*�X�V�̌��ʃQ�[���X�e�[�g���ω����Ă��邩*/
		if (m_GameState != oldGameState)
		{
			/*�ω����Ă����ꍇ
			 *�ω���̃V�[���ɂ���Ă�邱�Ƃ��ς��*/
			switch (m_GameState)
			{
			case GameState::RESULT:
				m_pResultScene->ChangeWorldNamber(m_pPlayScene->GetNowWorldLevel(), m_pPlayScene->GetNowStageLevel(), m_pDx11->m_pDevice);
				m_pParameterScene->ChangeWorldNamber(m_pPlayScene->GetNowWorldLevel(), m_pPlayScene->GetNowStageLevel(), m_pDx11->m_pDevice);
				m_pResultScene->ChangeMarioLife(m_pPlayScene->GetPlayer()->GetLife(), m_pDx11->m_pDevice);
				break;
			}
		}

		break;

	/*�Q�[���I�[�o�[�V�[��*/
	case GameState::GAMEOVER:

		/*�V�[���̍X�V*/
		m_GameState = m_pGameOverScene->UpDateScene(*m_pFlag, m_pDx11);

		/*�X�V�̌��ʃQ�[���X�e�[�g���ω����Ă��邩*/
		if (m_GameState != oldGameState)
		{
			m_pResultScene->ChangeWorldNamber(1, 1, m_pDx11->m_pDevice);
			m_pResultScene->ChangeMarioLife(m_pPlayScene->GetPlayer()->GetSTART_LIFE(), m_pDx11->m_pDevice);
			m_pParameterScene->ChangeWorldNamber(1, 1,m_pDx11->m_pDevice);
		}

		break;

	/*���U���g�V�[��*/
	case GameState::RESULT:

		/*�V�[���̍X�V*/
		m_GameState = m_pResultScene->UpDateScene(*m_pFlag, m_pDx11);

		break;
	}

	/*�����_�����O���I������*/
	m_pDx11->RenderEnd();
}


//����������