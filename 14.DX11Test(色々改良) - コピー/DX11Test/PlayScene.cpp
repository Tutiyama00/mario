#include"PlayScene.h"
#include"Stage.h"
#include"Camera.h"
#include"Player.h"
#include"Flag.h"
#include"Characters.h"
#include"Block.h"
#include"Dx11.h"
#include"Math.h"
#include"Goal.h"
#include<string>

using namespace OriginalMath;

/*�R���X�g���N�^*/
PlayScene::PlayScene(ID3D11Device* pDevice)
{
	m_NextGameState = GameState::PLAY;
	m_NowWorldLevel = 1;
	m_NowStageLevel = 1;

	std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //�X�e�[�W�̃t�@�C���p�X

	m_pStage  = new Stage(filePas.data());
	m_pCamera = new Camera(pDevice);
	MakeStageObj(pDevice);

	m_pPlayer->SetLife(m_pPlayer->GetSTART_LIFE());
}

/*�f�X�g���N�^*/
PlayScene::~PlayScene()
{
	if (m_pStage        != nullptr) { delete m_pStage;        m_pStage        = nullptr; }
	if (m_pCamera       != nullptr) { delete m_pCamera;       m_pCamera       = nullptr; }
	if (m_pPlayer       != nullptr) { delete m_pPlayer;       m_pPlayer       = nullptr; }
	if (m_pBlocks       != nullptr) { delete m_pBlocks;       m_pBlocks       = nullptr; }
	if (m_pGoal         != nullptr) { delete m_pGoal;         m_pGoal         = nullptr; }
}

