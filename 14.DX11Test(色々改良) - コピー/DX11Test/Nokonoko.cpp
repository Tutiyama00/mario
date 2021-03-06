#include"Nokonoko.h"
#include"Player.h"
#include"Animation.h"
#include"TextureData.h"
#include"SoundData.h"
#include"ScoreManager.h"

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="size">サイズ</param>
Nokonoko::Nokonoko(Vector3 pos, Vector2 size) : Enemy(pos, size)
{
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_pMainTextureResource = TextureData::Instance()->GetNOKONOKO1_TR();
	m_pMainTextureSRV      = TextureData::Instance()->GetNOKONOKO1_TSRV();

	m_InputFlag.Set(InputFlagCode::INPUT_LEFT);

	m_pWalkAnimation = new Animation();
	m_pWalkAnimation->AddAnimResource(TextureData::Instance()->GetNOKONOKO1_TR(), TextureData::Instance()->GetNOKONOKO1_TSRV());
	m_pWalkAnimation->AddAnimResource(TextureData::Instance()->GetNOKONOKO2_TR(), TextureData::Instance()->GetNOKONOKO2_TSRV());
	m_pWalkAnimation->SetAnimIntervalFlame(25);

	m_DieScorePoint = NOKONOKO_SCORE;
}

/// <summary>
/// デストラクタ
/// </summary>
Nokonoko::~Nokonoko()
{
	if (m_pWalkAnimation != nullptr) { delete m_pWalkAnimation; m_pWalkAnimation = nullptr; }
}

/*-------------------------------------         ----------------------------------*/
/*-------------------------------------  Enemy  ----------------------------------*/
/*-------------------------------------         ----------------------------------*/

/// <summary>
/// 動作
/// </summary>
void Nokonoko::Move()
{
	/*生きていない状態だったらリターンして動かさない*/
	if (!m_LivingFlag)
	{
		if (m_RenderFlag)
		{
			/*通常の死に方をしているかどうか*/
			if (m_StanderdDieFlag)
			{
				/*通常死亡演出*/
				StandardDie();

				return;
			}
		}
	}

	switch (m_MoveObjState)
	{
	case MoveObjState::CHECK_GROUND:
		m_MoveObjState = MoveObjState::FALL;

	case MoveObjState::ON_THE_GROUND:

		if (m_JumpLevelCount != m_MaxJumpLevel)
		{
			m_JumpLevelCount = m_MaxJumpLevel;
		}

		break;

	case MoveObjState::FALL:

		Fall();

		break;
	}

	/* 甲羅が止まっている状態だったら左右に動かなくする */
	if (m_NokonokoState == NokonokoState::KOURA_STOP)
	{
		m_InputFlag.ReSet(InputFlagCode::INPUT_LEFT);
		m_InputFlag.ReSet(InputFlagCode::INPUT_RIGHT);
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_RIGHT))
	{
		if (m_NokonokoState == NokonokoState::KOURA_RUN)
		{
			m_NowWalkSpeed = m_MaxWalkSpeed * 7;
		}
		else
		{
			m_NowWalkSpeed = m_MaxWalkSpeed;
		}
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_LEFT))
	{
		if (m_NokonokoState == NokonokoState::KOURA_RUN)
		{
			m_NowWalkSpeed = -m_MaxWalkSpeed * 7;
		}
		else
		{
			m_NowWalkSpeed = -m_MaxWalkSpeed;
		}
	}

	if (m_NokonokoState != NokonokoState::KOURA_STOP)
	{
		Walk(m_NowWalkSpeed);
	}

	if (m_MoveObjState == MoveObjState::ON_THE_GROUND)
	{
		m_MoveObjState = MoveObjState::CHECK_GROUND;
	}
}

