#pragma once

#include"IGameScene.h"
#include<d3d11.h>

//�O���錾
class Dx11;
class Camera;
class TextCharacters;
class Image;

class TitleScene : public IGameScene
{
public:
	TitleScene();
	~TitleScene();

private:
	Camera*         m_pCamera         = nullptr;
	TextCharacters* m_pTextCharacters = nullptr;
	Image*          m_pImageOfTitle   = nullptr;


/*------IGameScene------*/
public:
	GameState UpDateScene(InputFlag inputFlag);  //���̃V�[�����X�V����B�߂�l�́A���ɍs���ׂ��X�e�[�g

protected:
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	GameState m_NextGameState;
};
