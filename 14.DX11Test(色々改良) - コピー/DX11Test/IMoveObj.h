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
	virtual InputFlag    GetInputFlag   ()const { return m_InputFlag;    }

	/* setter */
	virtual void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	virtual void SetInputFlag   (InputFlag value)    { m_InputFlag    = value; }

protected:
	virtual void Walk(float xAmount) = 0;  //����
	virtual bool Jump(const unsigned int MAX_FRAME)              = 0;  //�W�����v
	virtual void Fall()              = 0;  //����

protected:
	bool               m_LivingFlag;             //�����Ă��邩�̃t���O
	MoveObjState       m_MoveObjState;           //�X�e�[�g
	InputFlag          m_InputFlag;              //���݂̓��͏��
	bool               m_CanJumpFlag       = true;                   //�W�����v�\���ǂ����̃t���O
	float              m_NowJumpFallPower  = 0.0005f;                //���̃W�����v�Ɨ����̑��x
	const float        M_JUMP_POWER        = 0.01f;                  //��{���x
	const float        M_JUMP_GRAVITY      = M_JUMP_POWER / 20;      //�W�����v���̏d��
	const float        M_FALL_MAX_POWER    = 0.01f;                  //�������x�̏��
	const float        M_FALL_GRAVITY      = M_FALL_MAX_POWER / 20;  //�������̏d��
	const unsigned int M_MAX_JUMP_FRAME    = 25;                     //�W�����v�̃t���[�����̏��
	const unsigned int M_MIN_JUMP_FRAME    = M_MAX_JUMP_FRAME / 4;   //�Œ�W�����v�t���[����
	unsigned int       m_JumpFrameCount    = 0;                      //�W�����v�̃t���[���J�E���^
	unsigned int       m_NowJumpMaxFrame   = 0;                      //�W�����v�����̂Ƃ���Jump�֐��ɑ������p�̕ϐ�
	float              m_MaxWalkSpeed;           //�����ő�X�s�[�h
	float              m_WalkFluctuationAmount;  //�����X�s�[�h��ς���
	float              m_NowWalkSpeed;           //���̕������x
	float              m_SlipStopAmount;         //�����}������l
	float              m_SlipStopThreshold;      //������O�ɂ��邵�����l
	const float        m_RunMagni = 1.7;  //�����Ă���Ƃ��̑��x�ɂ�����l
};