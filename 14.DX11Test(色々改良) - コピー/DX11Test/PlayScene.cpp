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
#include"Nokonoko.h"
#include"TextureData.h"

using namespace OriginalMath;


/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

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

	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		if (m_pKuriboVector[i] != nullptr) { delete m_pKuriboVector[i]; m_pKuriboVector[i] = nullptr; }
	}
	m_pKuriboVector.clear();

	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		if (m_pNokonokoVector[i] != nullptr) { delete m_pNokonokoVector[i]; m_pNokonokoVector[i] = nullptr; }
	}
	m_pNokonokoVector.clear();
}

/// <summary>
/// �v���C���[���E��
/// </summary>
void PlayScene::KillPlayer()
{
	//�v���C���[�̎��S����
	m_pPlayer->Die();
}

/*-------------------------------------              ----------------------------------*/
/*-------------------------------------  IGameScene  ----------------------------------*/
/*-------------------------------------              ----------------------------------*/

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


/*#####################################           #####################################*/
/*#####################################  PRIVATE  #####################################*/
/*#####################################           #####################################*/

/// <summary>
/// �X�e�[�W��̃I�u�W�F�N�g�̐���
/// </summary>
void PlayScene::MakeStageObj()
{
	m_pBlocks = new Characters<Block>(TextureData::Instance()->GetBLOCK_TR(),TextureData::Instance()->GetBLOCK_TSRV(), L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");

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
				m_pKuriboVector.push_back( new Kuribo(pos, size));
				break;

			case Object::NOKONOKO:
				m_pNokonokoVector.push_back( new Nokonoko(pos, size));
				break;
			}
		}
	}

	Vector3 pos  = { 1.75f,-0.115f,m_StandardZpos };
	Vector2 size = { 0.75f,0.75f };

	//m_pGoal = new Goal(pos, size);

	m_pBlocks->ThisObjCreateBuffer();

	/*���̎��S���胉�C���̌v�Z*/
	m_UnderDeathLine = m_StandardSize * -(m_pStage->GetStageHeight() - halfHeight);

	/* �J������X���W������ */
	m_CameraShootXPos = 0.8f;
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

/// <summary>
/// �X�e�[�W���\������I�u�W�F�N�g�̃f���[�g
/// </summary>
void PlayScene::StageObjDelete()
{
	if (m_pPlayer != nullptr) { delete m_pPlayer;       m_pPlayer = nullptr; }
	if (m_pBlocks != nullptr) { delete m_pBlocks;       m_pBlocks = nullptr; }
	if (m_pGoal   != nullptr) { delete m_pGoal;         m_pGoal   = nullptr; }

	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		if (m_pKuriboVector[i] != nullptr) { delete m_pKuriboVector[i]; m_pKuriboVector[i] = nullptr; }
	}
	m_pKuriboVector.clear();

	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		if (m_pNokonokoVector[i] != nullptr) { delete m_pNokonokoVector[i]; m_pNokonokoVector[i] = nullptr; }
	}
	m_pNokonokoVector.clear();
}

/// <summary>
/// �L�����B�̈ړ�����
/// </summary>
void PlayScene::MoveOrder()
{
	//�v���C���[�ړ�
	m_pPlayer->Move();

	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		m_pKuriboVector[i]->Move();
	}

	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		m_pNokonokoVector[i]->Move();
	}

}

