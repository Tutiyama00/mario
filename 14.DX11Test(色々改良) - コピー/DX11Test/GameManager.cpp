#include<Windows.h>
#include"GameManager.h"
#include"Flag.h"
#include"Enum.h"
#include"Player.h"
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
#include"SoundData.h"
#include<dsound.h>
#include"ScoreManager.h"

/*�f�X�g���N�^*/
GameManager::~GameManager()
{
	if (m_pFlag           != nullptr) { delete m_pFlag;            m_pFlag           = nullptr; }
	if (m_pTitleScene     != nullptr) { delete m_pTitleScene;      m_pTitleScene     = nullptr; }
	if (m_pPlayScene      != nullptr) { delete m_pPlayScene;       m_pPlayScene      = nullptr; }
	if (m_pGameOverScene  != nullptr) { delete m_pGameOverScene;   m_pGameOverScene  = nullptr; }
	if (m_pParameterScene != nullptr) { delete m_pParameterScene;  m_pParameterScene = nullptr; }
	if (m_pResultScene    != nullptr) { delete m_pResultScene;     m_pResultScene    = nullptr; }
}

/// <summary>
/// �������֐�
/// </summary>
/// <param name="hwnd"></param>
void GameManager::Initialize(HWND hwnd)
{
	if (!m_InitializedFlag)
	{
		/* Dx11�̏����� */
		Dx11::Instance()->Initialize(hwnd);

		/* TextureData�̏����� */
		TextureData::Instance()->Initialize();

		/* SoundData�̏����� */
		SoundData::Instance()->Initialize(hwnd);

		m_pFlag     = new InputFlag();
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
/// ���͂̎擾
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
/// �Q�[���̍X�V
/// </summary>
void GameManager::UpDateGame()
{
	if (!m_InitializedFlag) { MessageBox(NULL, "NotInitialize GameManager", "ERROR", MB_OK); return; }

	/*�����_�����O���J�n��Ԃɂ���*/
	Dx11::Instance()->RenderStart();

	/*��r�p�ɍ��̃Q�[���X�e�[�g��ۑ�����*/
	GameState oldGameState = m_GameState;

	/*�p�����[�^�[�V�[���̍X�V*/
	m_pParameterScene->UpDateScene(*m_pFlag);

	/*�X�e�[�g�ɍ��킹�āA�Ή������V�[���̍X�V*/
	switch (m_GameState)
	{
    /*�^�C�g���V�[��*/
	case GameState::TITLE:

		/*�V�[���̍X�V*/
		m_GameState = m_pTitleScene->UpDateScene(*m_pFlag);

		/*�X�V�̌��ʃQ�[���X�e�[�g���ω����Ă��邩*/
		if (m_GameState != oldGameState)
		{
			ScoreManager::Instance()->ScoreReSet();
			m_pParameterScene->SetTimer(m_pPlayScene->GetStageTime());
			m_pParameterScene->StartTimer();
		}

		break;

	/*�v���C�V�[��*/
	case GameState::PLAY:

		/*�V�[���̍X�V*/
		m_GameState = m_pPlayScene->UpDateScene(*m_pFlag);

		/*�X�V�̌��ʃQ�[���X�e�[�g���ω����Ă��邩*/
		if (m_GameState != oldGameState)
		{
			SoundData::Instance()->GetSTANDARD_BGMsoundBuffer()->Stop();  //�Đ����~�߂�

			/*�ω����Ă����ꍇ
			 *�ω���̃V�[���ɂ���Ă�邱�Ƃ��ς��*/
			switch (m_GameState)
			{
			case GameState::RESULT:
				m_pResultScene    ->ChangeWorldNamber(m_pPlayScene->GetNowWorldLevel(), m_pPlayScene->GetNowStageLevel());
				m_pParameterScene ->ChangeWorldNamber(m_pPlayScene->GetNowWorldLevel(), m_pPlayScene->GetNowStageLevel());	
				m_pResultScene    ->ChangeMarioLife(m_pPlayScene->GetPlayer()->GetLife());
				break;

			case GameState::GAMEOVER:
				SoundData::Instance()->GetGAME_OVERsoundBuffer()->SetCurrentPosition(0);
				SoundData::Instance()->GetGAME_OVERsoundBuffer()->Play(0,0,0);
				break;
			}
		}
		else
		{
			/*�b�����O�ɂȂ�����^�C���A�b�v�Ńv���C���[���E��*/
			if (m_pParameterScene->GetNowTime() <= 0)
			{
				m_pPlayScene->KillPlayer();
			}
		}

		break;

	/*�Q�[���I�[�o�[�V�[��*/
	case GameState::GAMEOVER:

		/*�V�[���̍X�V*/
		m_GameState = m_pGameOverScene->UpDateScene(*m_pFlag);

		/*�X�V�̌��ʃQ�[���X�e�[�g���ω����Ă��邩*/
		if (m_GameState != oldGameState)
		{
			m_pResultScene->ChangeWorldNamber(1, 1);
			m_pResultScene->ChangeMarioLife(m_pPlayScene->GetPlayer()->GetSTART_LIFE());
			m_pParameterScene->ChangeWorldNamber(1, 1);
		}

		break;

	/*���U���g�V�[��*/
	case GameState::RESULT:

		/*�V�[���̍X�V*/
		m_GameState = m_pResultScene->UpDateScene(*m_pFlag);

		/*�X�V�̌��ʃQ�[���X�e�[�g���ω����Ă��邩*/
		if (m_GameState != oldGameState)
		{
			SoundData::Instance()->GetSTANDARD_BGMsoundBuffer()->SetCurrentPosition(0);       //�Đ��ʒu��擪�ɖ߂�
			SoundData::Instance()->GetSTANDARD_BGMsoundBuffer()->Play(0,0, DSBPLAY_LOOPING);  //�Đ�����

			m_pParameterScene->SetTimer(m_pPlayScene->GetStageTime());
			m_pParameterScene->StartTimer();
		}

		break;
	}

	/*�����_�����O���I������*/
	Dx11::Instance()->RenderEnd();
}