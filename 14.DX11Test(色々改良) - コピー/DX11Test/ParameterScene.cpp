#include"ParameterScene.h"
#include"Flag.h"
#include"Timer.h"
#include"TextCharacters.h"
#include"Enum.h"
#include"Dx11.h"
#include"Image.h"
#include<string>
#include"GameManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="nowGameState">���݂̃Q�[���X�e�[�g</param>
ParameterScene::ParameterScene(GameState nowGameState)
{
	m_NextGameState = nowGameState;

	Vector3 pos  = { -0.8f,0.85f,0.0f };
	Vector2 size = { 0.07f,0.07f };
	m_pTextOfMARIO = new TextCharacters(pos, size, "MARIO", TPS_WHITE);

	pos.y = 0.775f;
	m_pTextOfScoreNamber = new TextCharacters(pos, size, "000000", TPS_WHITE);

	pos.x = 0.125f;
	pos.y = 0.85f;
	m_pTextOfWORLD = new TextCharacters(pos, size, "WORLD", TPS_WHITE);

	pos.x = 0.19f;
	pos.y = 0.775f;
	m_pTextOfWorldNamber = new TextCharacters(pos, size, "1-1", TPS_WHITE);

	pos.x = 0.6f;
	pos.y = 0.85f;
	m_pTextOfTIME  = new TextCharacters(pos, size, "TIME", TPS_WHITE);

	pos.x = 0.675f;
	pos.y = 0.775f;
	m_pTextOfTimeNamber = new TextCharacters(pos, size, "   ", TPS_WHITE);

	pos.x = -0.275f;
	m_pImageOfCoin = new Image(pos, size, L"Texture/COIN1.png");

	pos.x = -0.225f;
	m_pTextOfCoinNamber = new TextCharacters(pos, size, "*00", TPS_WHITE);

	m_pTimer = new Timer();
	//m_pTimer->SetTimeRemaining(110);
	//int time = m_pTimer->CountStart();

	//m_pTextOfTimeNamber->ChangeText(std::to_string(time));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
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

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <param name="inputFlag"></param>
/// <returns>���̃Q�[���X�e�[�g</returns>
GameState ParameterScene::UpDateScene(InputFlag inputFlag)
{
	UpDateGame(inputFlag);
	Draw();

	return m_NextGameState;
}

void ParameterScene::UpDateGame(InputFlag inputFlag)
{
	/* �Q�[���X�e�[�g���v���C�������� */
	if(GameManager::Instance()->GetGameState() == GameState::PLAY)
	{
		/* time���擾 */
		UINT time = m_pTimer->GetCount();
		if (time < 100 && time > 9)
		{
			/* �Q���̏ꍇ */
			m_pTextOfTimeNamber->ChangeText("0" + std::to_string(time));
		}
		else if (time <= 9)
		{
			/* �P���̏ꍇ */
			m_pTextOfTimeNamber->ChangeText("00" + std::to_string(time));
		}
		else
		{
			/* �R���̏ꍇ */
			m_pTextOfTimeNamber->ChangeText(std::to_string(time));
		}
	}
	else
	{
		/* �v���C��Ԃł͂Ȃ�������A�^�C����\�����Ȃ�*/
		m_pTextOfTimeNamber->ChangeText("   ");
	}
}

/// <summary>
/// �`��
/// </summary>
void ParameterScene::Draw()
{
	m_pTextOfMARIO      ->Render       ();
	m_pTextOfTIME       ->Render       ();
	m_pTextOfWORLD      ->Render       ();
	m_pTextOfTimeNamber ->Render       ();
	m_pTextOfScoreNamber->Render       ();
	m_pTextOfCoinNamber ->Render       ();
	m_pImageOfCoin      ->ThisObjRender();
	m_pTextOfWorldNamber->Render       ();
}

/// <summary>
/// �X�e�[�W�ԍ��̕\����ς���
/// </summary>
/// <param name="worldNamber">�ω���̃��[���h�ԍ�</param>
/// <param name="stageNamber">�ω���̃X�e�[�W�ԍ�</param>
void ParameterScene::ChangeWorldNamber(int worldNamber, int stageNamber)
{
	std::string filePas = std::to_string(worldNamber) + "-" + std::to_string(stageNamber);  //�X�e�[�W�̃t�@�C���p�X

	m_pTextOfWorldNamber->ChangeText(filePas);
}

void ParameterScene::StopTimer()
{
	m_pTimer->CountStop();
}

void ParameterScene::StartTimer()
{
	m_pTimer->CountStart();
}

void ParameterScene::SetTimer(DWORD time)
{
	m_pTimer->SetTimeRemaining(time);
}