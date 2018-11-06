#pragma once

#include<d3d11.h>
#include"IGameScene.h"

class Dx11;
class Camera;
class TextCharacters;


class GameOverScene : public IGameScene
{
public:
	GameOverScene(ID3D11Device* pDevice);
	~GameOverScene();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag, Dx11* pDx11);  //このシーンを更新する。戻り値は、次に行くべきステート

private:
	Camera* m_pCamera = nullptr;
	TextCharacters* m_pTextCharacters = nullptr;

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag, ID3D11Device* pDevice);
	void Draw(Dx11* pDx11);

protected:
	//---IGameScene---
	GameState m_NextGameState;
};