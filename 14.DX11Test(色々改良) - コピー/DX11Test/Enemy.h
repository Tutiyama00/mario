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
	virtual void Abstract() = 0;  //�������z�֐��i����ɂ���Ă��̃N���X�̓C���X�^���X�ł��Ȃ�)

	/*---IMoveObj---*/
	virtual void Walk(float xAmount);  //����
	virtual bool Jump();               //�W�����v
	virtual void Fall();               //����
};