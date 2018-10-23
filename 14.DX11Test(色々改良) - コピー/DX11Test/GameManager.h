#pragma once

//�O���錾
class InputFlag;
enum class GameState : unsigned char;
class Player;
class Dx11;
class Dsound;
class Stage;
class Camera;
class CharacterManager;

class GameManager
{
public:
	GameManager(HWND hwnd);  //�R���X�g���N�^
	~GameManager(); //�f�X�g���N�^

	void GetInput();
	void UpDateGame();
	void Draw();

public:
	Dx11*     m_pDx11     = nullptr;
	Dsound*   m_pDsound   = nullptr;

private:
	CharacterManager* m_pCharacterManager = nullptr;
	InputFlag*        m_pFlag             = nullptr;
	Stage*            m_pStage            = nullptr;
	Camera*           m_pCamera           = nullptr;
	int               m_InputKey          = 0;

	GameState m_GameState;
};