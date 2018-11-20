#pragma once

#include<d3d11.h>
#include"Flag.h"

//�O���錾
enum class MoveObjState : unsigned char;


//�ړ�����I�u�W�F�N�g�Ɍp��������
class IMoveObj
{
public:
	virtual ~IMoveObj() {};

	virtual void Move() = 0;

public:
	/* getter */
	virtual MoveObjState GetMoveObjState()const { return m_MoveObjState; }
	virtual InputFlag GetInputFlag      ()const { return m_InputFlag; }

	/* setter */
	virtual void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	virtual void SetInputFlag   (InputFlag value)    { m_InputFlag = value; }

protected:
	virtual void Walk(float xAmount) = 0;  //����
	virtual bool Jump() = 0;               //�W�����v
	virtual void Fall() = 0;               //����

protected:
	bool m_LivingFlag;            //�����Ă��邩�̃t���O

	MoveObjState m_MoveObjState;  //�X�e�[�g

	InputFlag m_InputFlag;

	int m_MaxJumpLevel;           //�W�����v�̃��x���J�E���g�̏��
	int m_JumpLevelCount;         //�W�����v�̃��x���J�E���g�i�W�����v�{�^�������Ă�Ƃ��ɃJ�E���g�����j
	int m_JumpAbjustPoint;        //�W�����v�͌v�Z�Ɏg�������l


	float m_MaxWalkSpeed;          //�����ő�X�s�[�h
	float m_WalkFluctuationAmount; //�����X�s�[�h��ς���

	float m_SlipStopAmount;       //�����}������l
	float m_SlipStopThreshold;    //������O�ɂ��邵�����l

	bool  m_JumpFlag;             //�W�����v�\���ǂ����̃t���O
	float m_NowWalkSpeed;         //���̕������x
	float m_JumpPower;            //�W�����v��
};