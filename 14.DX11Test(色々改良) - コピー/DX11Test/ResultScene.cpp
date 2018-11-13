#include"ResultScene.h"
#include"Image.h"
#include"Enum.h"
#include"Flag.h"
#include"Dx11.h"
#include"TextCharacters.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playerLife">�����v���C���[�c�@</param>
ResultScene::ResultScene(UINT playerLife)
{
	m_NextGameState = GameState::RESULT;

	Vector3 pos  = { -0.14f,0.0f,0.0f };
	Vector2 size = { 0.1f,0.1f };

	m_pImageOfMario = new Image(pos, size, L"Texture/Mario.png");

	pos.x  = 0.0f;
	size.x = size.y = 0.07f;
	m_pTextOfMarioLife = new TextCharacters(pos, size, "*  " + std::to_string(playerLife), TPS_WHITE);

	pos.x  = -0.25f;
	pos.y  = 0.2f;
	size.x = size.y = 0.07f;
	m_pTextOfWORLD = new TextCharacters(pos, size, "WORLD", TPS_WHITE);

	pos.x = 0.15f;
	m_pTextOfWorldNamber = new TextCharacters(pos, size, "1-1", TPS_WHITE);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{
	if (m_pImageOfMario      != nullptr) { delete m_pImageOfMario;      m_pImageOfMario      = nullptr; }
	if (m_pTextOfWORLD       != nullptr) { delete m_pTextOfWORLD;       m_pTextOfWORLD       = nullptr; }
	if (m_pTextOfMarioLife   != nullptr) { delete m_pTextOfMarioLife;   m_pTextOfMarioLife   = nullptr; }
	if (m_pTextOfWorldNamber != nullptr) { delete m_pTextOfWorldNamber; m_pTextOfWorldNamber = nullptr; }
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <param name="inputFlag"></param>
/// <returns>���̃V�[��</returns>
GameState ResultScene::UpDateScene(InputFlag inputFlag)
{
	m_NextGameState = GameState::RESULT;

	UpDateGame(inputFlag);
	Draw();

	return m_NextGameState;
}

/// <summary>
/// �Q�[���̍X�V
/// </summary>
/// <param name="inputFlag"></param>
void ResultScene::UpDateGame(InputFlag inputFlag)
{
	/* �w�肵���t���[���������V�[�����p������ */
	if (m_FlameCount >= M_CHANGE_FLAME_COUNT)
	{
		/* �t���[�����J�E���g�̃��Z�b�g */
		m_FlameCount = 0;
		/* �V�[���̕ύX */
		m_NextGameState = GameState::PLAY;
	}
	else
	{
		/* �t���[�����J�E���g */
		m_FlameCount++;
	}
}

/// <summary>
/// �`��
/// </summary>
void ResultScene::Draw()
{
	m_pImageOfMario     ->ThisObjRender();
	m_pTextOfWORLD      ->Render       ();
	m_pTextOfMarioLife  ->Render       ();
	m_pTextOfWorldNamber->Render       ();
}

/// <summary>
/// �X�e�[�W�ԍ��\���̕ύX
/// </summary>
/// <param name="worldNamber">�ύX�ハ�[���h�ԍ�</param>
/// <param name="stageNamber">�ύX��X�e�[�W�ԍ�</param>
void ResultScene::ChangeWorldNamber(int worldNamber, int stageNamber)
{
	std::string filePas = std::to_string(worldNamber) + "-" + std::to_string(stageNamber);  //�X�e�[�W�̃t�@�C���p�X

	/* �X�e�[�W�ԍ��\���̕ύX */
	m_pTextOfWorldNamber->ChangeText(filePas);
}

/// <summary>
/// �v���C���[�̎c�@�̕\���̕ύX
/// </summary>
/// <param name="playerLife">�ύX��̃v���C���[�̎c�@</param>
void ResultScene::ChangeMarioLife(UINT playerLife)
{
	m_pTextOfMarioLife->ChangeText("*  " + std::to_string(playerLife));
}