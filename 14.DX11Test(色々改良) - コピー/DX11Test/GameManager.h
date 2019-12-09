#pragma once
#include"Singleton.h"

//前方宣言
class InputFlag;
enum class GameState : unsigned char;
class TitleScene;
class PlayScene;
class GameOverScene;
class ParameterScene;
class ResultScene;

class GameManager : public Singleton<GameManager>
{
public:
	friend class Singleton<GameManager>;

public:
	void InputGet();   //入力情報の取得
	void UpDateGame(); //ゲームの更新

	void Initialize(HWND hwnd); //初期化関数

public:
	/* getter */
	GameState GetGameState() { return m_GameState; }

private:
	GameManager() {};  //コンストラクタ
	GameManager(const GameManager &gameManager) {};  //コピーコンストラクタ
	~GameManager();    //デストラクタ

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
	bool m_InitializedFlag = false;  //初期化しているかのフラグ（True＝初期化済み、False＝未初期化）

protected:
	void Abstract() {};
};