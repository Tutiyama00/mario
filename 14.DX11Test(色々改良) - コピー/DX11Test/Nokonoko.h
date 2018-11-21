#pragma once

#include"Enemy.h"

class Nokonoko : public Enemy
{
public:
	Nokonoko(Vector3 pos, Vector2 size);
	~Nokonoko() {};

	/*---Enemy---*/
	void Move();

protected:
	/*---Enemy---*/
	void Abstract() {};
};