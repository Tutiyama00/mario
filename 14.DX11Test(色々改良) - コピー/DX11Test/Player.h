#pragma once

#include"Vertex.h"
#include"RenderObj.h"
#include"Enum.h"
#include"Interface.h"

//�O���錾
class InputFlag;
class Block;

class Player : public Square, public RenderObj, public IMoveObj
{
public:
	Player(float xPos, float yPos, float zPos, float xSize, float ySize, ID3D11Device* pDevice);  //�R���X�g���N�^
	~Player(); //�f�X�g���N�^

	//---IMoveObj---
	void Move(InputFlag* inputFlag);  //�v���C���[�̓����i���͏��)

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

public:

	//---IMoveObj---
	MoveObjState m_MoveObjState = MoveObjState::ON_THE_GROUND;     //�v���C���[�̃X�e�[�g
	bool m_JumpFlag = true;        //�W�����v�\���ǂ����̃t���O
	float m_NowWalkSpeed = 0.0f;   //���̕������x
	float m_JumpPower = 0.0005f;   //�W�����v��

private:
	//---IMoveObj---
	void Walk(float xAmount);  //����
	bool Jump();               //�W�����v
	void Fall();               //����

	//---RenderObj---
	void Abstract();

private:
	//---IMoveObj---
	int m_MaxJumpLevel    = 50;                //�W�����v�̃��x���J�E���g�̏��
	int m_JumpLevelCount          = m_MaxJumpLevel;  //�W�����v�̃��x���J�E���g�i�W�����v�{�^�������Ă�Ƃ��ɃJ�E���g�����j
	const int m_JumpAbjustPoint = 2;                 //�W�����v�͌v�Z�Ɏg�������l
	const float m_MaxWalkSpeed  = 0.003f;            //�����ő�X�s�[�h
	float m_WalkFluctuationAmount = 0.0005f;           //�����X�s�[�h��ς���

    float m_SlipStopAmount        = 0.0001f;       //�����}������l
	float m_SlipStopThreshold     = 0.001f;        //������O�ɂ��邵�����l
};