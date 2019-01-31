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
#include"Image.h"
#include"ClayPipe.h"
#include"Enemy.h"
#include"BackGround.h"

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
	if (m_pStage             != nullptr) { delete m_pStage;             m_pStage             = nullptr; }
	if (m_pCamera            != nullptr) { delete m_pCamera;            m_pCamera            = nullptr; }
	StageObjDelete();
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
	m_pBlocks            = new Characters<Block>(TextureData::Instance()->GetBLOCK_TR(),        TextureData::Instance()->GetBLOCK_TSRV(),        L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	m_pBlockDummys       = new Characters<Image>(TextureData::Instance()->GetBLOCK_TR(),        TextureData::Instance()->GetBLOCK_TSRV(),        L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	m_pBlockGrounds      = new Characters<Block>(TextureData::Instance()->GetBLOCK_GROUND_TR(), TextureData::Instance()->GetBLOCK_GROUND_TSRV(), L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	m_pBlockGroundDummys = new Characters<Image>(TextureData::Instance()->GetBLOCK_GROUND_TR(), TextureData::Instance()->GetBLOCK_GROUND_TSRV(), L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	m_pClayPipes         = new Characters<ClayPipe>(TextureData::Instance()->GetCLAY_PIPE_TR(), TextureData::Instance()->GetCLAY_PIPE_TSRV(),    L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");

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
			switch (*(m_pStage->m_pStageDataArray + (height * m_pStage->GetStageWidth() + width)))
			{
			case Object::MARIO:
				m_pPlayer = new Player(pos, size);
				break;

			case Object::NORMAL_BLOCK:
				m_pBlocks->m_ObjectVector.push_back(new Block(pos, size));
				break;

			case Object::NORMAL_BLOCK_DUMMY:
				m_pBlockDummys->m_ObjectVector.push_back(new Image(pos, size, TextureData::Instance()->GetBLOCK_TR(), TextureData::Instance()->GetBLOCK_TSRV(),false));
				break;

			case Object::GROUND_BLOCK:
				m_pBlockGrounds->m_ObjectVector.push_back(new Block(pos, size));
				break;

			case Object::GROUND_BLOCK_DUMMY:
				m_pBlockGroundDummys->m_ObjectVector.push_back(new Image(pos, size, TextureData::Instance()->GetBLOCK_GROUND_TR(), TextureData::Instance()->GetBLOCK_GROUND_TSRV(), false));
				break;

			case Object::CLAY_PIPE_2:
				m_pClayPipes->m_ObjectVector.push_back(new ClayPipe(pos,size,2));
				break;

			case Object::CLAY_PIPE_3:
				m_pClayPipes->m_ObjectVector.push_back(new ClayPipe(pos, size, 3));
				break;

			case Object::CLAY_PIPE_4:
				m_pClayPipes->m_ObjectVector.push_back(new ClayPipe(pos, size, 4));
				break;

			case Object::KURIBOU:
				m_pKuriboVector.push_back( new Kuribo(pos, size));
				break;

			case Object::NOKONOKO:
				m_pNokonokoVector.push_back( new Nokonoko(pos, size));
				break;

			case Object::GOAL:
				m_pGoal = new Goal(pos);
				break;
			}
		}
	}

	float xPos = m_StandardSize * 11.5f;
	float yPos = m_StandardSize * -((m_pStage->GetStageHeight() - 12.5f) - halfHeight);
	m_pBackGround = new BackGround(Vector3{ xPos,yPos,m_StandardZpos }, 
		                      Vector2{ m_StandardSize * 24, m_StandardSize * 24 }, 
		                      TextureData::Instance()->GetBACK_GROUND_1_TR(), 
		                      TextureData::Instance()->GetBACK_GROUND_1_TSRV()
		                      );
	m_pBackGround->AddBackGround(TextureData::Instance()->GetBACK_GROUND_2_TR(), TextureData::Instance()->GetBACK_GROUND_2_TSRV());
	m_pBackGround->ThisObjCreateBuffer();

	Vector3 pos  = { 1.75f,-0.115f,m_StandardZpos };
	Vector2 size = { 0.75f,0.75f };

	m_pBlocks->ThisObjCreateBuffer();
	m_pBlockDummys->ThisObjCreateBuffer();
	m_pBlockGrounds->ThisObjCreateBuffer();
	m_pBlockGroundDummys->ThisObjCreateBuffer();
	m_pClayPipes->ThisObjCreateBuffer();

	/*���̎��S���胉�C���̌v�Z*/
	m_UnderDeathLine = m_StandardSize * -(m_pStage->GetStageHeight() - halfHeight);

	/* �J������X���W������ */
	m_CameraShootXPos = 0.8f;

	/* �v���C���[�����E�l�̏����� */
	m_PlayerMoveEndXPos = m_CameraShootXPos - m_EndToShootXPosAmount;

	/* �I�u�W�F�N�g�E���E�l�̏����� */
	m_ObjMoveRightXPos = m_CameraShootXPos + m_EndToShootXPosAmount + m_ObjMoveXPosAdjust;
	/* �I�u�W�F�N�g�����E�l�̏����� */
	m_ObjMoveLeftXPos = m_CameraShootXPos - m_EndToShootXPosAmount - m_ObjMoveXPosAdjust;
	/* �u���b�N�E���E�l�̏����� */
	m_BlockCheckRightXPos = m_CameraShootXPos + m_EndToShootXPosAmount + m_ObjMoveXPosAdjust + m_BlockCheckXPosDiff;
	/* �u���b�N�����E�l�̏����� */
	m_BlockCheckLeftXPos = m_CameraShootXPos - m_EndToShootXPosAmount - m_ObjMoveXPosAdjust - m_BlockCheckXPosDiff;
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
	if (m_pPlayer            != nullptr) { delete m_pPlayer;            m_pPlayer            = nullptr; }
	if (m_pBlocks            != nullptr) { delete m_pBlocks;            m_pBlocks            = nullptr; }
	if (m_pBlockDummys       != nullptr) { delete m_pBlockDummys;       m_pBlockDummys       = nullptr; }
	if (m_pBlockGrounds      != nullptr) { delete m_pBlockGrounds;      m_pBlockGrounds      = nullptr; }
	if (m_pBlockGroundDummys != nullptr) { delete m_pBlockGroundDummys; m_pBlockGroundDummys = nullptr; }
	if (m_pClayPipes         != nullptr) { delete m_pClayPipes;         m_pClayPipes         = nullptr; }
	if (m_pGoal              != nullptr) { delete m_pGoal;              m_pGoal              = nullptr; }
	if (m_pBackGround != nullptr) { delete m_pBackGround;              m_pBackGround = nullptr; }

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

	/*�N���{�[�̈ړ�*/
	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		EnemyMoveOrder(m_pKuriboVector[i]);
	}

	/*�m�R�m�R�̈ړ�*/
	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		EnemyMoveOrder(m_pNokonokoVector[i]);
	}
}

