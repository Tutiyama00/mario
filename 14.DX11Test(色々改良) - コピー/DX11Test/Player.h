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
class Animation;

class Player : public Square, public RenderObj, public IMoveObj
{
public:
	Player(Vector3 pos, Vector2 size);  //�R���X�g���N�^
	~Player(); //�f�X�g���N�^

	void Die(); //���S����
	bool DieMove();  //���S���o
	void MiniJumpStart();
	void GoalPlay(float downAmount, float downEndYPos, bool down);

public:
	/* getter */
	unsigned char GetLife      ()const { return m_Life;       }
	unsigned char GetSTART_LIFE()const { return M_START_LIFE; }
	bool          GetLivibgFlag()const { return m_LivingFlag; }
	/* setter */
	void SetLife        (UINT  value) { m_Life         = value; }
	void SetJumpFlag    (bool  value) { m_JumpFlag     = value; }
	void SetNowWalkSpeed(float value) { m_NowWalkSpeed = value; }
	
private:
	bool MiniJump();
	void PlayerMove();
	

private:
	const UINT          M_START_LIFE          = 3;      //�Q�[���X�^�[�g���̃v���C���[�̎c�@
	bool                m_InvincibleFlag      = false;  //���G��ԃt���O�@true=���G�Afalse=�ʏ�
	unsigned char       m_MiniJumpCount       = 0;
	const unsigned char M_MINI_JUMP_COUNT_MAX = 25;
	bool                m_MiniJumpFlag        = false;
	const unsigned char M_MINI_JUMP_COUNT_INVINCIBLE_MAX = 5;  //�~�j�W�����v���̖��G���ԁi�t���[�����j
	unsigned char m_Life = 0;     //�c��c�@
	Animation* m_pRunAnimation = nullptr;

	bool m_GoalPlayFlag = false;  //�S�[�������ǂ����̃t���O
	enum GoalPlayState
	{
		POLE_DOWN,
		POLE_STOP,
		POLE_PARALLEL_WAIT,
		WALK_TO_CASTLE
	};
	GoalPlayState m_GoalPlayState = GoalPlayState::POLE_DOWN;
	const unsigned int M_POLE_STOP_WAIT_FRAME = 20;
	unsigned int m_PoleStopWaitCounter = 0;

	const unsigned int M_DIE_MOVE_FRAME      = 360;  //���S�����ɂ�����t���[����
	const unsigned int M_DIE_MOVE_STOP_FRAME = 60;   //���S�����ōŏ��~�܂��Ă���t���[����
	unsigned int       m_DieMoveFrameCounter = 0;    //���S�����Ŏg�p����t���[���J�E���^�[
	const float        M_DIE_MOVE_SPEED_MAX  = 0.02f;
	float              m_DieMoveNowSpeed     = M_DIE_MOVE_SPEED_MAX;
	float              m_DieMoveChangeAmount = 0.0005f;  //���S�����̈ړ��ʂ̕ϓ��l



/*------IMoveObj------*/
public:
	void Move();  //�v���C���[�̓���

public:
	/* getter */
	MoveObjState GetMoveObjState()const { return m_MoveObjState; }
	InputFlag    GetInputFlag()const { return m_InputFlag; }
	/* setter */
	void         SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	void         SetInputFlag(InputFlag value) { if (!m_GoalPlayFlag) { m_InputFlag = value; } }

private:
	void Walk(float xAmount);  //����
	bool Jump();               //�W�����v
	void Fall();               //����

private:
	bool          m_LivingFlag = true;  //�����Ă��邩�̃t���O
	
	MoveObjState m_MoveObjState = MoveObjState::ON_THE_GROUND;  //�v���C���[�̃X�e�[�g

	InputFlag    m_InputFlag;  //���݂̓��͏��

	int          m_MaxJumpLevel = 50;              //�W�����v�̃��x���J�E���g�̏��
	int          m_JumpLevelCount = m_MaxJumpLevel;  //�W�����v�̃��x���J�E���g�i�W�����v�{�^�������Ă�Ƃ��ɃJ�E���g�����j
	int          m_JumpAbjustPoint = 2;               //�W�����v�͌v�Z�Ɏg�������l
	bool         m_JumpFlag = true;            //�W�����v�\���ǂ����̃t���O
	float        m_JumpPower = 0.0005f;         //�W�����v��

	float        m_MaxWalkSpeed = 0.003f;   //�����ő�X�s�[�h
	float        m_WalkFluctuationAmount = 0.0005f;  //�����X�s�[�h��ς���
	float        m_NowWalkSpeed = 0.0f;     //���̕������x

	float        m_SlipStopAmount = 0.0001f;  //�����}������l
	float        m_SlipStopThreshold = 0.001f;   //������O�ɂ��邵�����l


/*------RenderObj------*/
public:
	void ThisObjRender();
	void ThisObjCreateBuffer();

private:
	void Abstract() {};
};