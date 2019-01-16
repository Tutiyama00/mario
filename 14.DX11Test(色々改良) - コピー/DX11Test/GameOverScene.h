#pragma once

#include<d3d11.h>
#include"IGameScene.h"

class Dx11;
class Camera;
class TextCharacters;


class GameOverScene : public IGameScene
{
public:
	GameOverScene();
	~GameOverScene();

private:
	Camera*         m_pCamera         = nullptr;
	TextCharacters* m_pTextCharacters = nullptr;

	unsigned int m_FlameCount = 0;  //シーンを遷移させるまでのカウント
	const unsigned int M_CHANGE_FLAME_COUNT = 480;


/*------IGameScene------*/
public:
	GameState UpDateScene(InputFlag inputFlag);  //このシーンを更新する。戻り値は、次に行くべきステート

protected:
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	GameState m_NextGameState;
};