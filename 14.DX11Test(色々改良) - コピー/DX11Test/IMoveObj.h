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
	virtual MoveObjState GetMoveObjState() { return m_MoveObjState; }
	virtual InputFlag GetInputFlag() { return m_InputFlag; }

	/* setter */
	virtual void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	virtual void SetInputFlag(InputFlag value) { m_InputFlag = value; }

protected:
	virtual void Walk(float xAmount) = 0;  //歩く
	virtual bool Jump() = 0;               //ジャンプ
	virtual void Fall() = 0;               //落下

protected:
	bool m_LivingFlag;            //生きているかのフラグ
	MoveObjState m_MoveObjState;  //ステート
	int m_MaxJumpLevel;           //ジャンプのレベルカウントの上限
	int m_JumpLevelCount;         //ジャンプのレベルカウント（ジャンプボタン押してるときにカウントされる）
	int m_JumpAbjustPoint;        //ジャンプ力計算に使う調整値


	float m_MaxWalkSpeed;          //歩く最大スピード
	float m_WalkFluctuationAmount; //歩くスピードを変える

	float m_SlipStopAmount;       //滑りを抑制する値
	float m_SlipStopThreshold;    //滑りを０にするしきい値

	bool  m_JumpFlag;             //ジャンプ可能かどうかのフラグ
	float m_NowWalkSpeed;         //今の歩く速度
	float m_JumpPower;            //ジャンプ量

	InputFlag m_InputFlag;
};