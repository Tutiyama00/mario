#pragma once

#include"Vertex.h"
#include"NotPlayer.h"
#include"Math.h"

using namespace OriginalMath;

//‘O•ûéŒ¾
class InputFlag;

class Block : public NotPlayer
{
public:
	Block(Vector3 pos, Vector2 size);
	~Block() {};

protected:
	void Abstract() {};


/*------NotPlayer------*/
public:
	void CheckPlayer(Player* pPlayer);
	void CheckEnemy(Enemy*  pEnemy);
};