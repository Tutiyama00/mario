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

using namespace OriginalMath;


/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// コンストラクタ
/// </summary>
PlayScene::PlayScene()
{
	m_NextGameState = GameState::PLAY;
	m_NowWorldLevel = 1;
	m_NowStageLevel = 1;

	std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //ステージのファイルパス

	m_pStage  = new Stage(filePas.data());
	m_pCamera = new Camera();
	MakeStageObj();

	m_pPlayer->SetLife(m_pPlayer->GetSTART_LIFE());
}

/// <summary>
/// デストラクタ
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
/// プレイヤーを殺す
/// </summary>
void PlayScene::KillPlayer()
{
	//プレイヤーの死亡処理
	m_pPlayer->Die();
}

/*-------------------------------------              ----------------------------------*/
/*-------------------------------------  IGameScene  ----------------------------------*/
/*-------------------------------------              ----------------------------------*/

/// <summary>
/// シーンの更新
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
/// ステージ上のオブジェクトの生成
/// </summary>
void PlayScene::MakeStageObj()
{
	m_pBlocks = new Characters<Block>(L"Texture/Block2.png", L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");

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

	m_pGoal = new Goal(pos, size);

	m_pBlocks->ThisObjCreateBuffer();

	/*下の死亡判定ラインの計算*/
	m_UnderDeathLine = m_StandardSize * -(m_pStage->GetStageHeight() - halfHeight);
}



/// <summary>
/// ゲームのリスタート
/// </summary>
void PlayScene::ReStart()
{
	/*再生成後のプレイヤーに残機を設定するためにデリート前に値を保存*/
	m_OldPlayerLife = m_pPlayer->GetLife();

	/*ステージ上のオブジェクトのデリート*/
	StageObjDelete();

	/*ステージオブジェクト再生成*/
	MakeStageObj();

	/*プレイヤーの残機設定*/
	m_pPlayer->SetLife(m_OldPlayerLife);
}

/// <summary>
/// ゲーム状態のリセット
/// </summary>
/// <param name="pDevice"></param>
void PlayScene::ReSet()
{
	StageObjDelete();

	m_NowWorldLevel = 1;
	m_NowStageLevel = 1;

	std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //ステージのファイルパス

	m_pStage->ChangeStage(filePas.data());
	MakeStageObj();

	m_pPlayer->SetLife(m_pPlayer->GetSTART_LIFE());
}

/// <summary>
/// シーンを遷移する
/// </summary>
void PlayScene::MoveScene()
{
	//残り残機が０だったらゲームオーバー画面に行く、まだ残機があったらリザルトに飛ぶ
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

void PlayScene::MoveOrder()
{
	//プレイヤー移動
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

void PlayScene::ObjCheckOrder()
{
	//ブロック群のプレイヤーに対して衝突判定
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
		if (m_pKuriboVector[i]->GetLivingFlag())
		{
			/* クリボーとプレイヤーの比較 */
			m_pKuriboVector[i]->CheckPlayer(m_pPlayer);

			for (int j = 0; j < m_pNokonokoVector.size(); j++)
			{
				if (m_pNokonokoVector[j]->GetLivingFlag())
				{
					/* クリボーとノコノコの比較 */
					m_pNokonokoVector[j]->CheckEnemy(m_pKuriboVector[i]);
					m_pKuriboVector[i]->CheckEnemy(m_pNokonokoVector[j]);
				}
			}

			if (i + 1 < m_pKuriboVector.size())
			{
				/* クリボーとクリボーの比較 */
				for (int c = i + 1; c < m_pKuriboVector.size(); c++)
				{
					m_pKuriboVector[i]->CheckEnemy(m_pKuriboVector[c]);
					m_pKuriboVector[c]->CheckEnemy(m_pKuriboVector[i]);
				}
			}
		}
	}

	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		if (m_pNokonokoVector[i]->GetLivingFlag())
		{
			m_pNokonokoVector[i]->CheckPlayer(m_pPlayer);

			if (i + 1 < m_pNokonokoVector.size())
			{
				/*　ノコノコとノコノコの比較 */
				for (int x = i + 1; x < m_pNokonokoVector.size(); x++)
				{
					if (m_pNokonokoVector[i]->GetNokonokoState() == NokonokoState::KOURA_RUN)
					{
						if (m_pNokonokoVector[x]->GetNokonokoState() == NokonokoState::KOURA_RUN)
						{
							if (m_pNokonokoVector[x]->CollisionCheck(m_pNokonokoVector[i]) && m_pNokonokoVector[x]->CollisionCheck(m_pNokonokoVector[i]))
							{
								m_pNokonokoVector[i]->Die();
								m_pNokonokoVector[x]->Die();
							}
						}

						m_pNokonokoVector[i]->CheckEnemy(m_pNokonokoVector[x]);
						m_pNokonokoVector[x]->CheckEnemy(m_pNokonokoVector[i]);
					}
					else if (m_pNokonokoVector[x]->GetNokonokoState() == NokonokoState::KOURA_RUN)
					{
						m_pNokonokoVector[x]->CheckEnemy(m_pNokonokoVector[i]);
						m_pNokonokoVector[i]->CheckEnemy(m_pNokonokoVector[x]);
					}
					else
					{
						m_pNokonokoVector[i]->CheckEnemy(m_pNokonokoVector[x]);
						m_pNokonokoVector[x]->CheckEnemy(m_pNokonokoVector[i]);
					}
				}
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
/// ゲームの更新
/// </summary>
/// <param name="inputFlag"></param>
void PlayScene::UpDateGame(InputFlag inputFlag)
{
	m_NextGameState = GameState::PLAY;

	m_pPlayer->SetInputFlag(inputFlag);

	ObjCheckOrder();

	MoveOrder();

	/*ゴールチェック*/
	if (m_pGoal->CollisionCheck(m_pPlayer))
	{
		m_NowStageLevel++;
		if (m_NowStageLevel > M_IN_STAGE_AMOUNT)
		{
			m_NowWorldLevel++;
			m_NowStageLevel = 1;
		}

		std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //ステージのファイルパス

		m_pStage->ChangeStage(filePas.data());
		ReStart();
		m_NextGameState = GameState::RESULT;
	}

	//落下チェック
	if (m_UnderDeathLine > m_pPlayer->GetyPos())
	{
		KillPlayer();
	}

	/* プレイヤーが死んでいるかどうか */
	if (m_pPlayer->GetLivibgFlag() == false)
	{
		/* 死んでいたらシーン遷移 */
		MoveScene();
	}
}

/// <summary>
/// 描画
/// </summary>
void PlayScene::Draw()
{
	m_pCamera->Shoot(m_pPlayer->GetxPos());
	m_pPlayer->ThisObjRender();
	m_pBlocks->ThisObjRender();
	m_pGoal->ThisObjRender();

	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		m_pKuriboVector[i]->ThisObjRender();
	}

	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		m_pNokonokoVector[i]->ThisObjRender();
	}
}