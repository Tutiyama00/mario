#pragma once

#include"IGameScene.h"
#include<d3d11.h>

//前方宣言
class Title;
class Dx11;
class Camera;

class TitleScene : public IGameScene
{
public:
	TitleScene(ID3D11Device* pDevice);
	~TitleScene();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag,Dx11* pDx11);  //このシーンを更新する。戻り値は、次に行くべきステート

private:
	Camera* m_pCamera = nullptr;
	Title*  m_pTitle  = nullptr;

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag);
	void Draw(Dx11* pDx11);

protected:
	//---IGameScene---
	GameState m_NextGameState;
};
