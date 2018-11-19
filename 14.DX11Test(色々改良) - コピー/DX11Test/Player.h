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
	Player(Vector3 pos, Vector2 size);  //�R���X�g���N�^
	~Player() {}; //�f�X�g���N�^

	void Die(); //���S����

	/*---IMoveObj---*/
	void Move();  //�v���C���[�̓����i���͏��)

	/*---RenderObj---*/
	void ThisObjRender();
	void ThisObjCreateBuffer();

public:
	/* getter */
	unsigned char GetLife()const       { return m_Life; }
	unsigned char GetSTART_LIFE()const { return M_START_LIFE; }
	bool          GetLivibgFlag()const { return m_LivingFlag; }

	/* setter */
	void SetLife        (UINT  value) { m_Life         = value; }
	void SetJumpFlag    (bool  value) { m_JumpFlag     = value; }
	void SetNowWalkSpeed(float value) { m_NowWalkSpeed = value; }

	/*---IMoveObj---*/
	MoveObjState GetMoveObjState() { return m_MoveObjState; };
	void SetMoveObjState(MoveObjState value) { m_MoveObjState = value; };
	
private:
	/*---IMoveObj---*/
	void Walk(float xAmount);  //����
	bool Jump();               //�W�����v
	void Fall();               //����

	/*---RenderObj---*/
	void Abstract() {};

private:
	const UINT M_START_LIFE = 3;  //�Q�[���X�^�[�g���̃v���C���[�̎c�@

	/*---IMoveObj---*/
	bool m_LivingFlag             = true;                         //�����Ă��邩�̃t���O
	MoveObjState m_MoveObjState   = MoveObjState::ON_THE_GROUND;  //�v���C���[�̃X�e�[�g
	int m_MaxJumpLevel            = 50;              //�W�����v�̃��x���J�E���g�̏��
	int m_JumpLevelCount          = m_MaxJumpLevel;  //�W�����v�̃��x���J�E���g�i�W�����v�{�^�������Ă�Ƃ��ɃJ�E���g�����j
	const int m_JumpAbjustPoint   = 2;               //�W�����v�͌v�Z�Ɏg�������l
	const float m_MaxWalkSpeed    = 0.003f;          //�����ő�X�s�[�h
	float m_WalkFluctuationAmount = 0.0005f;         //�����X�s�[�h��ς���

    float m_SlipStopAmount        = 0.0001f;       //�����}������l
	float m_SlipStopThreshold     = 0.001f;        //������O�ɂ��邵�����l

	unsigned char m_Life = 0; //�c��c�@

	bool  m_JumpFlag     = true;    //�W�����v�\���ǂ����̃t���O
	float m_NowWalkSpeed = 0.0f;    //���̕������x
	float m_JumpPower    = 0.0005f; //�W�����v��
};