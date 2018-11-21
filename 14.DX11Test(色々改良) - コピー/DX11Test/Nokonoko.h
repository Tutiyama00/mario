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

protected:
	/*---Enemy---*/
	void Abstract() {};

	NokonokoState m_NokonokoState = NokonokoState::NORMAL;
};