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

class Player : public Square, public RenderObj, public IMoveObj
{
public:
	Player(Vector3 pos, Vector2 size);  //コンストラクタ
	~Player(); //デストラクタ

	void Die(); //死亡処理

	/*---IMoveObj---*/
	void Move(InputFlag* inputFlag);  //プレイヤーの動き（入力情報)

	/*---RenderObj---*/
	void ThisObjRender();
	void ThisObjCreateBuffer();

public:
	/* getter */
	unsigned char GetLife()       { return m_Life; }
	unsigned char GetSTART_LIFE() { return M_START_LIFE; }
	bool          GetLivibgFlag() { return m_LivingFlag; }

	/* setter */
	void SetLife        (UINT  value) { m_Life         = value; }
	void SetJumpFlag    (bool  value) { m_JumpFlag     = value; }
	void SetNowWalkSpeed(float value) { m_NowWalkSpeed = value; }

	/*---IMoveObj---*/
	MoveObjState GetMoveObjState() { return m_MoveObjState; };
	void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; };
	
private:
	/*---IMoveObj---*/
	void Walk(float xAmount);  //歩く
	bool Jump();               //ジャンプ
	void Fall();               //落下

	/*---RenderObj---*/
	void Abstract();

private:
	const UINT M_START_LIFE = 3;  //ゲームスタート時のプレイヤーの残機

	/*---IMoveObj---*/
	bool m_LivingFlag             = true;                         //生きているかのフラグ
	MoveObjState m_MoveObjState   = MoveObjState::ON_THE_GROUND;  //プレイヤーのステート
	int m_MaxJumpLevel            = 50;              //ジャンプのレベルカウントの上限
	int m_JumpLevelCount          = m_MaxJumpLevel;  //ジャンプのレベルカウント（ジャンプボタン押してるときにカウントされる）
	const int m_JumpAbjustPoint   = 2;               //ジャンプ力計算に使う調整値
	const float m_MaxWalkSpeed    = 0.003f;          //歩く最大スピード
	float m_WalkFluctuationAmount = 0.0005f;         //歩くスピードを変える

    float m_SlipStopAmount        = 0.0001f;       //滑りを抑制する値
	float m_SlipStopThreshold     = 0.001f;        //滑りを０にするしきい値

	unsigned char m_Life = 0; //残り残機

	bool  m_JumpFlag     = true;    //ジャンプ可能かどうかのフラグ
	float m_NowWalkSpeed = 0.0f;    //今の歩く速度
	float m_JumpPower    = 0.0005f; //ジャンプ量
};