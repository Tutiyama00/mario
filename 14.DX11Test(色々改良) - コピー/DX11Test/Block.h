#pragma once

#include"Vertex.h"
#include"INotPlayer.h"
#include"Math.h"

using namespace OriginalMath;

//前方宣言
class InputFlag;

class Block : public Square,public INotPlayer
{
public:
	Block(Vector3 pos, Vector2 size);
	~Block() {};

	//---INotPlayer---
	void CheckPlayer(Player* pPlayer);
	void CheckEnemy(Enemy* pEnemy);

private:
	bool LeftCheck (Square* pSquare);
	bool RightCheck(Square* pSquare);
	bool DownCheck (Square* pSquare);
	bool UpCheck   (Square* pSquare);

private:
	float m_Threshold = 0.025f; //衝突判定時に使用する判定の調整値（値が大きくなれば判定も甘くなる）
};