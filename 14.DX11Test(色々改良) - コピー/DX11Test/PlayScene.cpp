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
#include"Kuribo.h"

using namespace OriginalMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayScene::PlayScene()
{
	m_NextGameState = GameState::PLAY;
	m_NowWorldLevel = 1;
	m_NowStageLevel = 1;

	std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //�X�e�[�W�̃t�@�C���p�X

	m_pStage  = new Stage(filePas.data());
	m_pCamera = new Camera();
	MakeStageObj();

	m_pPlayer->SetLife(m_pPlayer->GetSTART_LIFE());
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{
	if (m_pStage        != nullptr) { delete m_pStage;        m_pStage        = nullptr; }
	if (m_pCamera       != nullptr) { delete m_pCamera;       m_pCamera       = nullptr; }
	if (m_pPlayer       != nullptr) { delete m_pPlayer;       m_pPlayer       = nullptr; }
	if (m_pBlocks       != nullptr) { delete m_pBlocks;       m_pBlocks       = nullptr; }
	if (m_pGoal         != nullptr) { delete m_pGoal;         m_pGoal         = nullptr; }
	if (m_pKuribo       != nullptr) { delete m_pKuribo;       m_pKuribo       = nullptr; }
}

/// <summary>
/// �X�e�[�W��̃I�u�W�F�N�g�̐���
/// </summary>
void PlayScene::MakeStageObj()
{
	m_pBlocks = new Characters<Block>(L"Texture/Block2.png", L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");

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
				m_pPlayer = new Player(pos, size);
				break;

			case Object::NORMAL_BLOCK:
				m_pBlocks->m_ObjectVector.push_back(new Block(pos, size));
				break;
			case Object::KURIBOU:
				//m_pKuribo = new Kuribo(pos, size);
				break;
			}
		}
	}

	Vector3 pos  = { 1.75f,-0.115f,m_StandardZpos };
	Vector2 size = { 0.75f,0.75f };

	m_pGoal = new Goal(pos, size);

	m_pBlocks->ThisObjCreateBuffer();

	/*���̎��S���胉�C���̌v�Z*/
	m_UnderDeathLine = m_StandardSize * -(m_pStage->GetStageHeight() - halfHeight);
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <param name="inputFlag"></param>
/// <returns></returns>
GameState PlayScene::UpDateScene(InputFlag inputFlag)
{
	UpDateGame(inputFlag);
	Draw();

	return m_NextGameState;
}

/// <summary>
/// �Q�[���̍X�V
/// </summary>
/// <param name="inputFlag"></param>
void PlayScene::UpDateGame(InputFlag inputFlag)
{
	m_NextGameState = GameState::PLAY;

	m_pPlayer->SetInputFlag(inputFlag);

	//�u���b�N�Q�̃v���C���[�ɑ΂��ďՓ˔���
	for (int i = 0; i < m_pBlocks->m_ObjectVector.size(); i++)
	{
		m_pBlocks->m_ObjectVector[i]->CheckPlayer(m_pPlayer);
	}

	//m_pKuribo->CheckPlayer(m_pPlayer);

	//�v���C���[�ړ�
	m_pPlayer->Move();

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
		ReStart();
		m_NextGameState = GameState::RESULT;
	}

	//�����`�F�b�N
	if (m_UnderDeathLine > m_pPlayer->GetyPos())
	{
		KillPlayer();
	}

	/* �v���C���[������ł��邩�ǂ��� */
	if (m_pPlayer->GetLivibgFlag() == false)
	{
		/* ����ł�����V�[���J�� */
		MoveScene();
	}
}

/// <summary>
/// �`��
/// </summary>
void PlayScene::Draw()
{
	m_pCamera->Shoot(m_pPlayer->GetxPos());
	m_pPlayer->ThisObjRender();
	m_pBlocks->ThisObjRender();
	m_pGoal  ->ThisObjRender();
	//m_pKuribo->ThisObjRender();
}

/// <summary>
/// �Q�[���̃��X�^�[�g
/// </summary>
void PlayScene::ReStart()
{
	/*�Đ�����̃v���C���[�Ɏc�@��ݒ肷�邽�߂Ƀf���[�g�O�ɒl��ۑ�*/
	m_OldPlayerLife = m_pPlayer->GetLife();

	/*�X�e�[�W��̃I�u�W�F�N�g�̃f���[�g*/
	StageObjDelete();

	/*�X�e�[�W�I�u�W�F�N�g�Đ���*/
	MakeStageObj();

	/*�v���C���[�̎c�@�ݒ�*/
	m_pPlayer->SetLife(m_OldPlayerLife);
}

/// <summary>
/// �Q�[����Ԃ̃��Z�b�g
/// </summary>
/// <param name="pDevice"></param>
void PlayScene::ReSet()
{
	StageObjDelete();

	m_NowWorldLevel = 1;
	m_NowStageLevel = 1;

	std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //�X�e�[�W�̃t�@�C���p�X

	m_pStage->ChangeStage(filePas.data());
	MakeStageObj();

	m_pPlayer->SetLife(m_pPlayer->GetSTART_LIFE());
}

/// <summary>
/// �v���C���[���E��
/// </summary>
void PlayScene::KillPlayer()
{
	//�v���C���[�̎��S����
	m_pPlayer->Die();
}

/// <summary>
/// �V�[����J�ڂ���
/// </summary>
void PlayScene::MoveScene()
{
	//�c��c�@���O��������Q�[���I�[�o�[��ʂɍs���A�܂��c�@���������烊�U���g�ɔ��
	if (m_pPlayer->GetLife() == 0)
	{
		ReSet();
		m_NextGameState = GameState::GAMEOVER;
	}
	else
	{
		ReStart();
		m_NextGameState = GameState::RESULT;
	}
}

void PlayScene::StageObjDelete()
{
	if (m_pPlayer != nullptr) { delete m_pPlayer;       m_pPlayer = nullptr; }
	if (m_pBlocks != nullptr) { delete m_pBlocks;       m_pBlocks = nullptr; }
	if (m_pGoal != nullptr) { delete m_pGoal;         m_pGoal = nullptr; }
	if (m_pKuribo != nullptr) { delete m_pKuribo;       m_pKuribo = nullptr; }
}