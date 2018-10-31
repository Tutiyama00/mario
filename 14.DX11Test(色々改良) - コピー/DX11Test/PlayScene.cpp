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
	//.5が切り上げになるので縦幅（奇数前提）の中間値が取得できる
	int halfHeight = m_pStage->GetStageHeight() / 2;

	//ステージ情報から生成するオブジェクトを判別
	for (int height = 0; height < m_pStage->GetStageHeight(); height++)
	{
		for (int width = 0; width < m_pStage->GetStageWidth(); width++)
		{
			//初期位置のポジションの計算
			float xPos = m_StandardSize * width;
			float yPos = m_StandardSize * -(height - halfHeight);

			Vector3 pos = { xPos,yPos,m_StandardZpos };
			Vector2 size = { m_StandardSize, m_StandardSize };

			//スイッチ分で判別
			switch (*(m_pStage->m_pStageDataArray + (height*m_pStage->GetStageWidth() + width)))
			{
			case Object::MARIO:

				m_pPlayer = new Player(pos, size, pDevice);

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
	if (m_pPlayer->m_MoveObjState == MoveObjState::DEATH)
	{
		m_NextGameState = GameState::GAMEOVER;
	}

	//ブロック群のプレイヤーに対して衝突判定
	for (int i = 0; i < m_pBlocks->m_ObjectVector.size(); i++)
	{
		m_pBlocks->m_ObjectVector[i]->CheckPlayer(m_pPlayer, &inputFlag);
	}

	//プレイヤー移動
	m_pPlayer->Move(&inputFlag);

	if (m_pDeathChecker->DeathCheck(m_pPlayer))
	{
		m_pPlayer->m_MoveObjState = MoveObjState::DEATH;
		m_NextGameState = GameState::GAMEOVER;
	}
}

void PlayScene::Draw(Dx11* pDx11)
{
	auto playRender = [this, pDx11]
	{
		m_pCamera->Shoot(pDx11->m_pDeviceContext, &pDx11->m_ViewPort, m_pPlayer->m_xPos);
		m_pPlayer      ->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
		m_pDeathChecker->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
		m_pBlocks      ->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	};

	pDx11->Render(playRender);
}