#pragma once

#include"Enemy.h"

class Kuribo : public Enemy
{
public:
	Kuribo(Vector3 pos, Vector2 size);
	~Kuribo() {};

protected:
	/*---Enemy---*/
	void Abstract() {};
};