#pragma once

#include"Enemy.h"
#include"IMoveObj.h"

class Kuribo : public Enemy, public IMoveObj
{
public:
	Kuribo(Vector3 pos, Vector2 size);
	~Kuribo() {};

	/*---IMoveObj---*/
	void Move();

private:
	/*---IMoveObj---*/
	void Walk(float xAmount);      //歩く
	bool Jump() { return false; };  //ジャンプ
	void Fall();                   //落下

protected:
	/*---Enemy---*/
	void Abstract() {};
};