/// <summary>
/// �G�̈ړ�����
/// </summary>
/// <param name="pEnemy">�ړ�������G�|�C���^</param>
void PlayScene::EnemyMoveOrder(Enemy* pEnemy)
{
	/*�s���͈͓��ɂ���̂��ǂ���*/
	if (pEnemy->GetxPos() >= m_ObjMoveLeftXPos && pEnemy->GetxPos() <= m_ObjMoveRightXPos)
	{
		/*�ړ�*/
		pEnemy->Move();
	}
}

/// <summary>
/// �L�����B�̃`�F�b�N����
/// </summary>
void PlayScene::ObjCheckOrder()
{
	CollisionCheckBlock(m_pBlocks);
	CollisionCheckBlock(m_pBlockGrounds);
	CollisionCheckClayPipe();
	CollisionCheckKuribo  ();
	CollisionCheckNokonoko();
}

/// <summary>
/// //�S�[���������̃`�F�b�N
/// </summary>
void PlayScene::GoalCheckOrder()
{
	/*�v���C���[���S�[�����Ă��邩*/
	if (m_pGoal->GoalCheck(m_pPlayer))
	{
		/*�S�[�����o���I����Ă��邩*/
		if (!m_pGoal->Play(m_pPlayer))
		{
			/*�X�e�[�W�̃��x�����P�グ��*/
			m_NowStageLevel++;
			/*�X�e�[�W�̃��x�����P���[���h���ɂ���X�e�[�W���������Ă��邩�ǂ���*/
			if (m_NowStageLevel > M_IN_STAGE_AMOUNT)
			{
				/*���[���h�̃��x����1�グ��*/
				m_NowWorldLevel++;
				/*�X�e�[�W�̃��x�����P�ɖ߂�*/
				m_NowStageLevel = 1;
			}

			/*���ɓǂݍ��ރt�@�C���p�X��ݒ�*/
			std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //�X�e�[�W�̃t�@�C���p�X

			/*�X�e�[�W��ς���*/
			m_pStage->ChangeStage(filePas.data());
			/*�V�[�������X�^�[�g*/
			ReStart();
			/*���Ƀ��U���g�V�[���ɔ��*/
			m_NextGameState = GameState::RESULT;
		}
	}
}

