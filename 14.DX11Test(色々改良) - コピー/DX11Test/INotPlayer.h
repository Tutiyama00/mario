#pragma once

//�O���錾
class Player;
class InputFlag;
class Enemy;
class Square;

//�v���C���[�ȊO�̃I�u�W�F�N�g�Ɍp��������
class INotPlayer
{
public:
	virtual ~INotPlayer() {};
	virtual void CheckPlayer(Player* pPlayer) = 0;
	virtual void CheckEnemy (Enemy* pEnemy)   = 0;
};