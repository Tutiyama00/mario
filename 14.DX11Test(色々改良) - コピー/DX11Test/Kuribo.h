#pragma once

#include"Enemy.h"
#include"IMoveObj.h"

class Kuribo : public Enemy/*, public IMoveObj*/
{
public:
	Kuribo(Vector3 pos, Vector2 size);
	~Kuribo() {};

	/*---IMoveObj---*/
	void Move(InputFlag* inputFlag);

protected:
	/*---Enemy---*/
	void Abstract() {};
};