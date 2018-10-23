#pragma once

#include<d3d11.h>

//前方宣言
class Player;
class InputFlag;

//##############インターフェース#########################

//プレイヤー以外のオブジェクトに継承させる
class INotPlayer
{
public:
	virtual ~INotPlayer() {};
	virtual void CheckPlayer(Player* player, InputFlag* pInputFlag) = 0;
};