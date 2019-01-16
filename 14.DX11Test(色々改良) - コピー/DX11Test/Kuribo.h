#pragma once

#include"Enemy.h"
#include"IMoveObj.h"

/* �O���錾 */
class Animation;
class Player;

class Kuribo : public Enemy
{
public:
	Kuribo(Vector3 pos, Vector2 size);
	~Kuribo();

private:
	Animation* m_pWalkAnimation = nullptr;
	bool m_StompDieFlag = false;  //���܂�Ď��񂾂��̃t���O
	const unsigned int M_STOMP_RENDER_FRAME = 120;  //���܂ꂽ�Ƃ��ɏ�����܂ł̃t���[����
	unsigned int m_StompRenderFrameCounter = 0;  //���܂ꂽ�Ƃ��ɏ�����܂ł̃t���[�����̃J�E���^�[

/*---Enemy---*/
public:
	void Move();
	void ThisObjRender();
    void Die();
	void CheckPlayer(Player* pPlayer);

protected:
	void Abstract() {};
};