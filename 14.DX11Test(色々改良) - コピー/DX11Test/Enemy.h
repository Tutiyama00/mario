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

	void Die();

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
	virtual void Abstract() = 0;  //�������z�֐��i����ɂ���Ă��̃N���X�̓C���X�^���X�ł��Ȃ�)

	/*---IMoveObj---*/
	virtual void Walk(float xAmount);  //����
	virtual bool Jump();               //�W�����v
	virtual void Fall();               //����

protected:
	/*---IMoveObj---*/
	bool         m_LivingFlag            = true;                         //�����Ă��邩�̃t���O
	MoveObjState m_MoveObjState          = MoveObjState::ON_THE_GROUND;  //�v���C���[�̃X�e�[�g
	int          m_MaxJumpLevel          = 50;              //�W�����v�̃��x���J�E���g�̏��
	int          m_JumpLevelCount        = m_MaxJumpLevel;  //�W�����v�̃��x���J�E���g�i�W�����v�{�^�������Ă�Ƃ��ɃJ�E���g�����j
	const int    m_JumpAbjustPoint       = 2;               //�W�����v�͌v�Z�Ɏg�������l
	const float  m_MaxWalkSpeed          = 0.001f;          //�����ő�X�s�[�h
	float        m_WalkFluctuationAmount = 0.0005f;         //�����X�s�[�h��ς���

	float m_SlipStopAmount        = 0.0001f;         //�����}������l
	float m_SlipStopThreshold     = 0.001f;          //������O�ɂ��邵�����l

	unsigned char m_Life          = 0;               //�c��c�@

	bool  m_JumpFlag              = true;            //�W�����v�\���ǂ����̃t���O
	float m_NowWalkSpeed          = 0.0f;            //���̕������x
	float m_JumpPower             = 0.0005f;         //�W�����v��

	InputFlag m_InputFlag;

};