#pragma once

#include<d3d11.h>
#include"Flag.h"

//前方宣言
enum class MoveObjState : unsigned char;


//移動するオブジェクトに継承させる
class IMoveObj
{
public:
	virtual ~IMoveObj() {};

	virtual void Move() = 0;

public:
	/* getter */
	virtual MoveObjState GetMoveObjState()const { return m_MoveObjState; }
	virtual InputFlag    GetInputFlag   ()const { return m_InputFlag;    }
	virtual float        GetNowWalkSpeed()const { return m_NowWalkSpeed; }

	/* setter */
	virtual void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	virtual void SetInputFlag   (InputFlag value)    { m_InputFlag    = value; }

protected:
	virtual void Walk(float xAmount) = 0;  //歩く
	virtual bool Jump(const unsigned int MAX_FRAME)              = 0;  //ジャンプ
	virtual void Fall()              = 0;  //落下

protected:
	bool               m_LivingFlag;             //生きているかのフラグ
	MoveObjState       m_MoveObjState;           //ステート
	InputFlag          m_InputFlag;              //現在の入力状態
	bool               m_CanJumpFlag       = true;                   //ジャンプ可能かどうかのフラグ
	float              m_NowJumpFallPower  = 0.0005f;                //今のジャンプと落下の速度
	const float        M_JUMP_POWER        = 0.01f;                  //基本速度
	const float        M_JUMP_GRAVITY      = M_JUMP_POWER / 20;      //ジャンプ中の重力
	const float        M_FALL_MAX_POWER    = 0.01f;                  //落下速度の上限
	const float        M_FALL_GRAVITY      = M_FALL_MAX_POWER / 20;  //落下中の重力
	const unsigned int M_MAX_JUMP_FRAME    = 25;                     //ジャンプのフレーム数の上限
	const unsigned int M_MIN_JUMP_FRAME    = M_MAX_JUMP_FRAME / 4;   //最低ジャンプフレーム数
	unsigned int       m_JumpFrameCount    = 0;                      //ジャンプのフレームカウンタ
	unsigned int       m_NowJumpMaxFrame   = 0;                      //ジャンプ処理のときにJump関数に代入する用の変数
	float              m_MaxWalkSpeed;           //歩く最大スピード
	float              m_WalkFluctuationAmount;  //歩くスピードを変える
	float              m_NowWalkSpeed;           //今の歩く速度
	float              m_SlipStopAmount;         //滑りを抑制する値
	float              m_SlipStopThreshold;      //滑りを０にするしきい値
	const float        m_RunMagni = 1.7;         //走っているときの速度にかける値
	bool               m_RunFlag  = false;       //走っているかどうかのフラグ
	const float        m_RunAnimMagni = 1.5;     //走っているときのアニメーションのインターバル調整値
};