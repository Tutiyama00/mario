#pragma once
#include"Singleton.h"

//�O���錾
class InputFlag;
enum class GameState : unsigned char;
class Player;
class Dx11;
class SoundData;
class Stage;
class Camera;
class CharacterManager;
class TitleScene;
class PlayScene;
class GameOverScene;
class ParameterScene;
class ResultScene;
class SoundData;

class GameManager : public Singleton<GameManager>
{
public:
	friend class Singleton<GameManager>;

public:
	void InputGet();   //���͏��̎擾
	void UpDateGame(); //�Q�[���̍X�V

	void Initialize(HWND hwnd); //�������֐�

public:
	/* getter */
	GameState GetGameState() { return m_GameState; }

private:
	GameManager() {};  //�R���X�g���N�^
	GameManager(const GameManager &gameManager) {};  //�R�s�[�R���X�g���N�^
	~GameManager();    //�f�X�g���N�^

private:
	InputFlag*        m_pFlag         = nullptr;
	int               m_InputKey      = 0;

	GameState       m_GameState;
	TitleScene*     m_pTitleScene     = nullptr;
	PlayScene*      m_pPlayScene      = nullptr;
	GameOverScene*  m_pGameOverScene  = nullptr;
	ParameterScene* m_pParameterScene = nullptr;
	ResultScene*    m_pResultScene    = nullptr;


/*------Singleton------*/
protected:
	bool m_InitializedFlag = false;  //���������Ă��邩�̃t���O�iTrue���������ς݁AFalse�����������j

protected:
	void Abstract() {};
};