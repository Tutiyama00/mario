#pragma once

//前方宣言
class Player;
class InputFlag;

//プレイヤー以外のオブジェクトに継承させる
class INotPlayer
{
public:
	virtual ~INotPlayer() {};
	virtual void CheckPlayer(Player* player, InputFlag* pInputFlag) = 0;
};