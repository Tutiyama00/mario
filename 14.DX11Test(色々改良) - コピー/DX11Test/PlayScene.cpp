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
	if (m_pStage             != nullptr) { delete m_pStage;             m_pStage             = nullptr; }
	if (m_pCamera            != nullptr) { delete m_pCamera;            m_pCamera            = nullptr; }
	StageObjDelete();
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
	m_pBlocks            = new Characters<Block>(TextureData::Instance()->GetBLOCK_TR(),        TextureData::Instance()->GetBLOCK_TSRV(),        L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	m_pBlockDummys       = new Characters<Image>(TextureData::Instance()->GetBLOCK_TR(),        TextureData::Instance()->GetBLOCK_TSRV(),        L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	m_pBlockGrounds      = new Characters<Block>(TextureData::Instance()->GetBLOCK_GROUND_TR(), TextureData::Instance()->GetBLOCK_GROUND_TSRV(), L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	m_pBlockGroundDummys = new Characters<Image>(TextureData::Instance()->GetBLOCK_GROUND_TR(), TextureData::Instance()->GetBLOCK_GROUND_TSRV(), L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	m_pClayPipes         = new Characters<ClayPipe>(TextureData::Instance()->GetCLAY_PIPE_TR(), TextureData::Instance()->GetCLAY_PIPE_TSRV(),    L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");

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

	/*背景の生成*/
	float xPos = m_StandardSize * m_BackGroundXPosAdjust;
	float yPos = m_StandardSize * -((m_pStage->GetStageHeight() - m_BackGroundYPosAdjust) - halfHeight);
	m_pBackGround = new BackGround(Vector3{ xPos,yPos,m_StandardZpos }, 
		                      Vector2{ m_StandardSize * m_BackGroundBlockAmount, m_StandardSize * m_BackGroundBlockAmount }, 
		                      TextureData::Instance()->GetBACK_GROUND_1_TR(), 
		                      TextureData::Instance()->GetBACK_GROUND_1_TSRV()
		                      );
	m_pBackGround->AddBackGround(TextureData::Instance()->GetBACK_GROUND_2_TR(), TextureData::Instance()->GetBACK_GROUND_2_TSRV());
	m_pBackGround->ThisObjCreateBuffer();

	m_pBlocks            -> ThisObjCreateBuffer();
	m_pBlockDummys       -> ThisObjCreateBuffer();
	m_pBlockGrounds      -> ThisObjCreateBuffer();
	m_pBlockGroundDummys -> ThisObjCreateBuffer();
	m_pClayPipes         -> ThisObjCreateBuffer();

	/*下の死亡判定ラインの計算*/
	m_UnderDeathLine = m_StandardSize * -(m_pStage->GetStageHeight() - halfHeight);

	/* カメラのX座標初期化 */
	m_CameraShootXPos = 0.8f;

	/* プレイヤー左限界値の初期化 */
	m_PlayerMoveEndXPos = m_CameraShootXPos - m_EndToShootXPosAmount;

	/* オブジェクト右限界値の初期化 */
	m_ObjMoveRightXPos    = m_CameraShootXPos + m_EndToShootXPosAmount + m_ObjMoveXPosAdjust;
	/* オブジェクト左限界値の初期化 */
	m_ObjMoveLeftXPos     = m_CameraShootXPos - m_EndToShootXPosAmount - m_ObjMoveXPosAdjust;
	/* ブロック右限界値の初期化 */
	m_BlockCheckRightXPos = m_CameraShootXPos + m_EndToShootXPosAmount + m_ObjMoveXPosAdjust + m_BlockCheckXPosDiff;
	/* ブロック左限界値の初期化 */
	m_BlockCheckLeftXPos  = m_CameraShootXPos - m_EndToShootXPosAmount - m_ObjMoveXPosAdjust - m_BlockCheckXPosDiff;
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

/// <summary>
/// ステージを構成するオブジェクトのデリート
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
	if (m_pBackGround        != nullptr) { delete m_pBackGround;        m_pBackGround        = nullptr; }

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
/// キャラ達の移動命令
/// </summary>
void PlayScene::MoveOrder()
{
	//プレイヤー移動
	m_pPlayer->Move();

	/*クリボーの移動*/
	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		EnemyMoveOrder(m_pKuriboVector[i]);
	}

	/*ノコノコの移動*/
	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		EnemyMoveOrder(m_pNokonokoVector[i]);
	}
}

/// <summary>
/// 敵の移動命令
/// </summary>
/// <param name="pEnemy">移動させる敵ポインタ</param>
void PlayScene::EnemyMoveOrder(Enemy* pEnemy)
{
	/*行動範囲内にいるのかどうか*/
	if (pEnemy->GetxPos() >= m_ObjMoveLeftXPos && pEnemy->GetxPos() <= m_ObjMoveRightXPos)
	{
		/*移動*/
		pEnemy->Move();
	}
}

/// <summary>
/// キャラ達のチェック命令
/// </summary>
void PlayScene::ObjCheckOrder()
{
	CollisionCheckBlock   (m_pBlocks);
	CollisionCheckBlock   (m_pBlockGrounds);
	CollisionCheckClayPipe();
	CollisionCheckKuribo  ();
	CollisionCheckNokonoko();
}

/// <summary>
/// //ゴールしたかのチェック
/// </summary>
void PlayScene::GoalCheckOrder()
{
	/*プレイヤーがゴールしているか*/
	if (m_pGoal->GoalCheck(m_pPlayer))
	{
		/*ゴール演出が終わっているか*/
		if (!m_pGoal->Play(m_pPlayer))
		{
			/*ステージのレベルを１上げる*/
			m_NowStageLevel++;
			/*ステージのレベルが１ワールド内にあるステージ数を上回っているかどうか*/
			if (m_NowStageLevel > M_IN_STAGE_AMOUNT)
			{
				/*ワールドのレベルを1上げる*/
				m_NowWorldLevel++;
				/*ステージのレベルを１に戻す*/
				m_NowStageLevel = 1;
			}

			/*次に読み込むファイルパスを設定*/
			std::string filePas = "Stage/STAGE_" + std::to_string(m_NowWorldLevel) + "-" + std::to_string(m_NowStageLevel) + ".txt";  //ステージのファイルパス

			/*ステージを変える*/
			m_pStage->ChangeStage(filePas.data());
			/*シーンをリスタート*/
			ReStart();
			/*次にリザルトシーンに飛ぶ*/
			m_NextGameState = GameState::RESULT;
		}
	}
}

/// <summary>
/// ブロックのコリジョンチェック
/// </summary>
/// <param name="pBlocks"></param>
void PlayScene::CollisionCheckBlock(Characters<Block>* pBlocks)
{
	//ブロック群の衝突判定
	for (int i = 0; i < pBlocks->m_ObjectVector.size(); i++)
	{
		/*判定可能範囲内にいるのかどうか*/
		if (pBlocks->m_ObjectVector[i]->GetxPos() >= m_BlockCheckLeftXPos && pBlocks->m_ObjectVector[i]->GetxPos() <= m_BlockCheckRightXPos)
		{
			/*プレイヤーに対してのチェック*/
			pBlocks->m_ObjectVector[i]->CheckPlayer(m_pPlayer);

			/*クリボーに対してのチェック*/
			for (int j = 0; j < m_pKuriboVector.size(); j++)
			{
				pBlocks->m_ObjectVector[i]->CheckEnemy(m_pKuriboVector[j]);
			}

			/*ノコノコに対してのチェック*/
			for (int j = 0; j < m_pNokonokoVector.size(); j++)
			{
				pBlocks->m_ObjectVector[i]->CheckEnemy(m_pNokonokoVector[j]);
			}
		}
	}
}

/// <summary>
/// ノコノコのコリジョンチェック
/// </summary>
void PlayScene::CollisionCheckNokonoko()
{
	/*ノコノコの衝突判定*/
	for (int i = 0; i < m_pNokonokoVector.size(); i++)
	{
		/*判定可能範囲内にいるのかどうか*/
		if (m_pNokonokoVector[i]->GetxPos() >= m_ObjMoveLeftXPos && m_pNokonokoVector[i]->GetxPos() <= m_ObjMoveRightXPos)
		{
			/* ノコノコとプレイヤーの比較 */
			m_pNokonokoVector[i]->CheckPlayer(m_pPlayer);

			/* チェックしているのが配列の最後のノコノコだった場合ノコノコ同士の処理しない */
			if (i + 1 >= m_pNokonokoVector.size()) { continue; }

			/*　ノコノコとノコノコの比較 */
			for (int j = i + 1; j < m_pNokonokoVector.size(); j++)
			{
				/* ノコノコが甲羅走りしているのかチェック */
				bool NokonokoRunStateFlagI = m_pNokonokoVector[i]->GetNokonokoState() == NokonokoState::KOURA_RUN;
				bool NokonokoRunStateFlagJ = m_pNokonokoVector[j]->GetNokonokoState() == NokonokoState::KOURA_RUN;

				/* 両方のノコノコが甲羅走り */
				if (NokonokoRunStateFlagI && NokonokoRunStateFlagJ)
				{
					if (m_pNokonokoVector[j]->CollisionCheck(m_pNokonokoVector[i]) && m_pNokonokoVector[i]->CollisionCheck(m_pNokonokoVector[j]))
					{
						/*それぞれどちら側にいるのか*/
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

				/* Iの方のノコノコだけが甲羅走り */
				if (NokonokoRunStateFlagI && !NokonokoRunStateFlagJ)
				{
					m_pNokonokoVector[i]->CheckEnemy(m_pNokonokoVector[j]);
					m_pNokonokoVector[j]->CheckEnemy(m_pNokonokoVector[i]);

					continue;
				}

				/* Jの方のノコノコだけが甲羅走り */
				if (!NokonokoRunStateFlagI && NokonokoRunStateFlagJ)
				{
					m_pNokonokoVector[j]->CheckEnemy(m_pNokonokoVector[i]);
					m_pNokonokoVector[i]->CheckEnemy(m_pNokonokoVector[j]);

					continue;
				}

				/* どのパターンにも当てはまらなかった場合 */
				m_pNokonokoVector[j]->CheckEnemy(m_pNokonokoVector[i]);
				m_pNokonokoVector[i]->CheckEnemy(m_pNokonokoVector[j]);
			}
		}
	}
}

/// <summary>
/// クリボーのコリジョンチェック
/// </summary>
void PlayScene::CollisionCheckKuribo()
{
	/*クリボーの衝突判定*/
	for (int i = 0; i < m_pKuriboVector.size(); i++)
	{
		/*判定可能範囲にいるのかどうか*/
		if (m_pKuriboVector[i]->GetxPos() >= m_ObjMoveLeftXPos && m_pKuriboVector[i]->GetxPos() <= m_ObjMoveRightXPos)
		{
			/*プレイヤーに対してのチェック*/
			m_pKuriboVector[i]->CheckPlayer(m_pPlayer);

			/*ノコノコに対してのチェック*/
			for (int j = 0; j < m_pNokonokoVector.size(); j++)
			{
				/*ノコノコが生きているかどうか*/
				if (m_pNokonokoVector[j]->GetLivingFlag())
				{
					/* クリボーとノコノコの比較 */
					m_pNokonokoVector[j]->CheckEnemy(m_pKuriboVector[i]);
					m_pKuriboVector[i]->CheckEnemy(m_pNokonokoVector[j]);
				}
			}

			/*クリボーに対してのチェック*/
			/*配列の最後尾かどうか*/
			if (i + 1 < m_pKuriboVector.size())
			{
				/*クリボーとクリボーの比較*/
				for (int c = i + 1; c < m_pKuriboVector.size(); c++)
				{
					/*対象のクリボーが生きているかどうか*/
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
/// 土管のコリジョンチェック
/// </summary>
void PlayScene::CollisionCheckClayPipe()
{
	/*土管群の対して衝突判定*/
	for (int i = 0; i < m_pClayPipes->m_ObjectVector.size(); i++)
	{
		/*判定可能範囲内にいるのかどうか*/
		if (m_pClayPipes->m_ObjectVector[i]->GetxPos() >= m_BlockCheckLeftXPos && m_pClayPipes->m_ObjectVector[i]->GetxPos() <= m_BlockCheckRightXPos)
		{
			/*プレイヤーに対してのチェック*/
			m_pClayPipes->m_ObjectVector[i]->CheckPlayer(m_pPlayer);

			/*クリボーに対してのチェック*/
			for (int j = 0; j < m_pKuriboVector.size(); j++)
			{
				m_pClayPipes->m_ObjectVector[i]->CheckEnemy(m_pKuriboVector[j]);
			}

			/*ノコノコに対してのチェック*/
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
/// ゲームの更新
/// </summary>
/// <param name="inputFlag"></param>
void PlayScene::UpDateGame(InputFlag inputFlag)
{
	m_NextGameState = GameState::PLAY;

	/* プレイヤーが左限界値を超えないようにする */
	if (m_pPlayer->GetxPos() <= m_PlayerMoveEndXPos)
	{
		inputFlag.ReSet(InputFlagCode::INPUT_LEFT);
	}

	/*入力情報をプレイヤーにセットする*/
	m_pPlayer->SetInputFlag(inputFlag);

	/*キャラクター達のコリジョンチェック*/
	ObjCheckOrder();

	/*移動命令*/
	MoveOrder();

	/*ゴールチェック*/
	GoalCheckOrder();
	
	/* カメラの映すX座標を変えていいか */
	if (m_pPlayer->GetxPos() >= m_CameraShootXPos)
	{
		/*カメラのX座標をプレイヤーに合わせる*/
		m_CameraShootXPos     = m_pPlayer->GetxPos();
		/* プレイヤー左限界値の初期化 */
		m_PlayerMoveEndXPos   = m_CameraShootXPos - m_EndToShootXPosAmount;
		/* オブジェクト右限界値の初期化 */
		m_ObjMoveRightXPos    = m_CameraShootXPos + m_EndToShootXPosAmount + m_ObjMoveXPosAdjust;
		/* オブジェクト左限界値の初期化 */
		m_ObjMoveLeftXPos     = m_CameraShootXPos - m_EndToShootXPosAmount - m_ObjMoveXPosAdjust;
		/* ブロック右限界値の初期化 */
		m_BlockCheckRightXPos = m_CameraShootXPos + m_EndToShootXPosAmount + m_ObjMoveXPosAdjust + m_BlockCheckXPosDiff;
		/* ブロック左限界値の初期化 */
		m_BlockCheckLeftXPos  = m_CameraShootXPos - m_EndToShootXPosAmount - m_ObjMoveXPosAdjust - m_BlockCheckXPosDiff;
	}

	/*背景を入れ替えるかどうかチェックする*/
	m_pBackGround->NextCheck(m_ObjMoveLeftXPos);

	/*プレイヤーが落下死しているかどうか*/
	if (m_UnderDeathLine > m_pPlayer->GetyPos())
	{
		/*プレイヤーを殺す*/
		KillPlayer();
	}

	/* プレイヤーが死んでいるかどうか */
	if (m_pPlayer->GetLivibgFlag() == false)
	{
		/*死亡演出が終わったかどうか*/
		if (!m_pPlayer->DieMove())
		{
			/*死亡演出が終わったらシーン遷移*/
			MoveScene();
		}
	}
}

/// <summary>
/// 描画
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
	m_pBackGround        -> ThisObjRender();
}