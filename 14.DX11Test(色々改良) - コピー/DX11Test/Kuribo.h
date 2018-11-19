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
	void Walk(float xAmount);      //����
	bool Jump() { return false; };  //�W�����v
	void Fall();                   //����

protected:
	/*---Enemy---*/
	void Abstract() {};
};