#pragma once

#include"IGameScene.h"
#include<d3d11.h>

//前方宣言
class Dx11;
class Camera;
class TextCharacters;
class Image;

class TitleScene : public IGameScene
{
public:
	TitleScene();
	~TitleScene();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag);  //このシーンを更新する。戻り値は、次に行くべきステート

private:
	Camera*         m_pCamera         = nullptr;
	TextCharacters* m_pTextCharacters = nullptr;
	Image*          m_pImageOfTitle   = nullptr;

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	//---IGameScene---
	GameState m_NextGameState;
};
