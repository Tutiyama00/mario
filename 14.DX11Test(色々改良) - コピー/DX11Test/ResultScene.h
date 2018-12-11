#pragma once

#include"IGameScene.h"
#include<d3d11.h>

class Image;
class TextCharacters;

class ResultScene : public IGameScene
{
public:
	ResultScene(UINT playerLife);
	~ResultScene();

	void ChangeWorldNamber(int worldNamber, int stageNamber);
	void ChangeMarioLife(UINT playerLife);

private:
	Image*          m_pImageOfMario      = nullptr;
	TextCharacters* m_pTextOfWORLD       = nullptr;
	TextCharacters* m_pTextOfWorldNamber = nullptr;
	TextCharacters* m_pTextOfMarioLife   = nullptr;

	unsigned int m_FlameCount = 0;  //シーンを遷移させるまでのカウント
	const unsigned int M_CHANGE_FLAME_COUNT = 180;


/*------IGameScene------*/
public:
	GameState UpDateScene(InputFlag inputFlag);  //このシーンを更新する。戻り値は、次に行くべきステート

protected:
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	GameState m_NextGameState;
};