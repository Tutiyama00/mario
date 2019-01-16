#pragma once

#include"Enemy.h"
#include"IMoveObj.h"

/* 前方宣言 */
class Animation;
class Player;

class Kuribo : public Enemy
{
public:
	Kuribo(Vector3 pos, Vector2 size);
	~Kuribo();

private:
	Animation* m_pWalkAnimation = nullptr;
	bool m_StompDieFlag = false;  //踏まれて死んだかのフラグ
	const unsigned int M_STOMP_RENDER_FRAME = 120;  //踏まれたときに消えるまでのフレーム数
	unsigned int m_StompRenderFrameCounter = 0;  //踏まれたときに消えるまでのフレーム数のカウンター

/*---Enemy---*/
public:
	void Move();
	void ThisObjRender();
    void Die();
	void CheckPlayer(Player* pPlayer);

protected:
	void Abstract() {};
};