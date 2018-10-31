#pragma once

#include"IGameScene.h"
#include<d3d11.h>

//�O���錾
class Title;
class Dx11;
class Camera;
class TextChar;
class TextCharacters;

class TitleScene : public IGameScene
{
public:
	TitleScene(ID3D11Device* pDevice);
	~TitleScene();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag,Dx11* pDx11);  //���̃V�[�����X�V����B�߂�l�́A���ɍs���ׂ��X�e�[�g

private:
	Camera* m_pCamera = nullptr;
	Title*  m_pTitle  = nullptr;
	TextChar* m_pTextChar = nullptr;
	TextCharacters* m_pTextCharacters = nullptr;

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag);
	void Draw(Dx11* pDx11);

protected:
	//---IGameScene---
	GameState m_NextGameState;
};
