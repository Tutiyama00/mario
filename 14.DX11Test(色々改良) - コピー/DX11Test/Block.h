#pragma once

#include"Vertex.h"
#include"INotPlayer.h"

//ëOï˚êÈåæ
class InputFlag;

class Block : public Square,public INotPlayer
{
public:
	Block(float xPos, float yPos, float zPos, float xSize, float ySize);
	~Block();

	void CheckPlayer(Player* pPlayer,InputFlag* pInputFlag);

public:
	float m_Threshold = 0.025f;

private:
	bool LeftCheck(Player* pPlayer, InputFlag* pInputFlag);
	bool RightCheck(Player* pPlayer, InputFlag* pInputFlag);
	bool DownCheck(Player* pPlayer, InputFlag* pInputFlag);
	bool UpCheck(Player* pPlayer, InputFlag* pInputFlag);
};