#pragma once

#include"IGameScene.h"
#include<d3d11.h>

class Timer;
class TextCharacters;
class Image;

class ParameterScene : public IGameScene
{
public:
	ParameterScene(ID3D11Device* pDevice, GameState nowGameState);
	~ParameterScene();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag, Dx11* pDx11);  //���̃V�[�����X�V����B�߂�l�́A���ɍs���ׂ��X�e�[�g

private:
	Timer*          m_pTimer             = nullptr;
	TextCharacters* m_pTextOfMARIO       = nullptr;
	TextCharacters* m_pTextOfWORLD       = nullptr;
	TextCharacters* m_pTextOfTIME        = nullptr;
	TextCharacters* m_pTextOfTimeNamber  = nullptr;
	TextCharacters* m_pTextOfCoinNamber  = nullptr;
	TextCharacters* m_pTextOfScoreNamber = nullptr;
	Image*          m_pImageOfCoin       = nullptr;

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag, ID3D11Device* pDevice);
	void Draw(Dx11* pDx11);

protected:
	//---IGameScene---
	GameState m_NextGameState;
};