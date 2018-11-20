#pragma once

#include"Vertex.h"
#include"INotPlayer.h"
#include"Math.h"

using namespace OriginalMath;

//�O���錾
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
	float m_Threshold = 0.025f; //�Փ˔��莞�Ɏg�p���锻��̒����l�i�l���傫���Ȃ�Δ�����Â��Ȃ�j
};