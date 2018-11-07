#pragma once

#include"IGameScene.h"
#include<d3d11.h>

class Image;
class TextCharacters;

class ResultScene : public IGameScene
{
public:
	ResultScene(ID3D11Device* pDevice,UINT playerLife);
	~ResultScene();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag, Dx11* pDx11);  //���̃V�[�����X�V����B�߂�l�́A���ɍs���ׂ��X�e�[�g

private:
	Image*          m_pImageOfMario    = nullptr;
	TextCharacters* m_pTextOfWORLD     = nullptr;
	TextCharacters* m_pTextOfMarioLife = nullptr;

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag, ID3D11Device* pDevice);
	void Draw(Dx11* pDx11);

protected:
	//---IGameScene---
	GameState m_NextGameState;
};