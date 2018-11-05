#pragma once

#include"IGameScene.h"
#include<d3d11.h>

class ResultScene : public IGameScene
{
public:
	ResultScene(ID3D11Device* pDevice, GameState nowGameState);
	~ResultScene();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag, Dx11* pDx11);  //���̃V�[�����X�V����B�߂�l�́A���ɍs���ׂ��X�e�[�g

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag);
	void Draw(Dx11* pDx11);

protected:
	//---IGameScene---
	GameState m_NextGameState;
};