/// <summary>
/// �u���b�N�̃R���W�����`�F�b�N
/// </summary>
/// <param name="pBlocks"></param>
void PlayScene::CollisionCheckBlock(Characters<Block>* pBlocks)
{
	//�u���b�N�Q�̏Փ˔���
	for (int i = 0; i < pBlocks->m_ObjectVector.size(); i++)
	{
		/*����\�͈͓��ɂ���̂��ǂ���*/
		if (pBlocks->m_ObjectVector[i]->GetxPos() >= m_BlockCheckLeftXPos && pBlocks->m_ObjectVector[i]->GetxPos() <= m_BlockCheckRightXPos)
		{
			/*�v���C���[�ɑ΂��Ẵ`�F�b�N*/
			pBlocks->m_ObjectVector[i]->CheckPlayer(m_pPlayer);

			/*�N���{�[�ɑ΂��Ẵ`�F�b�N*/
			for (int j = 0; j < m_pKuriboVector.size(); j++)
			{
				pBlocks->m_ObjectVector[i]->CheckEnemy(m_pKuriboVector[j]);
			}

			/*�m�R�m�R�ɑ΂��Ẵ`�F�b�N*/
			for (int j = 0; j < m_pNokonokoVector.size(); j++)
			{
				pBlocks->m_ObjectVector[i]->CheckEnemy(m_pNokonokoVector[j]);
			}
		}
	}
}

/// <summary>
/// �m�R�m�R�̃R���W�����`�F�b�N
/// </summary>
void PlayScene::CollisionCheckNokonoko()
{
	/*�m�R�m�R�̏Փ˔���*/
	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		/*����\�͈͓��ɂ���̂��ǂ���*/
		if (m_pNokonokoVector[i]->GetxPos() >= m_ObjMoveLeftXPos && m_pNokonokoVector[i]->GetxPos() <= m_ObjMoveRightXPos)
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
						/*���ꂼ��ǂ��瑤�ɂ���̂�*/
						if (m_pNokonokoVector[i]->GetxPos() <= m_pNokonokoVector[j]->GetxPos())
						{
							m_pNokonokoVector[i]->StartStandardDie(false);
							m_pNokonokoVector[j]->StartStandardDie(true);
						}
						else
						{
							m_pNokonokoVector[i]->StartStandardDie(true);
							m_pNokonokoVector[j]->StartStandardDie(false);
						}

						continue;
					}
				}

				/* I�̕��̃m�R�m�R�������b������ */
				if (NokonokoRunStateFlagI && !NokonokoRunStateFlagJ)
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
}

/// <summary>
/// �N���{�[�̃R���W�����`�F�b�N
/// </summary>
void PlayScene::CollisionCheckKuribo()
{
	/*�N���{�[�̏Փ˔���*/
	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		/*����\�͈͂ɂ���̂��ǂ���*/
		if (m_pKuriboVector[i]->GetxPos() >= m_ObjMoveLeftXPos && m_pKuriboVector[i]->GetxPos() <= m_ObjMoveRightXPos)
		{
			/*�v���C���[�ɑ΂��Ẵ`�F�b�N*/
			m_pKuriboVector[i]->CheckPlayer(m_pPlayer);

			/*�m�R�m�R�ɑ΂��Ẵ`�F�b�N*/
			for (int j = 0; j < m_pNokonokoVector.size(); j++)
			{
				/*�m�R�m�R�������Ă��邩�ǂ���*/
				if (m_pNokonokoVector[j]->GetLivingFlag())
				{
					/* �N���{�[�ƃm�R�m�R�̔�r */
					m_pNokonokoVector[j]->CheckEnemy(m_pKuriboVector[i]);
					m_pKuriboVector[i]->CheckEnemy(m_pNokonokoVector[j]);
				}
			}

			/*�N���{�[�ɑ΂��Ẵ`�F�b�N*/
			/*�z��̍Ō�����ǂ���*/
			if (i + 1 < m_pKuriboVector.size())
			{
				/*�N���{�[�ƃN���{�[�̔�r*/
				for (int c = i + 1; c < m_pKuriboVector.size(); c++)
				{
					/*�Ώۂ̃N���{�[�������Ă��邩�ǂ���*/
					if (m_pKuriboVector[c]->GetLivingFlag())
					{
						m_pKuriboVector[i]->CheckEnemy(m_pKuriboVector[c]);
						m_pKuriboVector[c]->CheckEnemy(m_pKuriboVector[i]);
					}
				}
			}
		}
	}
}

