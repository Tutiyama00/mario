#pragma once

#include<d3d11.h>

enum class GameState : unsigned char;
class InputFlag;
class Dx11;

class IGameScene
{
public:
	virtual GameState UpDateScene(InputFlag inputFlag) = 0;

protected:
	virtual void UpDateGame(InputFlag inputFlag) = 0;
	virtual void Draw()                          = 0;

protected:
	GameState m_NextGameState;
};