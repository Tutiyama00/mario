#pragma once

#include"INotPlayer.h"
#include"Vertex.h"
#include"RenderObj.h"

class Enemy : public Square, public RenderObj, public INotPlayer
{
public:
	Enemy(Vector3 pos, Vector2 size) : Square(pos, size) {};
	~Enemy() {};

	/*---INotPlayer---*/
	void CheckPlayer(Player* pPlayer, InputFlag* pInputFlag);

	/*---RenderObj---*/
	void ThisObjRender();
	void ThisObjCreateBuffer();

protected:
	virtual void Abstract() = 0;  //純粋仮想関数（これによってこのクラスはインスタンスできない)
};