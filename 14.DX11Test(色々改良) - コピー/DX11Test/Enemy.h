#pragma once

#include"INotPlayer.h"
#include"Vertex.h"
#include"RenderObj.h"
#include"IMoveObj.h"
#include"Enum.h"

class Enemy : public Square, public RenderObj, public INotPlayer, public IMoveObj
{
public:
	Enemy(Vector3 pos, Vector2 size) : Square(pos, size) {};
	~Enemy() {};

	/*---INotPlayer---*/
	void CheckPlayer(Player* pPlayer);
	void CheckEnemy(Enemy* pEnemy);

	/*---RenderObj---*/
	void ThisObjRender();
	void ThisObjCreateBuffer();

	/*---IMoveObj---*/
	virtual void Move() = 0;

public:
	/*---IMoveObj---*/
	/* getter */
	MoveObjState GetMoveObjState()const { return m_MoveObjState; }
	InputFlag    GetInputFlag   ()const { return m_InputFlag; }
	/* setter */
	void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	void SetInputFlag   (InputFlag    value) { m_InputFlag    = value; }

protected:
	virtual void Abstract() = 0;  //純粋仮想関数（これによってこのクラスはインスタンスできない)

	/*---IMoveObj---*/
	virtual void Walk(float xAmount);  //歩く
	virtual bool Jump();               //ジャンプ
	virtual void Fall();               //落下

protected:
	/*---IMoveObj---*/
	bool m_LivingFlag             = true;                         //生きているかのフラグ
	MoveObjState m_MoveObjState   = MoveObjState::ON_THE_GROUND;  //プレイヤーのステート
	int m_MaxJumpLevel            = 50;              //ジャンプのレベルカウントの上限
	int m_JumpLevelCount          = m_MaxJumpLevel;  //ジャンプのレベルカウント（ジャンプボタン押してるときにカウントされる）
	const int m_JumpAbjustPoint   = 2;               //ジャンプ力計算に使う調整値
	const float m_MaxWalkSpeed    = 0.003f;          //歩く最大スピード
	float m_WalkFluctuationAmount = 0.0005f;         //歩くスピードを変える

	float m_SlipStopAmount        = 0.0001f;         //滑りを抑制する値
	float m_SlipStopThreshold     = 0.001f;          //滑りを０にするしきい値

	unsigned char m_Life          = 0;               //残り残機

	bool  m_JumpFlag              = true;            //ジャンプ可能かどうかのフラグ
	float m_NowWalkSpeed          = 0.0f;            //今の歩く速度
	float m_JumpPower             = 0.0005f;         //ジャンプ量

	InputFlag m_InputFlag;

};