#pragma once

#include"INotPlayer.h"
#include"Vertex.h"
#include"RenderObj.h"
#include"IMoveObj.h"

class Enemy : public Square, public RenderObj, public INotPlayer, public IMoveObj
{
public:
	Enemy(Vector3 pos, Vector2 size) : Square(pos, size) {};
	~Enemy() {};

	/*---INotPlayer---*/
	void CheckPlayer(Player* pPlayer);

	/*---RenderObj---*/
	void ThisObjRender();
	void ThisObjCreateBuffer();

	/*---IMoveObj---*/
	virtual void Move() = 0;

protected:
	virtual void Abstract() = 0;  //純粋仮想関数（これによってこのクラスはインスタンスできない)

	/*---IMoveObj---*/
	virtual void Walk(float xAmount);  //歩く
	virtual bool Jump();               //ジャンプ
	virtual void Fall();               //落下
};