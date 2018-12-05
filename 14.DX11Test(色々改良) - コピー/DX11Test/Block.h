#pragma once

#include"Vertex.h"
#include"NotPlayer.h"
#include"Math.h"

using namespace OriginalMath;

//�O���錾
class InputFlag;

class Block : public NotPlayer
{
public:
	Block(Vector3 pos, Vector2 size);
	~Block() {};

	/*---NotPlayer---*/
	void CheckPlayer(Player* pPlayer);
	void CheckEnemy (Enemy*  pEnemy );

protected:
	void Abstract() {};
};