#pragma once

#include"Enemy.h"

/* 前方宣言 */
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
	const unsigned char M_STATE_KEEP_FLAME    = 10;       //ステートの変わり目に判定の甘さを入れるフレーム数
	unsigned char       m_StateKeepFlameCount = 0;        //ステートの変わり目に判定の甘さを入れるフレームカウント
	bool                m_StateKeepFlag       = false;    //ステートの変わり目中かどうかのフラグ
	Animation*          m_pWalkAnimation      = nullptr;  //歩くアニメーション


/*------Enemy------*/
public:
	void Move()override;
	void CheckPlayer(Player* pPlayer)override;
	void CheckEnemy(Enemy* pEnemy)override;
	void ThisObjRender()override;
	void StartStandardDie(bool direction)override;

protected:
	void Abstract()override {};
};