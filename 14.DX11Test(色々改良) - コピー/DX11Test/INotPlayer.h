#pragma once

//前方宣言
class Player;
class InputFlag;
class Enemy;
class Square;

//プレイヤー以外のオブジェクトに継承させる
class INotPlayer
{
public:
	virtual ~INotPlayer() {};
	virtual void CheckPlayer(Player* pPlayer) = 0;
	virtual void CheckEnemy (Enemy* pEnemy)   = 0;
};