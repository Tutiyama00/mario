#pragma once

#include"Vertex.h"

//�O���錾
class Player;
class InputFlag;
class Enemy;

//�v���C���[�ȊO�̃I�u�W�F�N�g�Ɍp��������
class NotPlayer : public Square
{
public:
	NotPlayer(Vector3 pos, Vector2 size) : Square(pos, size) {};
	~NotPlayer() {};
	virtual void CheckPlayer(Player* pPlayer) = 0;
	virtual void CheckEnemy (Enemy* pEnemy)   = 0;

protected:
	virtual void Abstract() = 0;  //�������z�֐��i����ɂ���Ă��̃N���X�̓C���X�^���X�ł��Ȃ�)

	bool LeftCheck (Square* pSquare);
	bool RightCheck(Square* pSquare);
	bool DownCheck (Square* pSquare);
	bool UpCheck   (Square* pSquare);

	bool LeftCheck (Square* pSquare, float threshold);
	bool RightCheck(Square* pSquare, float threshold);
	bool DownCheck (Square* pSquare, float threshold);
	bool UpCheck   (Square* pSquare, float threshold);

protected:
	float m_Threshold = 0.025f; //�Փ˔��莞�Ɏg�p���锻��̒����l�i�l���傫���Ȃ�Δ�����Â��Ȃ�j
};