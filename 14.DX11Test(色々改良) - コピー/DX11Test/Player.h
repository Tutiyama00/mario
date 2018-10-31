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
	Player(Vector3 pos, Vector2 size, ID3D11Device* pDevice);  //コンストラクタ
	~Player(); //デストラクタ

	//---IMoveObj---
	void Move(InputFlag* inputFlag);  //プレイヤーの動き（入力情報)

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

public:

	//---IMoveObj---
	MoveObjState m_MoveObjState = MoveObjState::ON_THE_GROUND;     //プレイヤーのステート
	bool m_JumpFlag = true;        //ジャンプ可能かどうかのフラグ
	float m_NowWalkSpeed = 0.0f;   //今の歩く速度
	float m_JumpPower = 0.0005f;   //ジャンプ量

private:
	//---IMoveObj---
	void Walk(float xAmount);  //歩く
	bool Jump();               //ジャンプ
	void Fall();               //落下

	//---RenderObj---
	void Abstract();

private:
	//---IMoveObj---
	int m_MaxJumpLevel    = 50;                //ジャンプのレベルカウントの上限
	int m_JumpLevelCount          = m_MaxJumpLevel;  //ジャンプのレベルカウント（ジャンプボタン押してるときにカウントされる）
	const int m_JumpAbjustPoint = 2;                 //ジャンプ力計算に使う調整値
	const float m_MaxWalkSpeed  = 0.003f;            //歩く最大スピード
	float m_WalkFluctuationAmount = 0.0005f;           //歩くスピードを変える

    float m_SlipStopAmount        = 0.0001f;       //滑りを抑制する値
	float m_SlipStopThreshold     = 0.001f;        //滑りを０にするしきい値
};