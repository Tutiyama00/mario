#pragma once

#include"IGameScene.h"
#include<d3d11.h>
#include"Stage.h"
#include"Player.h"
#include<vector>

using namespace std;

class Camera;
template<class T> class Characters;
class Block;
class Goal;
class Kuribo;
class Nokonoko;
class Image;
class ClayPipe;
class Enemy;
class BackGround;

class PlayScene : public IGameScene
{
public:
	PlayScene();
	~PlayScene();

	void KillPlayer();

public:
	/* getter */
	const Player*  GetPlayer       ()const { return m_pPlayer; }
	const int      GetNowWorldLevel()const { return m_NowWorldLevel; }
	const int      GetNowStageLevel()const { return m_NowStageLevel; }
	const DWORD    GetStageTime    ()const { return m_pStage->GetStageTime(); }

private:
	void MakeStageObj          ();                            //ステージオブジェクトの生成
	void ReStart               ();                            //ゲームのリスタート
	void ReSet                 ();                            //ゲームのリセット
	void MoveScene             ();                            //シーンの遷移
	void StageObjDelete        ();                            //ステージ上のオブジェクトのデリート
	void MoveOrder             ();                            //キャラ達の移動命令
	void EnemyMoveOrder        (Enemy* pEnemy);               //敵の移動命令
	void ObjCheckOrder         ();                            //キャラ達のチェック命令
	void GoalCheckOrder        ();                            //ゴールしたかのチェック
	void CollisionCheckNokonoko();                            //ノコノコの衝突判定
	void CollisionCheckKuribo  ();                            //クリボーの衝突判定
	void CollisionCheckBlock   (Characters<Block>* pBlocks);  //ブロックの衝突判定
	void CollisionCheckClayPipe();                            //土管の衝突判定

private:
	Stage*                m_pStage             = nullptr;
	Camera*               m_pCamera            = nullptr;
	Player*               m_pPlayer            = nullptr;
	Characters<Block>*    m_pBlocks            = nullptr;
	Characters<Image>*    m_pBlockDummys       = nullptr;
	Characters<Block>*    m_pBlockGrounds      = nullptr;
	Characters<Image>*    m_pBlockGroundDummys = nullptr;
	Characters<ClayPipe>* m_pClayPipes         = nullptr;
	Goal*                 m_pGoal              = nullptr;
	BackGround*           m_pBackGround        = nullptr;
	vector<Kuribo*>       m_pKuriboVector;
	vector<Nokonoko*>     m_pNokonokoVector;
	

	float     m_StandardSize          = 0.075f; //基準のサイズ
	float     m_StandardZpos          = -0.5f;  //基準のオブジェクトZポジション
	UINT      m_OldPlayerLife         = 0;      //プレイヤーの残機保存用変数
	float     m_UnderDeathLine        = 0;      //画面下の死亡判定ライン
	int       m_NowWorldLevel         = 0;      //現在のワールド
	int       m_NowStageLevel         = 0;      //現在のステージ
	const int M_IN_STAGE_AMOUNT       = 4;      //一つのワールドにある面の数
	float     m_CameraShootXPos       = 0.0f;   //カメラを映すX座標
	float     m_PlayerMoveEndXPos     = 0.0f;   //プレイヤーの動ける左限界値
	float     m_EndToShootXPosAmount  = 0.75f;  //カメラから左限界値までの距離
	float     m_ObjMoveRightXPos      = 0.0f;   //オブジェクトが動ける範囲の右端のX座標
	float     m_ObjMoveLeftXPos       = 0.0f;   //オブジェクトが動ける範囲の左端のX座標
	float     m_BlockCheckRightXPos   = 0.0f;   //ブロックがコリジョンチェックする範囲の右端のX座標
	float     m_BlockCheckLeftXPos    = 0.0f;   //ブロックがコリジョンチェックする範囲の左端のX座標
	float     m_BlockCheckXPosDiff    = 0.3f;   //オブジェクトのMove範囲とブロックのコリジョン範囲の差（コリジョン範囲の方が広くなる）
	float     m_ObjMoveXPosAdjust     = 0.2f;   //カメラで映っている範囲のしきい値

/*------IGameScene------*/
public:
	GameState UpDateScene(InputFlag inputFlag);  //このシーンを更新する。戻り値は、次に行くべきステート

protected:
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	GameState m_NextGameState;
};
