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

	void ChangeWorldNamber(int worldNamber, int stageNamber, ID3D11Device* pDevice);
	void ChangeMarioLife(UINT playerLife, ID3D11Device* pDevice);

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag, Dx11* pDx11);  //このシーンを更新する。戻り値は、次に行くべきステート

private:
	Image*          m_pImageOfMario      = nullptr;
	TextCharacters* m_pTextOfWORLD       = nullptr;
	TextCharacters* m_pTextOfWorldNamber = nullptr;
	TextCharacters* m_pTextOfMarioLife   = nullptr;

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag, ID3D11Device* pDevice);
	void Draw(Dx11* pDx11);

protected:
	//---IGameScene---
	GameState m_NextGameState;
};