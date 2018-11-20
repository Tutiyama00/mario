#pragma once

#include"Enemy.h"
#include"IMoveObj.h"

class Kuribo : public Enemy
{
public:
	Kuribo(Vector3 pos, Vector2 size);
	~Kuribo() {};

	/*---Enemy---*/
	void Move();

protected:
	/*---Enemy---*/
	void Abstract() {};
};