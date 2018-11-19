#pragma once

#include"Enemy.h"
#include"MoveObj.h"

class Kuribo : public Enemy, public MoveObj
{
public:
	Kuribo(Vector3 pos, Vector2 size);
	~Kuribo() {};

	/*---IMoveObj---*/
	void Move();

protected:
	/*---Enemy---*/
	void Abstract() {};
};