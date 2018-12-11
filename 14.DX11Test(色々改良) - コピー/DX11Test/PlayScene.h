#pragma once

#include"IGameScene.h"
#include<d3d11.h>
#include"Stage.h"
#include"Player.h"
#include<vector>

using namespace std;

class Camera;
template<class T> class Characters;
class Block;
class Goal;
class Kuribo;
class Nokonoko;

class PlayScene : public IGameScene
{
public:
	PlayScene();
	~PlayScene();

	void KillPlayer();

public:
	/* getter */
	const Player*  GetPlayer       ()const { return m_pPlayer; }
	const int      GetNowWorldLevel()const { return m_NowWorldLevel; }
	const int      GetNowStageLevel()const { return m_NowStageLevel; }
	const DWORD    GetStageTime    ()const { return m_pStage->GetStageTime(); }

private:
	void MakeStageObj  ();  //�X�e�[�W�I�u�W�F�N�g�̐���
	void ReStart       ();  //�Q�[���̃��X�^�[�g
	void ReSet         ();  //�Q�[���̃��Z�b�g
	void MoveScene     ();  //�V�[���̑J��
	void StageObjDelete();  //�X�e�[�W��̃I�u�W�F�N�g�̃f���[�g
	void MoveOrder     ();  //�L�����B�̈ړ�����
	void ObjCheckOrder ();  //�L�����B�̃`�F�b�N����

private:
	Stage*             m_pStage        = nullptr;
	Camera*            m_pCamera       = nullptr;
	Player*            m_pPlayer       = nullptr;
	Characters<Block>* m_pBlocks       = nullptr;
	Goal*              m_pGoal         = nullptr;
	vector<Kuribo*>    m_pKuriboVector;
	vector<Nokonoko*>  m_pNokonokoVector;

	float     m_StandardSize    = 0.075f;  //��̃T�C�Y
	float     m_StandardZpos    = -0.5f;   //��̃I�u�W�F�N�gZ�|�W�V����
	UINT      m_OldPlayerLife   = 0;       //�v���C���[�̎c�@�ۑ��p�ϐ�
	float     m_UnderDeathLine  = 0;       //��ʉ��̎��S���胉�C��
	int       m_NowWorldLevel   = 0;       //���݂̃��[���h
	int       m_NowStageLevel   = 0;       //���݂̃X�e�[�W
	const int M_IN_STAGE_AMOUNT = 4;       //��̃��[���h�ɂ���ʂ̐�


/*------IGameScene------*/
public:
	GameState UpDateScene(InputFlag inputFlag);  //���̃V�[�����X�V����B�߂�l�́A���ɍs���ׂ��X�e�[�g

protected:
	void UpDateGame(InputFlag inputFlag);
	void Draw();

protected:
	GameState m_NextGameState;
};