/// <summary>
/// プレイヤーのチェック
/// </summary>
/// <param name="pPlayer">チェックするプレイヤーのポインター</param>
/// <param name="pInputFlag">入力情報</param>
void Nokonoko::CheckPlayer(Player* pPlayer)
{
	if (!m_LivingFlag) { return; }
	if (!pPlayer->GetLivibgFlag()) { return; }

	/* プレイヤーと衝突していたら */
	if (CollisionCheck(pPlayer, -(pPlayer->GetxSize() / 3)))
	{
		switch (m_NokonokoState)
		{
		case NokonokoState::NORMAL:

			if (m_StateKeepFlag)
			{
				StateKeepFlame();
				break;
			}

			/* 上から衝突しているのかどうか */
			if (UpCheck(pPlayer))
			{
				SoundData::Instance()->GetSTOMPsoundBuffer()->SetCurrentPosition(0);
				SoundData::Instance()->GetSTOMPsoundBuffer()->Play(0, 0, 0);

				pPlayer->MiniJumpStart();
				m_NokonokoState = NokonokoState::KOURA_STOP;
				m_InputFlag.AllReSet();
				StateKeepFlameStart();
			}
			else
			{
				/* プレイヤーを殺す */
				pPlayer->Die();
			}

			break;

		case NokonokoState::KOURA_STOP:

			if (m_StateKeepFlag)
			{
				StateKeepFlame();
				break;
			}

			StateKeepFlameStart();
			m_NokonokoState = NokonokoState::KOURA_RUN;

			SoundData::Instance()->GetKICKsoundBuffer()->SetCurrentPosition(0);
			SoundData::Instance()->GetKICKsoundBuffer()->Play(0, 0, 0);

			/* 左右どちら側に衝突しているか */
			if (pPlayer->GetxPos() <= GetxPos())
			{
				m_InputFlag.Set(InputFlagCode::INPUT_RIGHT);
			}
			else
			{
				m_InputFlag.Set(InputFlagCode::INPUT_LEFT);
			}

			break;

		case NokonokoState::KOURA_RUN:


			if (m_StateKeepFlag)
			{
				StateKeepFlame();
				break;
			}

			if (UpCheck(pPlayer))
			{
				SoundData::Instance()->GetSTOMPsoundBuffer()->SetCurrentPosition(0);
				SoundData::Instance()->GetSTOMPsoundBuffer()->Play(0, 0, 0);

				pPlayer->MiniJumpStart();
				m_NokonokoState = NokonokoState::KOURA_STOP;
				m_InputFlag.AllReSet();
				StateKeepFlameStart();
			}
			else
			{
				pPlayer->Die();
			}

			break;
		}
	}
}

/// <summary>
/// Enemyのチェック
/// </summary>
/// <param name="pEnemy">チェックする対象</param>
void Nokonoko::CheckEnemy(Enemy* pEnemy)
{
	if (!m_LivingFlag) { return; }
	if (!pEnemy->GetLivingFlag()) { return; }

	if (CollisionCheck(pEnemy))
	{
		/* エネミーのインプットフラグの取得 */
		InputFlag enemyInput = pEnemy->GetInputFlag();

		switch (m_NokonokoState)
		{
		case NokonokoState::KOURA_RUN:

			/*ノコノコがどちら側で敵にぶつかったか*/
			if (m_xPos < pEnemy->GetxPos())
			{
				/*右に飛ばす*/
				pEnemy->StartStandardDie(true);
			}
			else
			{
				/*左に飛ばす*/
				pEnemy->StartStandardDie(false);
			}
			break;

		default:
			/* エネミーが右に進もうとしているかどうか */
			if (enemyInput.Check(InputFlagCode::INPUT_RIGHT))
			{
				/* このプレイヤーがこのブロックの左側に衝突しているか */
				if (LeftCheck(pEnemy))
				{
					/* もしそうなら左に進ませる */
					enemyInput.ReSet(InputFlagCode::INPUT_RIGHT);
					enemyInput.Set(InputFlagCode::INPUT_LEFT);
				}
			}

			/* エネミーが左に進もうとしているかどうか */
			if (enemyInput.Check(InputFlagCode::INPUT_LEFT))
			{
				/* このプレイヤーがこのブロックの右側に衝突しているか */
				if (RightCheck(pEnemy))
				{
					/* もしそうなら右に進ませる */
					enemyInput.ReSet(InputFlagCode::INPUT_LEFT);
					enemyInput.Set(InputFlagCode::INPUT_RIGHT);
				}
			}

			/* エネミーがFALL中かどうか */
			if (pEnemy->GetMoveObjState() == MoveObjState::FALL || pEnemy->GetMoveObjState() == MoveObjState::CHECK_GROUND)
			{
				if (UpCheck(pEnemy))
				{
					/* もしそうならステートを接地中に変える */
					pEnemy->SetMoveObjState(MoveObjState::ON_THE_GROUND);
				}
			}

			break;
		}

		/* 更新後のインプットフラグを同期 */
		pEnemy->SetInputFlag(enemyInput);
	}
}

