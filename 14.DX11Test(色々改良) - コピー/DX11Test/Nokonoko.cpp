#include"Nokonoko.h"
#include"Player.h"

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
	LoadTexture(L"Texture/NOKONOKO1.png");
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_InputFlag.Set(InputFlagCode::INPUT_LEFT);
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
	if (!m_LivingFlag) { return; }

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
			Walk(m_MaxWalkSpeed * 7);
		}
		else
		{
			Walk(m_MaxWalkSpeed);
		}
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_LEFT))
	{
		if (m_NokonokoState == NokonokoState::KOURA_RUN)
		{
			Walk(-m_MaxWalkSpeed * 7);
		}
		else
		{
			Walk(-m_MaxWalkSpeed);
		}
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

	/* プレイヤーと衝突していたら */
	if (CollisionCheck(pPlayer))
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
				pPlayer->MiniJumpStart();
				LoadTexture(L"Texture/KOURA1.png");
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

	if (CollisionCheck(pEnemy))
	{
		/* エネミーのインプットフラグの取得 */
		InputFlag enemyInput = pEnemy->GetInputFlag();

		switch (m_NokonokoState)
		{
		case NokonokoState::KOURA_RUN:
			pEnemy->Die();
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