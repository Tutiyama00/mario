#pragma once

#include<d3d11.h>

//�O���錾
class Player;
class InputFlag;

//##############�C���^�[�t�F�[�X#########################

//�v���C���[�ȊO�̃I�u�W�F�N�g�Ɍp��������
class INotPlayer
{
public:
	virtual ~INotPlayer() {};
	virtual void CheckPlayer(Player* player, InputFlag* pInputFlag) = 0;
};