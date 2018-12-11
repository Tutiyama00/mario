#pragma once

#include"IGameScene.h"
#include<d3d11.h>
#include"Flag.h"
#include"Timer.h"

class Timer;
class TextCharacters;
class Image;

class ParameterScene : public IGameScene
{
public:
	ParameterScene(GameState nowGameState);
	~ParameterScene();

	void ChangeWorldNamber(int worldNamber, int stageNamber);
	void StopTimer();
	void StartTimer();
	void SetTimer(DWORD time);
	DWORD GetNowTime() { return m_pTimer->GetCount(); }

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


/*------IGameScene------*/
public:
	GameState UpDateScene(InputFlag inputFlag);  //このシーンを更新する。戻り値は、次に行くべきステート

protected:
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	GameState m_NextGameState;
};