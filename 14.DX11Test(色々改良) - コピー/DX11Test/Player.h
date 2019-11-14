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

	void Die          ();  //���S����
	bool DieMove      ();  //���S���o
	void MiniJumpStart();  //�~�j�W�����v���n�߂�
	void GoalPlay(float downAmount, float downEndYPos, bool down);

public:
	/* getter */
	unsigned char GetLife      ()const { return m_Life;       }
	unsigned char GetSTART_LIFE()const { return M_START_LIFE; }
	bool          GetLivibgFlag()const { return m_LivingFlag; }
	/* setter */
	void SetLife        (UINT  value) { m_Life         = value; }
	void SetJumpFlag    (bool  value) { m_CanJumpFlag  = value; }
	void SetNowWalkSpeed(float value) { m_NowWalkSpeed = value; }
	
private:
	bool MiniJump();
	void PlayerMove();
	

private:
	const UINT          M_START_LIFE                     = 3;       //�Q�[���X�^�[�g���̃v���C���[�̎c�@
	bool                m_InvincibleFlag                 = false;   //���G��ԃt���O�@true=���G�Afalse=�ʏ�
	unsigned char       m_MiniJumpCount                  = 0;       //�~�j�W�����v�ł̃t���[���J�E���^
	const unsigned char M_MINI_JUMP_COUNT_MAX            = 3;       //�~�j�W�����v�ɂ�����t���[����
	bool                m_MiniJumpFlag                   = false;   //�~�j�W�����v�����Ă���̂��̃t���O
	const unsigned char M_MINI_JUMP_COUNT_INVINCIBLE_MAX = 3;       //�~�j�W�����v���̖��G���ԁi�t���[�����j
	unsigned char       m_Life                           = 0;       //�c��c�@
	Animation*          m_pRunAnimation                  = nullptr; //����A�j���[�V����

	bool m_GoalPlayFlag = false;  //�S�[�������ǂ����̃t���O
	enum GoalPlayState
	{
		POLE_DOWN,
		POLE_STOP,
		POLE_PARALLEL_WAIT,
		WALK_TO_CASTLE
	};
	GoalPlayState      m_GoalPlayState        = GoalPlayState::POLE_DOWN;  //�S�[�����o�̃X�e�[�g
	const unsigned int M_POLE_STOP_WAIT_FRAME = 20;                        //�S�[�����o�Ń|�[���ɂ����݂��Ă���t���[����
	unsigned int       m_PoleStopWaitCounter  = 0;                         //�S�[�����o�Ń|�[���ɂ����݂��Ă���t���[���J�E���^

	const unsigned int M_DIE_MOVE_FRAME      = 360;                   //���S�����ɂ�����t���[����
	const unsigned int M_DIE_MOVE_STOP_FRAME = 60;                    //���S�����ōŏ��~�܂��Ă���t���[����
	unsigned int       m_DieMoveFrameCounter = 0;                     //���S�����Ŏg�p����t���[���J�E���^�[
	const float        M_DIE_MOVE_SPEED_MAX  = 0.02f;                 //���S�����Ń|�[�����痎���鑬�x�ő�l
	float              m_DieMoveNowSpeed     = M_DIE_MOVE_SPEED_MAX;  //���S�����Ń|�[�����痎���鑬�x
	float              m_DieMoveChangeAmount = 0.0005f;               //���S�����̈ړ��ʂ̕ϓ��l



/*------IMoveObj------*/
public:
	void Move();  //�v���C���[�̓���

public:
	/* getter */
	MoveObjState GetMoveObjState()const { return m_MoveObjState; }
	InputFlag    GetInputFlag   ()const { return m_InputFlag; }
	float        GetNowWalkSpeed()const { return m_NowWalkSpeed; }
	/* setter */
	void         SetMoveObjState(MoveObjState value) { m_MoveObjState = value; }
	void         SetInputFlag   (InputFlag    value) { if (!m_GoalPlayFlag) { m_InputFlag = value; } }

private:
	void Walk(float xAmount);  //����
	bool Jump(const unsigned int MAX_FRAME);               //�W�����v
	void Fall();               //����

private:
	bool          m_LivingFlag  = true;  //�����Ă��邩�̃t���O
	
	MoveObjState m_MoveObjState = MoveObjState::ON_THE_GROUND;  //�v���C���[�̃X�e�[�g

	InputFlag    m_InputFlag;  //���݂̓��͏��

	float        m_MaxWalkSpeed          = 0.003f;   //�����ő�X�s�[�h
	float        m_WalkFluctuationAmount = 0.0005f;  //�����X�s�[�h��ς���
	float        m_NowWalkSpeed          = 0.0f;     //���̕������x

	float        m_SlipStopAmount    = 0.0001f;  //�����}������l
	float        m_SlipStopThreshold = 0.001f;   //������O�ɂ��邵�����l


/*------RenderObj------*/
public:
	void ThisObjRender();
	void ThisObjCreateBuffer();

private:
	void Abstract() {};
};