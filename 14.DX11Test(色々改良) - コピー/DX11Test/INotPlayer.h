#pragma once

//�O���錾
class Player;
class InputFlag;

//�v���C���[�ȊO�̃I�u�W�F�N�g�Ɍp��������
class INotPlayer
{
public:
	virtual ~INotPlayer() {};
	virtual void CheckPlayer(Player* player) = 0;
};