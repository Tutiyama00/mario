#pragma once

#include"Vertex.h"

//前方宣言
class Player;
class InputFlag;
class Enemy;

//プレイヤー以外のオブジェクトに継承させる
class NotPlayer : public Square
{
public:
	NotPlayer(Vector3 pos, Vector2 size) : Square(pos, size) {};
	~NotPlayer() {};
	virtual void CheckPlayer(Player* pPlayer) = 0;
	virtual void CheckEnemy (Enemy* pEnemy)   = 0;

protected:
	virtual void Abstract() = 0;  //純粋仮想関数（これによってこのクラスはインスタンスできない)

	bool LeftCheck (Square* pSquare);
	bool RightCheck(Square* pSquare);
	bool DownCheck (Square* pSquare);
	bool UpCheck   (Square* pSquare);

	bool LeftCheck (Square* pSquare, float threshold);
	bool RightCheck(Square* pSquare, float threshold);
	bool DownCheck (Square* pSquare, float threshold);
	bool UpCheck   (Square* pSquare, float threshold);

protected:
	float m_Threshold = 0.025f; //衝突判定時に使用する判定の調整値（値が大きくなれば判定も甘くなる）
};