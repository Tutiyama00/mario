#pragma once

#include"IGameScene.h"
#include<d3d11.h>

class Camera;
class Player;
template<class T> class Characters;
class Block;
class Stage;
class DeathChecker;

class PlayScene : public IGameScene
{
public:
	PlayScene(ID3D11Device* pDevice);
	~PlayScene();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag, Dx11* pDx11);  //このシーンを更新する。戻り値は、次に行くべきステート

public:
	Player* GetPlayer() { return m_pPlayer; }

private:
	void MakeStageObj(ID3D11Device* pDevice);
	void ReStart(ID3D11Device* pDevice);

private:
	Stage*             m_pStage        = nullptr;
	Camera*            m_pCamera       = nullptr;
	Player*            m_pPlayer       = nullptr;
	Characters<Block>* m_pBlocks       = nullptr;
	DeathChecker*      m_pDeathChecker = nullptr;

	float m_StandardSize = 0.1f;
	float m_StandardZpos = -0.5f;

	UINT m_OldPlayerLife = 0;

	float m_UnderDeathLine = 0;  //画面下の死亡判定ライン

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag, ID3D11Device* pDevice);
	void Draw(Dx11* pDx11);

protected:
	//---IGameScene---
	GameState m_NextGameState;
};
