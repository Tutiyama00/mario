#pragma once

#include<d3d11.h>

//�O���錾
class Player;
class InputFlag;
enum class MoveObjState : unsigned char;

//##############�C���^�[�t�F�[�X#########################

//�v���C���[�ȊO�̃I�u�W�F�N�g�Ɍp��������
class INotPlayer
{
public:
	virtual ~INotPlayer() {};
	virtual void CheckPlayer(Player* player, InputFlag* pInputFlag) = 0;
};

//�ړ�����I�u�W�F�N�g�Ɍp��������
class IMoveObj
{
public:
	virtual ~IMoveObj() {};

	virtual void Move(InputFlag* inputFlag) = 0;

public:
	MoveObjState m_MoveObjState;  //�X�e�[�g
	bool  m_JumpFlag;             //�W�����v�\���ǂ����̃t���O
	float m_NowWalkSpeed;         //���̕������x
	float m_JumpPower;            //�W�����v��

protected:
	virtual void Walk(float xAmount) = 0;  //����
	virtual bool Jump() = 0;               //�W�����v
	virtual void Fall() = 0;               //����

protected:
	int m_MaxJumpLevel;      //�W�����v�̃��x���J�E���g�̏��
	int m_JumpLevelCount;    //�W�����v�̃��x���J�E���g�i�W�����v�{�^�������Ă�Ƃ��ɃJ�E���g�����j
	int m_JumpAbjustPoint;   //�W�����v�͌v�Z�Ɏg�������l


	float m_MaxWalkSpeed;            //�����ő�X�s�[�h
	float m_WalkFluctuationAmount;   //�����X�s�[�h��ς���

	float m_SlipStopAmount;       //�����}������l
	float m_SlipStopThreshold;    //������O�ɂ��邵�����l
};