/// <summary>
/// �L�����B�̃`�F�b�N����
/// </summary>
void PlayScene::ObjCheckOrder()
{
	//�u���b�N�Q�̃v���C���[�ɑ΂��ďՓ˔���
	for (int i = 0; i < m_pBlocks->m_ObjectVector.size(); i++)
	{
		m_pBlocks->m_ObjectVector[i]->CheckPlayer(m_pPlayer);

		for (int j = 0; j < m_pKuriboVector.size(); j++)
		{
			m_pBlocks->m_ObjectVector[i]->CheckEnemy(m_pKuriboVector[j]);
		}

		for (int j = 0; j < m_pNokonokoVector.size(); j++)
		{
			m_pBlocks->m_ObjectVector[i]->CheckEnemy(m_pNokonokoVector[j]);
		}
	}

	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
	    /* �N���{�[�ƃv���C���[�̔�r */
		m_pKuriboVector[i]->CheckPlayer(m_pPlayer);

		for (int j = 0; j < m_pNokonokoVector.size(); j++)
		{
			if (m_pNokonokoVector[j]->GetLivingFlag())
			{
				/* �N���{�[�ƃm�R�m�R�̔�r */
				m_pNokonokoVector[j]->CheckEnemy(m_pKuriboVector[i]);
				m_pKuriboVector[i]->CheckEnemy(m_pNokonokoVector[j]);
			}
		}

		if (i + 1 < m_pKuriboVector.size())
		{
			/* �N���{�[�ƃN���{�[�̔�r */
			for (int c = i + 1; c < m_pKuriboVector.size(); c++)
			{
				m_pKuriboVector[i]->CheckEnemy(m_pKuriboVector[c]);
				m_pKuriboVector[c]->CheckEnemy(m_pKuriboVector[i]);
			}
		}
	}

	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		/* �m�R�m�R�ƃv���C���[�̔�r */
		m_pNokonokoVector[i]->CheckPlayer(m_pPlayer);

		/* �`�F�b�N���Ă���̂��z��̍Ō�̃m�R�m�R�������ꍇ�m�R�m�R���m�̏������Ȃ� */
		if (i + 1 >= m_pNokonokoVector.size()) { continue; }

		/*�@�m�R�m�R�ƃm�R�m�R�̔�r */
		for (int j = i + 1; j < m_pNokonokoVector.size(); j++)
		{
			/* �m�R�m�R���b�����肵�Ă���̂��`�F�b�N */
			bool NokonokoRunStateFlagI = m_pNokonokoVector[i]->GetNokonokoState() == NokonokoState::KOURA_RUN;
			bool NokonokoRunStateFlagJ = m_pNokonokoVector[j]->GetNokonokoState() == NokonokoState::KOURA_RUN;

			/* �����̃m�R�m�R���b������ */
			if (NokonokoRunStateFlagI && NokonokoRunStateFlagJ)
			{
				if (m_pNokonokoVector[j]->CollisionCheck(m_pNokonokoVector[i]) && m_pNokonokoVector[i]->CollisionCheck(m_pNokonokoVector[j]))
				{
					m_pNokonokoVector[i]->Die();
					m_pNokonokoVector[j]->Die();

					continue;
				}
			}

			/* I�̕��̃m�R�m�R�������b������ */
			if(NokonokoRunStateFlagI && !NokonokoRunStateFlagJ)
			{
				m_pNokonokoVector[i]->CheckEnemy(m_pNokonokoVector[j]);
				m_pNokonokoVector[j]->CheckEnemy(m_pNokonokoVector[i]);

				continue;
			}

			/* J�̕��̃m�R�m�R�������b������ */
			if (!NokonokoRunStateFlagI && NokonokoRunStateFlagJ)
			{
				m_pNokonokoVector[j]->CheckEnemy(m_pNokonokoVector[i]);
				m_pNokonokoVector[i]->CheckEnemy(m_pNokonokoVector[j]);

				continue;
			}

			/* �ǂ̃p�^�[���ɂ����Ă͂܂�Ȃ������ꍇ */
			m_pNokonokoVector[j]->CheckEnemy(m_pNokonokoVector[i]);
			m_pNokonokoVector[i]->CheckEnemy(m_pNokonokoVector[j]);
			
		}
	}
}

/*#####################################             #####################################*/
/*#####################################  PROTECTED  #####################################*/
/*#####################################             #####################################*/

/*-------------------------------------              ----------------------------------*/
/*-------------------------------------  IGameScene  ----------------------------------*/
/*-------------------------------------              ----------------------------------*/

/// <summary>
/// �Q�[���̍X�V
/// </summary>
/// <param name="inputFlag"></param>
void PlayScene::UpDateGame(InputFlag inputFlag)
{
	m_NextGameState = GameState::PLAY;

	m_pPlayer->SetInputFlag(inputFlag);

	ObjCheckOrder();

	MoveOrder();

	/*�S�[���`�F�b�N*/
	//if (m_pGoal->CollisionCheck(m_pPlayer))
	//{
	//	m_NowStageLevel++;
	//	if (m_NowStageLevel > M_IN_STAGE_AMOUNT)
	//	{
	//		m_NowWorldLevel++;
	//		m_NowStageLevel = 1;
	//	}

	//	std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //�X�e�[�W�̃t�@�C���p�X

	//	m_pStage->ChangeStage(filePas.data());
	//	ReStart();
	//	m_NextGameState = GameState::RESULT;
	//}

	/* �J�����̉f��X���W��ς��Ă����� */
	if (m_pPlayer->GetxPos() >= m_CameraShootXPos)
	{
		m_CameraShootXPos = m_pPlayer->GetxPos();
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
	m_pCamera->Shoot(m_CameraShootXPos);
	m_pPlayer->ThisObjRender();
	//m_pGoal->ThisObjRender();

	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		m_pKuriboVector[i]->ThisObjRender();
	}

	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		m_pNokonokoVector[i]->ThisObjRender();
	}
	m_pBlocks->ThisObjRender();
}