/// <summary>
/// �y�ǂ̃R���W�����`�F�b�N
/// </summary>
void PlayScene::CollisionCheckClayPipe()
{
	/*�y�ǌQ�̑΂��ďՓ˔���*/
	for (int i = 0; i < m_pClayPipes->m_ObjectVector.size(); i++)
	{
		/*����\�͈͓��ɂ���̂��ǂ���*/
		if (m_pClayPipes->m_ObjectVector[i]->GetxPos() >= m_BlockCheckLeftXPos && m_pClayPipes->m_ObjectVector[i]->GetxPos() <= m_BlockCheckRightXPos)
		{
			/*�v���C���[�ɑ΂��Ẵ`�F�b�N*/
			m_pClayPipes->m_ObjectVector[i]->CheckPlayer(m_pPlayer);

			/*�N���{�[�ɑ΂��Ẵ`�F�b�N*/
			for (int j = 0; j < m_pKuriboVector.size(); j++)
			{
				m_pClayPipes->m_ObjectVector[i]->CheckEnemy(m_pKuriboVector[j]);
			}

			/*�m�R�m�R�ɑ΂��Ẵ`�F�b�N*/
			for (int j = 0; j < m_pNokonokoVector.size(); j++)
			{
				m_pClayPipes->m_ObjectVector[i]->CheckEnemy(m_pNokonokoVector[j]);
			}
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

	/* �v���C���[�������E�l�𒴂��Ȃ��悤�ɂ��� */
	if (m_pPlayer->GetxPos() <= m_PlayerMoveEndXPos)
	{
		inputFlag.ReSet(InputFlagCode::INPUT_LEFT);
	}

	/*���͏����v���C���[�ɃZ�b�g����*/
	m_pPlayer->SetInputFlag(inputFlag);

	/*�L�����N�^�[�B�̃R���W�����`�F�b�N*/
	ObjCheckOrder();

	/*�ړ�����*/
	MoveOrder();

	/*�S�[���`�F�b�N*/
	GoalCheckOrder();
	
	/* �J�����̉f��X���W��ς��Ă����� */
	if (m_pPlayer->GetxPos() >= m_CameraShootXPos)
	{
		/*�J������X���W���v���C���[�ɍ��킹��*/
		m_CameraShootXPos = m_pPlayer->GetxPos();
		/* �v���C���[�����E�l�̏����� */
		m_PlayerMoveEndXPos = m_CameraShootXPos - m_EndToShootXPosAmount;
		/* �I�u�W�F�N�g�E���E�l�̏����� */
		m_ObjMoveRightXPos = m_CameraShootXPos + m_EndToShootXPosAmount + m_ObjMoveXPosAdjust;
		/* �I�u�W�F�N�g�����E�l�̏����� */
		m_ObjMoveLeftXPos = m_CameraShootXPos - m_EndToShootXPosAmount - m_ObjMoveXPosAdjust;
		/* �u���b�N�E���E�l�̏����� */
		m_BlockCheckRightXPos = m_CameraShootXPos + m_EndToShootXPosAmount + m_ObjMoveXPosAdjust + m_BlockCheckXPosDiff;
		/* �u���b�N�����E�l�̏����� */
		m_BlockCheckLeftXPos = m_CameraShootXPos - m_EndToShootXPosAmount - m_ObjMoveXPosAdjust - m_BlockCheckXPosDiff;
	}

	m_pBackGround->NextCheck(m_ObjMoveLeftXPos);

	/*�v���C���[�����������Ă��邩�ǂ���*/
	if (m_UnderDeathLine > m_pPlayer->GetyPos())
	{
		/*�v���C���[���E��*/
		KillPlayer();
	}

	/* �v���C���[������ł��邩�ǂ��� */
	if (m_pPlayer->GetLivibgFlag() == false)
	{
		/*���S���o���I��������ǂ���*/
		if (!m_pPlayer->DieMove())
		{
			/*���S���o���I�������V�[���J��*/
			MoveScene();
		}
	}
}

/// <summary>
/// �`��
/// </summary>
void PlayScene::Draw()
{
	m_pCamera -> Shoot(m_CameraShootXPos);
	m_pPlayer -> ThisObjRender();
	m_pGoal   -> ThisObjRender();
	 
	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		m_pKuriboVector[i]->ThisObjRender();
	}

	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		m_pNokonokoVector[i]->ThisObjRender();
	}

	m_pBlocks            -> ThisObjRender();
	m_pBlockDummys       -> ThisObjRender();
	m_pBlockGrounds      -> ThisObjRender();
	m_pBlockGroundDummys -> ThisObjRender();
	m_pClayPipes         -> ThisObjRender();
	m_pBackGround->ThisObjRender();
}