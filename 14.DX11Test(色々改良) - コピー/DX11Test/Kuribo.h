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
	void Walk(float xAmount);      //•à‚­
	bool Jump() { return false; };  //ƒWƒƒƒ“ƒv
	void Fall();                   //—Ž‰º

protected:
	/*---Enemy---*/
	void Abstract() {};
};