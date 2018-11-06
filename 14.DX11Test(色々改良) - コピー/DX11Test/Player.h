#pragma once

#include"Vertex.h"
#include"RenderObj.h"
#include"Enum.h"
#include"IMoveObj.h"
#include"Math.h"

using namespace OriginalMath;

//�O���錾
class InputFlag;
class Block;

class Player : public Square, public RenderObj, public IMoveObj
{
public:
	Player(Vector3 pos, Vector2 size, ID3D11Device* pDevice);  //�R���X�g���N�^
	~Player(); //�f�X�g���N�^

	void Die(); //���S����

	//---IMoveObj---
	void Move(InputFlag* inputFlag);  //�v���C���[�̓����i���͏��)

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

public:
	//---IMoveObj---
	bool m_JumpFlag      = true;    //�W�����v�\���ǂ����̃t���O
	float m_NowWalkSpeed = 0.0f;    //���̕������x
	float m_JumpPower    = 0.0005f; //�W�����v��

public:
	int  GetLife()           { return m_Life; }
	void SetLife(UINT value) { m_Life = value; }

	//---IMoveObj---
	MoveObjState GetMoveObjState() { return m_MoveObjState; };
	void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; };
	
private:
	//---IMoveObj---
	void Walk(float xAmount);  //����
	bool Jump();               //�W�����v
	void Fall();               //����

	//---RenderObj---
	void Abstract();

private:
	//---IMoveObj---
	bool m_LivingFlag             = true;                         //�����Ă��邩�̃t���O
	MoveObjState m_MoveObjState   = MoveObjState::ON_THE_GROUND;  //�v���C���[�̃X�e�[�g
	int m_MaxJumpLevel            = 50;              //�W�����v�̃��x���J�E���g�̏��
	int m_JumpLevelCount          = m_MaxJumpLevel;  //�W�����v�̃��x���J�E���g�i�W�����v�{�^�������Ă�Ƃ��ɃJ�E���g�����j
	const int m_JumpAbjustPoint   = 2;               //�W�����v�͌v�Z�Ɏg�������l
	const float m_MaxWalkSpeed    = 0.003f;          //�����ő�X�s�[�h
	float m_WalkFluctuationAmount = 0.0005f;         //�����X�s�[�h��ς���

    float m_SlipStopAmount        = 0.0001f;       //�����}������l
	float m_SlipStopThreshold     = 0.001f;        //������O�ɂ��邵�����l

	UINT m_Life = 0; //�c��c�@
};