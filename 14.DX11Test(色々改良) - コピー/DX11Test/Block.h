#pragma once

#include"Vertex.h"
#include"INotPlayer.h"
#include"Math.h"

using namespace OriginalMath;

//ëOï˚êÈåæ
class InputFlag;

class Block : public Square,public INotPlayer
{
public:
	Block(Vector3 pos, Vector2 size);
	~Block();

	//---INotPlayer---
	void CheckPlayer(Player* pPlayer,InputFlag* pInputFlag);

public:
	float m_Threshold = 0.025f;

private:
	bool LeftCheck(Player* pPlayer, InputFlag* pInputFlag);
	bool RightCheck(Player* pPlayer, InputFlag* pInputFlag);
	bool DownCheck(Player* pPlayer, InputFlag* pInputFlag);
	bool UpCheck(Player* pPlayer, InputFlag* pInputFlag);
};