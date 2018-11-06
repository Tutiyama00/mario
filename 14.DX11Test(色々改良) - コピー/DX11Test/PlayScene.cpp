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

using namespace OriginalMath;

/*コンストラクタ*/
PlayScene::PlayScene(ID3D11Device* pDevice)
{
	m_NextGameState = GameState::PLAY;

	m_pStage  = new Stage("Stage/STAGE_1-1.txt");
	m_pCamera = new Camera(pDevice);
	MakeStageObj(pDevice);

	m_pPlayer->SetLife(3);
}

/*デストラクタ*/
PlayScene::~PlayScene()
{
	if (m_pStage        != nullptr) { delete m_pStage;        m_pStage        = nullptr; }
	if (m_pCamera       != nullptr) { delete m_pCamera;       m_pCamera       = nullptr; }
	if (m_pPlayer       != nullptr) { delete m_pPlayer;       m_pPlayer       = nullptr; }
	if (m_pBlocks       != nullptr) { delete m_pBlocks;       m_pBlocks       = nullptr; }
	if (m_pGoal         != nullptr) { delete m_pGoal;         m_pGoal         = nullptr; }
}

/*ステージ上のオブジェクトの生成*/
void PlayScene::MakeStageObj(ID3D11Device* pDevice)
{
	m_pBlocks = new Characters<Block>(pDevice, L"Texture/Block2.png", L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");

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

			Vector3 pos  = { xPos,yPos,m_StandardZpos };
			Vector2 size = { m_StandardSize, m_StandardSize };

			//スイッチ文で判別
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

	/*下の死亡判定ラインの計算*/
	m_UnderDeathLine = m_StandardSize * -(m_pStage->GetStageHeight() - halfHeight);
}

GameState PlayScene::UpDateScene(InputFlag inputFlag, Dx11* pDx11)
{
	UpDateGame(inputFlag,pDx11->m_pDevice);

	/*ReStart()をした後に描画をすると一瞬初期状態が映り込んでしまうため条件追加*/
	if (m_NextGameState == GameState::PLAY)
	{
		Draw(pDx11);
	}

	return m_NextGameState;
}

void PlayScene::UpDateGame(InputFlag inputFlag,ID3D11Device* pDevice)
{
	m_NextGameState = GameState::PLAY;

	//ブロック群のプレイヤーに対して衝突判定
	for (int i = 0; i < m_pBlocks->m_ObjectVector.size(); i++)
	{
		m_pBlocks->m_ObjectVector[i]->CheckPlayer(m_pPlayer, &inputFlag);
	}

	//プレイヤー移動
	m_pPlayer->Move(&inputFlag);

	//落下チェック
	if (m_UnderDeathLine > m_pPlayer->GetyPos())
	{
		//プレイヤーの死亡処理
		m_pPlayer->Die();
		//残り残機が０だったらゲームオーバー画面に行く、まだ残機があったらリザルトに飛ぶ
		if (m_pPlayer->GetLife() == 0)
		{
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
	m_pCamera->Shoot(pDx11->m_pDeviceContext, &pDx11->m_ViewPort, m_pPlayer->GetxPos());
	m_pPlayer      ->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	m_pBlocks      ->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	m_pGoal->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
}

/*ゲームのリスタート*/
void PlayScene::ReStart(ID3D11Device* pDevice)
{
	/*再生成後のプレイヤーに残機を設定するためにデリート前に値を保存*/
	m_OldPlayerLife = m_pPlayer->GetLife();

	/*ステージ上のオブジェクトのデリート*/
	if (m_pPlayer       != nullptr) { delete m_pPlayer;       m_pPlayer       = nullptr; }
	if (m_pBlocks       != nullptr) { delete m_pBlocks;       m_pBlocks       = nullptr; }
	if (m_pGoal         != nullptr) { delete m_pGoal;         m_pGoal         = nullptr; }

	/*ステージオブジェクト再生成*/
	MakeStageObj(pDevice);

	/*プレイヤーの残機設定*/
	m_pPlayer->SetLife(m_OldPlayerLife);
}