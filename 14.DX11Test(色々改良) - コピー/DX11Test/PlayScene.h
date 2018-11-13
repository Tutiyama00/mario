#pragma once

#include"IGameScene.h"
#include<d3d11.h>

class Camera;
class Player;
template<class T> class Characters;
class Block;
class Stage;
class Goal;

class PlayScene : public IGameScene
{
public:
	PlayScene();
	~PlayScene();



	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag);  //このシーンを更新する。戻り値は、次に行くべきステート

public:
	/* getter */
	Player* GetPlayer()        { return m_pPlayer; }
	int     GetNowWorldLevel() { return m_NowWorldLevel; }
	int     GetNowStageLevel() { return m_NowStageLevel; }

private:
	void MakeStageObj();
	void ReStart     ();
	void ReSet       ();

private:
	Stage*             m_pStage        = nullptr;
	Camera*            m_pCamera       = nullptr;
	Player*            m_pPlayer       = nullptr;
	Characters<Block>* m_pBlocks       = nullptr;
	Goal*              m_pGoal         = nullptr;

	float     m_StandardSize    = 0.075f;  //基準のサイズ
	float     m_StandardZpos    = -0.5f;   //基準のオブジェクトZポジション
	UINT      m_OldPlayerLife   = 0;       //プレイヤーの残機保存用変数
	float     m_UnderDeathLine  = 0;       //画面下の死亡判定ライン
	int       m_NowWorldLevel   = 0;       //現在のワールド
	int       m_NowStageLevel   = 0;       //現在のステージ
	const int M_IN_STAGE_AMOUNT = 4;       //一つのワールドにある面の数

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	//---IGameScene---
	GameState m_NextGameState;
};
