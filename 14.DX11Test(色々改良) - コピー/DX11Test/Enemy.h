#pragma once

#include"NotPlayer.h"
#include"Vertex.h"
#include"RenderObj.h"
#include"IMoveObj.h"
#include"Enum.h"

class Enemy : public RenderObj, public NotPlayer, public IMoveObj
{
public:
	Enemy(Vector3 pos, Vector2 size) : NotPlayer(pos, size) {};
	~Enemy() {};

	virtual void Die();
	virtual void StartStandardDie(bool direction);  //�ʏ�̎��S���o�X�^�[�g

public:
	bool GetLivingFlag() { return m_LivingFlag; }

protected:
	virtual void Abstract() = 0;

	virtual void StandardDie();  //�ʏ�̎��S�������o

protected:
	int m_DieScorePoint                        = 0;                       //���񂾂Ƃ��ɉ��Z�����X�R�A
	bool m_StanderdDieFlag                     = false;                   //�ʏ�̎��ɕ��������̂�
	const unsigned int M_S_DIE_MOVE_FRAME      = 360;                     //���S�����ɂ�����t���[����
	const unsigned int M_S_DIE_MOVE_STOP_FRAME = 60;                      //���S�����ōŏ��~�܂��Ă���t���[����
	unsigned int       m_S_DieMoveFrameCounter = 0;                       //���S�����Ŏg�p����t���[���J�E���^�[
	const float        M_S_DIE_MOVE_SPEED_MAX  = 0.02f;                   //���S�����ňړ�����Ƃ��̈ړ��ʂ̌��E
	float              m_S_DieMoveNowSpeed     = M_S_DIE_MOVE_SPEED_MAX;  //���S�����̍��̈ړ���
	float              m_S_DieMoveChangeAmount = 0.0005f;                 //���S�����̈ړ��ʂ̕ϓ��l
	float              m_S_DieMoveXMoveAmount  = 0.0003f;                 //���S������X���̈ړ���

/*------NotPlayer------*/
public:
	virtual void CheckPlayer(Player* pPlayer);
	virtual void CheckEnemy(Enemy* pEnemy);


/*------RenderObj------*/
public:
	virtual void ThisObjRender();
	void ThisObjCreateBuffer();


/*------IMoveObj------*/
public:
	virtual void Move() = 0;

public:
	/* getter */
	MoveObjState GetMoveObjState()const { return m_MoveObjState; }
	InputFlag    GetInputFlag   ()const { return m_InputFlag;    }
	/* setter */
	void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	void SetInputFlag   (InputFlag    value) { m_InputFlag    = value; }

protected:
	virtual void Walk(float xAmount);  //����
	virtual bool Jump();               //�W�����v
	virtual void Fall();               //����

protected:
	bool          m_LivingFlag            = true;                         //�����Ă��邩�̃t���O
	MoveObjState  m_MoveObjState          = MoveObjState::ON_THE_GROUND;  //�v���C���[�̃X�e�[�g
	int           m_MaxJumpLevel          = 50;              //�W�����v�̃��x���J�E���g�̏��
	int           m_JumpLevelCount        = m_MaxJumpLevel;  //�W�����v�̃��x���J�E���g�i�W�����v�{�^�������Ă�Ƃ��ɃJ�E���g�����j
	const int     m_JumpAbjustPoint       = 2;               //�W�����v�͌v�Z�Ɏg�������l
	const float   m_MaxWalkSpeed          = 0.001f;          //�����ő�X�s�[�h
	float         m_WalkFluctuationAmount = 0.0005f;         //�����X�s�[�h��ς���
	float         m_SlipStopAmount        = 0.0001f;         //�����}������l
	float         m_SlipStopThreshold     = 0.001f;          //������O�ɂ��邵�����l
	unsigned char m_Life                  = 0;               //�c��c�@
	bool          m_JumpFlag              = true;            //�W�����v�\���ǂ����̃t���O
	float         m_NowWalkSpeed          = 0.0f;            //���̕������x
	float         m_JumpPower             = 0.0005f;         //�W�����v��

	InputFlag m_InputFlag;

};