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
class TitleScene;
class PlayScene;
class GameOverScene;

class GameManager
{
public:
	GameManager(HWND hwnd);  //�R���X�g���N�^
	~GameManager(); //�f�X�g���N�^

	void GetInput();
	void UpDateGame();

public:
	Dx11*     m_pDx11     = nullptr;
	Dsound*   m_pDsound   = nullptr;

private:
	InputFlag*        m_pFlag             = nullptr;
	int               m_InputKey          = 0;

	GameState      m_GameState;
	TitleScene*    m_pTitleScene    = nullptr;
	PlayScene*     m_pPlayScene     = nullptr;
	GameOverScene* m_pGameOverScene = nullptr;
};