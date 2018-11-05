#include"PlayScene.h"
#include"Stage.h"
#include"Camera.h"
#include"Player.h"
#include"Flag.h"
#include"Characters.h"
#include"Block.h"
#include"DeathChecker.h"
#include"Dx11.h"
#include"Math.h"

using namespace OriginalMath;

PlayScene::PlayScene(ID3D11Device* pDevice)
{
	m_NextGameState = GameState::PLAY;

	m_pStage = new Stage("Stage/STAGE_1.txt");
	m_pCamera = new Camera(pDevice);
	m_pBlocks = new Characters<Block>(pDevice, L"Texture/Block2.png", L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	MakeStageObj(pDevice);

	m_pPlayer->SetLife(3);
}

PlayScene::~PlayScene()
{
	if (m_pStage        != nullptr) { delete m_pStage;        m_pStage        = nullptr; }
	if (m_pCamera       != nullptr) { delete m_pCamera;       m_pCamera       = nullptr; }
	if (m_pPlayer       != nullptr) { delete m_pPlayer;       m_pPlayer       = nullptr; }
	if (m_pBlocks       != nullptr) { delete m_pBlocks;       m_pBlocks       = nullptr; }
	if (m_pDeathChecker != nullptr) { delete m_pDeathChecker; m_pDeathChecker = nullptr; }
}

void PlayScene::MakeStageObj(ID3D11Device* pDevice)
{
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

			Vector3 pos = { xPos,yPos,m_StandardZpos };
			Vector2 size = { m_StandardSize, m_StandardSize };

			//�X�C�b�`���Ŕ���
			switch (*(m_pStage->m_pStageDataArray + (height*m_pStage->GetStageWidth() + width)))
			{
			case Object::MARIO:

				m_pPlayer = new Player(pos, size, pDevice);

				pos.x += 0.2f;
				pos.y -= 0.1f;

				m_pDeathChecker = new DeathChecker(pos, size, pDevice);
				break;
			case Object::NORMAL_BLOCK:

				m_pBlocks->m_ObjectVector.push_back(new Block(pos, size));
				break;
			}
		}
	}

	m_pBlocks->ThisObjCreateBuffer(pDevice);
}

GameState PlayScene::UpDateScene(InputFlag inputFlag, Dx11* pDx11)
{
	UpDateGame(inputFlag);
	Draw(pDx11);

	return m_NextGameState;
}

void PlayScene::UpDateGame(InputFlag inputFlag)
{
	//�u���b�N�Q�̃v���C���[�ɑ΂��ďՓ˔���
	for (int i = 0; i < m_pBlocks->m_ObjectVector.size(); i++)
	{
		m_pBlocks->m_ObjectVector[i]->CheckPlayer(m_pPlayer, &inputFlag);
	}

	//�v���C���[�ړ�
	m_pPlayer->Move(&inputFlag);

	//���S�`�F�b�N
	if (m_pDeathChecker->DeathCheck(m_pPlayer))
	{
		//�v���C���[�̎��S����
		m_pPlayer->Die();
		//�c��c�@���O��������Q�[���I�[�o�[��ʂɍs���A�܂��c�@���������烊�U���g�ɔ��
		if (m_pPlayer->GetLife() == 0)
		{
			m_NextGameState = GameState::GAMEOVER;
		}
		else
		{
			m_NextGameState = GameState::RESULT_RESTART;
		}
	}
}

void PlayScene::Draw(Dx11* pDx11)
{
	m_pCamera->Shoot(pDx11->m_pDeviceContext, &pDx11->m_ViewPort, m_pPlayer->GetxPos());
	m_pPlayer->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	m_pDeathChecker->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	m_pBlocks->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
}

void PlayScene::ReStart(ID3D11Device* pDevice)
{
	m_OldPlayerLife = m_pPlayer->GetLife();

	if (m_pPlayer != nullptr) { delete m_pPlayer;       m_pPlayer = nullptr; }
	if (m_pBlocks != nullptr) { delete m_pBlocks;       m_pBlocks = nullptr; }
	if (m_pDeathChecker != nullptr) { delete m_pDeathChecker; m_pDeathChecker = nullptr; }

	m_pBlocks = new Characters<Block>(pDevice, L"Texture/Block2.png", L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");

	MakeStageObj(pDevice);

	m_pPlayer->SetLife(m_OldPlayerLife);

	m_NextGameState = GameState::PLAY;
}