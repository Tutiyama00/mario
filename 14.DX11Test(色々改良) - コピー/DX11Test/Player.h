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
	void MiniJumpStart();

	/*---IMoveObj---*/
	void Move();  //�v���C���[�̓����i���͏��)

	/*---RenderObj---*/
	void ThisObjRender();
	void ThisObjCreateBuffer();

public:
	/* getter */
	unsigned char GetLife      ()const { return m_Life;       }
	unsigned char GetSTART_LIFE()const { return M_START_LIFE; }
	bool          GetLivibgFlag()const { return m_LivingFlag; }
	/* setter */
	void SetLife        (UINT  value) { m_Life         = value; }
	void SetJumpFlag    (bool  value) { m_JumpFlag     = value; }
	void SetNowWalkSpeed(float value) { m_NowWalkSpeed = value; }

	/*---IMoveObj---*/
	/* getter */
	MoveObjState GetMoveObjState()const              { return m_MoveObjState;  }
	InputFlag    GetInputFlag   ()const              { return m_InputFlag;     }
	/* setter */
	void         SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	void         SetInputFlag   (InputFlag value)    { m_InputFlag    = value; }
	
private:
	bool MiniJump();

	/*---IMoveObj---*/
	void Walk(float xAmount);  //����
	bool Jump();               //�W�����v
	void Fall();               //����

	/*---RenderObj---*/
	void Abstract() {};

private:
	const UINT M_START_LIFE = 3;      //�Q�[���X�^�[�g���̃v���C���[�̎c�@
	bool m_InvincibleFlag   = false;  //���G��ԃt���O�@true=���G�Afalse=�ʏ�
	unsigned char m_MiniJumpCount = 0;
	const unsigned char M_MINI_JUMP_COUNT_MAX = 50;
	bool m_MiniJumpFlag = false;
	const unsigned char M_MINI_JUMP_COUNT_INVINCIBLE_MAX = 5;  //�~�j�W�����v���̖��G���ԁi�t���[�����j

	/*---IMoveObj---*/
	bool          m_LivingFlag  = true;  //�����Ă��邩�̃t���O
	unsigned char m_Life        = 0;     //�c��c�@

	MoveObjState m_MoveObjState = MoveObjState::ON_THE_GROUND;  //�v���C���[�̃X�e�[�g

	InputFlag    m_InputFlag;  //���݂̓��͏��

	int       m_MaxJumpLevel    = 50;              //�W�����v�̃��x���J�E���g�̏��
	int       m_JumpLevelCount  = m_MaxJumpLevel;  //�W�����v�̃��x���J�E���g�i�W�����v�{�^�������Ă�Ƃ��ɃJ�E���g�����j
	const int m_JumpAbjustPoint = 2;               //�W�����v�͌v�Z�Ɏg�������l
	bool      m_JumpFlag        = true;            //�W�����v�\���ǂ����̃t���O
	float     m_JumpPower       = 0.0005f;         //�W�����v��

	const float  m_MaxWalkSpeed          = 0.003f;   //�����ő�X�s�[�h
	float        m_WalkFluctuationAmount = 0.0005f;  //�����X�s�[�h��ς���
	float        m_NowWalkSpeed          = 0.0f;     //���̕������x

    float m_SlipStopAmount     = 0.0001f;  //�����}������l
	float m_SlipStopThreshold  = 0.001f;   //������O�ɂ��邵�����l
};