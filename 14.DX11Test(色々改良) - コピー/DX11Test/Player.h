#pragma once

#include"Vertex.h"
#include"RenderObj.h"
#include"Enum.h"
#include"IMoveObj.h"
#include"Math.h"

using namespace OriginalMath;

//前方宣言
class InputFlag;
class Block;
class Animation;

class Player : public Square, public RenderObj, public IMoveObj
{
public:
	Player(Vector3 pos, Vector2 size);  //コンストラクタ
	~Player(); //デストラクタ

	void Die          ();  //死亡処理
	bool DieMove      ();  //死亡演出
	void MiniJumpStart();  //ミニジャンプを始める
	void GoalPlay(float downAmount, float downEndYPos, bool down);

public:
	/* getter */
	unsigned char GetLife      ()const { return m_Life;       }
	unsigned char GetSTART_LIFE()const { return M_START_LIFE; }
	bool          GetLivibgFlag()const { return m_LivingFlag; }
	/* setter */
	void SetLife        (UINT  value) { m_Life         = value; }
	void SetJumpFlag    (bool  value) { m_CanJumpFlag  = value; }
	void SetNowWalkSpeed(float value) { m_NowWalkSpeed = value; }
	
private:
	bool MiniJump();
	void PlayerMove();
	

private:
	const UINT          M_START_LIFE                     = 3;       //ゲームスタート時のプレイヤーの残機
	bool                m_InvincibleFlag                 = false;   //無敵状態フラグ　true=無敵、false=通常
	unsigned char       m_MiniJumpCount                  = 0;       //ミニジャンプでのフレームカウンタ
	const unsigned char M_MINI_JUMP_COUNT_MAX            = 3;      //ミニジャンプにかかるフレーム数
	bool                m_MiniJumpFlag                   = false;   //ミニジャンプをしているのかのフラグ
	const unsigned char M_MINI_JUMP_COUNT_INVINCIBLE_MAX = 3;       //ミニジャンプ中の無敵時間（フレーム数）
	unsigned char       m_Life                           = 0;       //残り残機
	Animation*          m_pRunAnimation                  = nullptr; //走るアニメーション

	bool m_GoalPlayFlag = false;  //ゴール中かどうかのフラグ
	enum GoalPlayState
	{
		POLE_DOWN,
		POLE_STOP,
		POLE_PARALLEL_WAIT,
		WALK_TO_CASTLE
	};
	GoalPlayState      m_GoalPlayState        = GoalPlayState::POLE_DOWN;  //ゴール演出のステート
	const unsigned int M_POLE_STOP_WAIT_FRAME = 20;                        //ゴール演出でポールにしがみついているフレーム数
	unsigned int       m_PoleStopWaitCounter  = 0;                         //ゴール演出でポールにしがみついているフレームカウンタ

	const unsigned int M_DIE_MOVE_FRAME      = 360;                   //死亡処理にかかるフレーム数
	const unsigned int M_DIE_MOVE_STOP_FRAME = 60;                    //死亡処理で最初止まっているフレーム数
	unsigned int       m_DieMoveFrameCounter = 0;                     //死亡処理で使用するフレームカウンター
	const float        M_DIE_MOVE_SPEED_MAX  = 0.02f;                 //死亡処理でポールから落ちる速度最大値
	float              m_DieMoveNowSpeed     = M_DIE_MOVE_SPEED_MAX;  //死亡処理でポールから落ちる速度
	float              m_DieMoveChangeAmount = 0.0005f;               //死亡処理の移動量の変動値



/*------IMoveObj------*/
public:
	void Move();  //プレイヤーの動き

public:
	/* getter */
	MoveObjState GetMoveObjState()const { return m_MoveObjState; }
	InputFlag    GetInputFlag   ()const { return m_InputFlag; }
	/* setter */
	void         SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	void         SetInputFlag   (InputFlag    value) { if (!m_GoalPlayFlag) { m_InputFlag = value; } }

private:
	void Walk(float xAmount);  //歩く
	bool Jump(const unsigned int MAX_FRAME);               //ジャンプ
	void Fall();               //落下

private:
	bool          m_LivingFlag  = true;  //生きているかのフラグ
	
	MoveObjState m_MoveObjState = MoveObjState::ON_THE_GROUND;  //プレイヤーのステート

	InputFlag    m_InputFlag;  //現在の入力状態

	float        m_MaxWalkSpeed          = 0.003f;   //歩く最大スピード
	float        m_WalkFluctuationAmount = 0.0005f;  //歩くスピードを変える
	float        m_NowWalkSpeed          = 0.0f;     //今の歩く速度

	float        m_SlipStopAmount    = 0.0001f;  //滑りを抑制する値
	float        m_SlipStopThreshold = 0.001f;   //滑りを０にするしきい値


/*------RenderObj------*/
public:
	void ThisObjRender();
	void ThisObjCreateBuffer();

private:
	void Abstract() {};
};