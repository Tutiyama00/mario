#pragma once

#include"Enemy.h"
#include"IMoveObj.h"

/* �O���錾 */
class Animation;

class Kuribo : public Enemy
{
public:
	Kuribo(Vector3 pos, Vector2 size);
	~Kuribo();

private:
	Animation* m_pWalkAnimation = nullptr;


/*---Enemy---*/
public:
	void Move();
	void ThisObjRender();

protected:
	void Abstract() {};
};