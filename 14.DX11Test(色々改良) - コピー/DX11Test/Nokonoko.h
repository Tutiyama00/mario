#pragma once

#include"Enemy.h"

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
	~Nokonoko() {};

	/*---Enemy---*/
	void Move();
	virtual void CheckPlayer(Player* pPlayer);
	virtual void CheckEnemy(Enemy* pEnemy);

private:
	void StateKeepFlameStart();
	void StateKeepFlame();

private:
	NokonokoState       m_NokonokoState       = NokonokoState::NORMAL;
	const unsigned char M_STATE_KEEP_FLAME    = 5;      //ステートの変わり目に判定の甘さを入れるフレーム数
	unsigned char       m_StateKeepFlameCount = 0;      //ステートの変わり目に判定の甘さを入れるフレームカウント
	bool                m_StateKeepFlag       = false;  //ステートの変わり目中かどうかのフラグ

protected:
	/*---Enemy---*/
	void Abstract() {};
};