#pragma once

#include"Enemy.h"

/* �O���錾 */
class Animation;

enum class NokonokoState : unsigned char
{
	NORMAL,
	KOURA_STOP,
	KOURA_RUN
};

class Nokonoko : public Enemy
{
public:
	Nokonoko(Vector3 pos, Vector2 size);
	~Nokonoko();

public:
	/* getter */
	NokonokoState GetNokonokoState()const { return m_NokonokoState; }

private:
	void StateKeepFlameStart();
	void StateKeepFlame();

private:
	NokonokoState       m_NokonokoState       = NokonokoState::NORMAL;
	const unsigned char M_STATE_KEEP_FLAME    = 10;       //�X�e�[�g�̕ς��ڂɔ���̊Â�������t���[����
	unsigned char       m_StateKeepFlameCount = 0;        //�X�e�[�g�̕ς��ڂɔ���̊Â�������t���[���J�E���g
	bool                m_StateKeepFlag       = false;    //�X�e�[�g�̕ς��ڒ����ǂ����̃t���O
	Animation*          m_pWalkAnimation      = nullptr;  //�����A�j���[�V����


/*------Enemy------*/
public:
	void Move();
	virtual void CheckPlayer(Player* pPlayer);
	virtual void CheckEnemy(Enemy* pEnemy);
	void ThisObjRender();

protected:
	void Abstract() {};
};