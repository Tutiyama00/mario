#pragma once

#include"Enemy.h"
#include"IMoveObj.h"

/* ‘O•ûéŒ¾ */
class Animation;

class Kuribo : public Enemy
{
public:
	Kuribo(Vector3 pos, Vector2 size);
	~Kuribo() {};

	/*---Enemy---*/
	void Move();

private:
	Animation* m_pWalkAnimation = nullptr;

protected:
	/*---Enemy---*/
	void Abstract() {};
};