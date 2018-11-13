#pragma once

#include"IGameScene.h"
#include<d3d11.h>

class Timer;
class TextCharacters;
class Image;

class ParameterScene : public IGameScene
{
public:
	ParameterScene(GameState nowGameState);
	~ParameterScene();

	void ChangeWorldNamber(int worldNamber, int stageNamber);

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag);  //���̃V�[�����X�V����B�߂�l�́A���ɍs���ׂ��X�e�[�g

private:
	Timer*          m_pTimer             = nullptr;
	TextCharacters* m_pTextOfMARIO       = nullptr;
	TextCharacters* m_pTextOfWORLD       = nullptr;
	TextCharacters* m_pTextOfWorldNamber = nullptr;
	TextCharacters* m_pTextOfTIME        = nullptr;
	TextCharacters* m_pTextOfTimeNamber  = nullptr;
	TextCharacters* m_pTextOfCoinNamber  = nullptr;
	TextCharacters* m_pTextOfScoreNamber = nullptr;
	Image*          m_pImageOfCoin       = nullptr;

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	//---IGameScene---
	GameState m_NextGameState;
};