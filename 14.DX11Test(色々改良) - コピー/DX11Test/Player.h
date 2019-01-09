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

	void Die(); //死亡処理
	void MiniJumpStart();
	void GoalPlay(float downAmount, float downEndYPos, bool down);

public:
	/* getter */
	unsigned char GetLife      ()const { return m_Life;       }
	unsigned char GetSTART_LIFE()const { return M_START_LIFE; }
	bool          GetLivibgFlag()const { return m_LivingFlag; }
	/* setter */
	void SetLife        (UINT  value) { m_Life         = value; }
	void SetJumpFlag    (bool  value) { m_JumpFlag     = value; }
	void SetNowWalkSpeed(float value) { m_NowWalkSpeed = value; }
	
private:
	bool MiniJump();
	void PlayerMove();

private:
	const UINT          M_START_LIFE          = 3;      //ゲームスタート時のプレイヤーの残機
	bool                m_InvincibleFlag      = false;  //無敵状態フラグ　true=無敵、false=通常
	unsigned char       m_MiniJumpCount       = 0;
	const unsigned char M_MINI_JUMP_COUNT_MAX = 25;
	bool                m_MiniJumpFlag        = false;
	const unsigned char M_MINI_JUMP_COUNT_INVINCIBLE_MAX = 5;  //ミニジャンプ中の無敵時間（フレーム数）
	unsigned char m_Life = 0;     //残り残機
	Animation* m_pRunAnimation = nullptr;

	bool m_GoalPlayFlag = false;  //ゴール中かどうかのフラグ
	enum GoalPlayState
	{
		POLE_DOWN,
		POLE_STOP,
		POLE_PARALLEL_WAIT,
		WALK_TO_CASTLE
	};
	GoalPlayState m_GoalPlayState = GoalPlayState::POLE_DOWN;
	const unsigned int M_POLE_STOP_WAIT_FRAME = 20;
	unsigned int m_PoleStopWaitCounter = 0;


/*------IMoveObj------*/
public:
	void Move();  //プレイヤーの動き

public:
	/* getter */
	MoveObjState GetMoveObjState()const { return m_MoveObjState; }
	InputFlag    GetInputFlag()const { return m_InputFlag; }
	/* setter */
	void         SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	void         SetInputFlag(InputFlag value) { if (!m_GoalPlayFlag) { m_InputFlag = value; } }

private:
	void Walk(float xAmount);  //歩く
	bool Jump();               //ジャンプ
	void Fall();               //落下

private:
	bool          m_LivingFlag = true;  //生きているかのフラグ
	
	MoveObjState m_MoveObjState = MoveObjState::ON_THE_GROUND;  //プレイヤーのステート

	InputFlag    m_InputFlag;  //現在の入力状態

	int          m_MaxJumpLevel = 50;              //ジャンプのレベルカウントの上限
	int          m_JumpLevelCount = m_MaxJumpLevel;  //ジャンプのレベルカウント（ジャンプボタン押してるときにカウントされる）
	int          m_JumpAbjustPoint = 2;               //ジャンプ力計算に使う調整値
	bool         m_JumpFlag = true;            //ジャンプ可能かどうかのフラグ
	float        m_JumpPower = 0.0005f;         //ジャンプ量

	float        m_MaxWalkSpeed = 0.003f;   //歩く最大スピード
	float        m_WalkFluctuationAmount = 0.0005f;  //歩くスピードを変える
	float        m_NowWalkSpeed = 0.0f;     //今の歩く速度

	float        m_SlipStopAmount = 0.0001f;  //滑りを抑制する値
	float        m_SlipStopThreshold = 0.001f;   //滑りを０にするしきい値


/*------RenderObj------*/
public:
	void ThisObjRender();
	void ThisObjCreateBuffer();

private:
	void Abstract() {};
};