/// <summary>
/// 描画
/// </summary>
void Nokonoko::ThisObjRender()
{
	/*描画してもよいかどうか*/
	if (!m_RenderFlag) { return; }

	/*生きているかどうか*/
	if (m_LivingFlag)
	{
		/*ノコノコのステートがノーマル状態かどうか*/
		if (m_NokonokoState == NokonokoState::NORMAL)
		{
			/*歩くアニメーションをさせる*/
			m_pWalkAnimation->AnimPlay();
			m_pMainTextureResource = m_pWalkAnimation->GetAnimTextureResource();
			m_pMainTextureSRV = m_pWalkAnimation->GetAnimTextureSRV();

			/* 右と左どちらに向いているのかの判定 */
			if (m_NowWalkSpeed > 0 && m_ParallelInvertedFlag)
			{
				ParallelInverted();
			}
			else if (m_NowWalkSpeed < 0 && !m_ParallelInvertedFlag)
			{
				ParallelInverted();
			}
		}
		else
		{
			/*テクスチャを甲羅にする*/
			m_pMainTextureResource = TextureData::Instance()->GetKOURA1_TR();
			m_pMainTextureSRV = TextureData::Instance()->GetKOURA1_TSRV();
		}
	}

	/*描画*/
	Render(m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// 通常死亡処理演出の開始
/// </summary>
/// <param name="direction"></param>
void Nokonoko::StartStandardDie(bool direction)
{
	/*死亡処理*/
	Die();
	/*通常の死亡処理が始まるのでフラグを立てる*/
	m_StanderdDieFlag = true;

	/*方向が左かどうか*/
	if (!direction)
	{
		/*X軸の移動量の符号を負にする*/
		m_S_DieMoveXMoveAmount *= -1;
	}

	/*甲羅状態にする*/
	m_pMainTextureResource = TextureData::Instance()->GetKOURA1_TR();
	m_pMainTextureSRV = TextureData::Instance()->GetKOURA1_TSRV();

	/*テクスチャをさかさまにする*/
	m_pVertexArray[0].tex.x = 0;  m_pVertexArray[0].tex.y = 1;
	m_pVertexArray[1].tex.x = 1;  m_pVertexArray[1].tex.y = 0;
	m_pVertexArray[2].tex.x = 0;  m_pVertexArray[2].tex.y = 0;
	m_pVertexArray[3].tex.x = 1;  m_pVertexArray[3].tex.y = 1;
}

/*#####################################           #####################################*/
/*#####################################  PRIVATE  #####################################*/
/*#####################################           #####################################*/

void Nokonoko::StateKeepFlameStart()
{
	m_StateKeepFlag = true;
	m_StateKeepFlameCount = 0;
}

void Nokonoko::StateKeepFlame()
{
	if (m_StateKeepFlameCount <= M_STATE_KEEP_FLAME)
	{
		m_StateKeepFlameCount++;
	}
	else
	{
		m_StateKeepFlag = false;
	}
}