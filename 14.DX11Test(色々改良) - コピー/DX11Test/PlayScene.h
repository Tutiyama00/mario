#pragma once

#include"IGameScene.h"
#include<d3d11.h>
#include"Stage.h"

class Camera;
class Player;
template<class T> class Characters;
class Block;
class Goal;

class PlayScene : public IGameScene
{
public:
	PlayScene();
	~PlayScene();

	GameState KillPlayer();

	//---IGameScene---
	GameState UpDateScene(InputFlag inputFlag);  //���̃V�[�����X�V����B�߂�l�́A���ɍs���ׂ��X�e�[�g

public:
	/* getter */
	Player* GetPlayer()        { return m_pPlayer; }
	int     GetNowWorldLevel() { return m_NowWorldLevel; }
	int     GetNowStageLevel() { return m_NowStageLevel; }
	DWORD   GetStageTime()     { return m_pStage->GetStageTime(); }

private:
	void MakeStageObj();
	void ReStart     ();
	void ReSet       ();

private:
	Stage*             m_pStage        = nullptr;
	Camera*            m_pCamera       = nullptr;
	Player*            m_pPlayer       = nullptr;
	Characters<Block>* m_pBlocks       = nullptr;
	Goal*              m_pGoal         = nullptr;

	float     m_StandardSize    = 0.075f;  //��̃T�C�Y
	float     m_StandardZpos    = -0.5f;   //��̃I�u�W�F�N�gZ�|�W�V����
	UINT      m_OldPlayerLife   = 0;       //�v���C���[�̎c�@�ۑ��p�ϐ�
	float     m_UnderDeathLine  = 0;       //��ʉ��̎��S���胉�C��
	int       m_NowWorldLevel   = 0;       //���݂̃��[���h
	int       m_NowStageLevel   = 0;       //���݂̃X�e�[�W
	const int M_IN_STAGE_AMOUNT = 4;       //��̃��[���h�ɂ���ʂ̐�

protected:
	//---IGameScene---
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	//---IGameScene---
	GameState m_NextGameState;
};