/*�X�e�[�W��̃I�u�W�F�N�g�̐���*/
void PlayScene::MakeStageObj(ID3D11Device* pDevice)
{
	m_pBlocks = new Characters<Block>(pDevice, L"Texture/Block2.png", L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");

	//.5���؂�グ�ɂȂ�̂ŏc���i��O��j�̒��Ԓl���擾�ł���
	int halfHeight = m_pStage->GetStageHeight() / 2;

	//�X�e�[�W��񂩂琶������I�u�W�F�N�g�𔻕�
	for (int height = 0; height < m_pStage->GetStageHeight(); height++)
	{
		for (int width = 0; width < m_pStage->GetStageWidth(); width++)
		{
			//�����ʒu�̃|�W�V�����̌v�Z
			float xPos = m_StandardSize * width;
			float yPos = m_StandardSize * -(height - halfHeight);

			Vector3 pos  = { xPos,yPos,m_StandardZpos };
			Vector2 size = { m_StandardSize, m_StandardSize };

			//�X�C�b�`���Ŕ���
			switch (*(m_pStage->m_pStageDataArray + (height*m_pStage->GetStageWidth() + width)))
			{
			case Object::MARIO:

				m_pPlayer = new Player(pos, size, pDevice);
				break;
			case Object::NORMAL_BLOCK:

				m_pBlocks->m_ObjectVector.push_back(new Block(pos, size));
				break;
			}
		}
	}

	Vector3 pos = { 1.75f,-0.115f,m_StandardZpos };
	Vector2 size = { 0.75f,0.75f };

	m_pGoal = new Goal(pos, size, pDevice);

	m_pBlocks->ThisObjCreateBuffer(pDevice);

	/*���̎��S���胉�C���̌v�Z*/
	m_UnderDeathLine = m_StandardSize * -(m_pStage->GetStageHeight() - halfHeight);
}

GameState PlayScene::UpDateScene(InputFlag inputFlag, Dx11* pDx11)
{
	UpDateGame(inputFlag,pDx11->m_pDevice);

	/*ReStart()��������ɕ`�������ƈ�u������Ԃ��f�荞��ł��܂����ߏ����ǉ�*/
	if (m_NextGameState == GameState::PLAY)
	{
		Draw(pDx11);
	}

	return m_NextGameState;
}

void PlayScene::UpDateGame(InputFlag inputFlag,ID3D11Device* pDevice)
{
	m_NextGameState = GameState::PLAY;

	//�u���b�N�Q�̃v���C���[�ɑ΂��ďՓ˔���
	for (int i = 0; i < m_pBlocks->m_ObjectVector.size(); i++)
	{
		m_pBlocks->m_ObjectVector[i]->CheckPlayer(m_pPlayer, &inputFlag);
	}

	//�v���C���[�ړ�
	m_pPlayer->Move(&inputFlag);

	/*�S�[���`�F�b�N*/
	if (m_pGoal->CollisionCheck(m_pPlayer))
	{
		m_NowStageLevel++;
		if (m_NowStageLevel > M_IN_STAGE_AMOUNT)
		{
			m_NowWorldLevel++;
			m_NowStageLevel = 1;
		}

		std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //�X�e�[�W�̃t�@�C���p�X

		m_pStage->ChangeStage(filePas.data());
		ReStart(pDevice);
		m_NextGameState = GameState::RESULT;
	}

	//�����`�F�b�N
	if (m_UnderDeathLine > m_pPlayer->GetyPos())
	{
		//�v���C���[�̎��S����
		m_pPlayer->Die();
		//�c��c�@���O��������Q�[���I�[�o�[��ʂɍs���A�܂��c�@���������烊�U���g�ɔ��
		if (m_pPlayer->GetLife() == 0)
		{
			ReSet(pDevice);
			m_NextGameState = GameState::GAMEOVER;
		}
		else
		{
			ReStart(pDevice);
			m_NextGameState = GameState::RESULT;
		}
	}
}

void PlayScene::Draw(Dx11* pDx11)
{
	m_pCamera->Shoot(pDx11->m_pDeviceContext, &pDx11->GetViewPort(), m_pPlayer->GetxPos());
	m_pPlayer->ThisObjRender(pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
	m_pBlocks->ThisObjRender(pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
	m_pGoal  ->ThisObjRender(pDx11->m_pDeviceContext, pDx11->GetStrides(), pDx11->GetOffsets());
}

/*�Q�[���̃��X�^�[�g*/
void PlayScene::ReStart(ID3D11Device* pDevice)
{
	/*�Đ�����̃v���C���[�Ɏc�@��ݒ肷�邽�߂Ƀf���[�g�O�ɒl��ۑ�*/
	m_OldPlayerLife = m_pPlayer->GetLife();

	/*�X�e�[�W��̃I�u�W�F�N�g�̃f���[�g*/
	if (m_pPlayer       != nullptr) { delete m_pPlayer;       m_pPlayer       = nullptr; }
	if (m_pBlocks       != nullptr) { delete m_pBlocks;       m_pBlocks       = nullptr; }
	if (m_pGoal         != nullptr) { delete m_pGoal;         m_pGoal         = nullptr; }

	/*�X�e�[�W�I�u�W�F�N�g�Đ���*/
	MakeStageObj(pDevice);

	/*�v���C���[�̎c�@�ݒ�*/
	m_pPlayer->SetLife(m_OldPlayerLife);
}

/// <summary>
/// �Q�[����Ԃ̃��Z�b�g
/// </summary>
/// <param name="pDevice"></param>
void PlayScene::ReSet(ID3D11Device* pDevice)
{
	if (m_pPlayer != nullptr) { delete m_pPlayer;       m_pPlayer = nullptr; }
	if (m_pBlocks != nullptr) { delete m_pBlocks;       m_pBlocks = nullptr; }
	if (m_pGoal != nullptr) { delete m_pGoal;         m_pGoal = nullptr; }

	m_NowWorldLevel = 1;
	m_NowStageLevel = 1;

	std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //�X�e�[�W�̃t�@�C���p�X

	m_pStage->ChangeStage(filePas.data());
	MakeStageObj(pDevice);

	m_pPlayer->SetLife(m_pPlayer->GetSTART_LIFE());
}