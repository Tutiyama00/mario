#pragma once

#include"NotPlayer.h"
#include"Vertex.h"
#include"RenderObj.h"
#include"IMoveObj.h"
#include"Enum.h"

class Enemy : public RenderObj, public NotPlayer, public IMoveObj
{
public:
	Enemy(Vector3 pos, Vector2 size) : NotPlayer(pos, size) {};
	~Enemy() {};

	virtual void StartStandardDie(bool direction);  //通常の死亡演出スタート

public:
	bool GetLivingFlag() { return m_LivingFlag; }

protected:
	virtual void Abstract() = 0;

	virtual void StandardDie();  //通常の死亡処理演出
	virtual void Die();

protected:
	int m_DieScorePoint                        = 0;                       //死んだときに加算されるスコア
	bool m_StanderdDieFlag                     = false;                   //通常の死に方をしたのか
	const unsigned int M_S_DIE_MOVE_FRAME      = 360;                     //死亡処理にかかるフレーム数
	const unsigned int M_S_DIE_MOVE_STOP_FRAME = 60;                      //死亡処理で最初止まっているフレーム数
	unsigned int       m_S_DieMoveFrameCounter = 0;                       //死亡処理で使用するフレームカウンター
	const float        M_S_DIE_MOVE_SPEED_MAX  = 0.01f;                   //死亡処理で移動するときの移動量の限界
	float              m_S_DieMoveNowSpeed     = M_S_DIE_MOVE_SPEED_MAX;  //死亡処理の今の移動量
	float              m_S_DieMoveChangeAmount = 0.0005f;                 //死亡処理の移動量の変動値
	float              m_S_DieMoveXMoveAmount  = 0.003f;                  //死亡処理のX軸の移動量

/*------NotPlayer------*/
public:
	virtual void CheckPlayer(Player* pPlayer);
	virtual void CheckEnemy(Enemy* pEnemy);


/*------RenderObj------*/
public:
	virtual void ThisObjRender();
	void ThisObjCreateBuffer();


/*------IMoveObj------*/
public:
	virtual void Move() = 0;

public:
	/* getter */
	MoveObjState GetMoveObjState()const { return m_MoveObjState; }
	InputFlag    GetInputFlag   ()const { return m_InputFlag;    }
	/* setter */
	void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	void SetInputFlag   (InputFlag    value) { m_InputFlag    = value; }

protected:
	virtual void Walk(float xAmount);  //歩く
	virtual bool Jump();               //ジャンプ
	virtual void Fall();               //落下

protected:
	bool          m_LivingFlag            = true;                         //生きているかのフラグ
	MoveObjState  m_MoveObjState          = MoveObjState::ON_THE_GROUND;  //プレイヤーのステート
	int           m_MaxJumpLevel          = 50;              //ジャンプのレベルカウントの上限
	int           m_JumpLevelCount        = m_MaxJumpLevel;  //ジャンプのレベルカウント（ジャンプボタン押してるときにカウントされる）
	const int     m_JumpAbjustPoint       = 2;               //ジャンプ力計算に使う調整値
	const float   m_MaxWalkSpeed          = 0.001f;          //歩く最大スピード
	float         m_WalkFluctuationAmount = 0.0005f;         //歩くスピードを変える
	float         m_SlipStopAmount        = 0.0001f;         //滑りを抑制する値
	float         m_SlipStopThreshold     = 0.001f;          //滑りを０にするしきい値
	unsigned char m_Life                  = 0;               //残り残機
	bool          m_JumpFlag              = true;            //ジャンプ可能かどうかのフラグ
	float         m_NowWalkSpeed          = 0.0f;            //今の歩く速度
	float         m_JumpPower             = 0.0005f;         //ジャンプ量

	InputFlag m_InputFlag;

};