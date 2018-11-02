#pragma once

#include"IGameScene.h"
#include<d3d11.h>

class Timer;
class TextCharacters;

class ParameterScene : public IGameScene
{
public:
	ParameterScene(ID3D11Device* pDevice, GameState nowGameState);
	~ParameterScene();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag, Dx11* pDx11);  //このシーンを更新する。戻り値は、次に行くべきステート

private:
	Timer*          m_pTimer       = nullptr;
	TextCharacters* m_pTextOfMARIO = nullptr;
	TextCharacters* m_pTextOfWORLD = nullptr;
	TextCharacters* m_pTextOfTIME  = nullptr;
	TextCharacters* m_pTextOfTimeNamber = nullptr;

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag);
	void Draw(Dx11* pDx11);

protected:
	//---IGameScene---
	GameState m_NextGameState;
};