#pragma once

enum class GameState : unsigned char;
class InputFlag;
class Dx11;

class IGameScene
{
public:
	virtual GameState UpDateScene(InputFlag inputFlag, Dx11* pDx11) = 0;

protected:
	virtual void UpDateGame(InputFlag inputFlag)  = 0;
	virtual void Draw(Dx11* pDx11)        = 0;

protected:
	GameState m_NextGameState;
};