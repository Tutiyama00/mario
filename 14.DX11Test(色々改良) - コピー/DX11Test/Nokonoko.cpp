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
	LoadTexture(L"Texture/NOKONOKO.png");
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

	if (m_InputFlag.Check(InputFlagCode::INPUT_RIGHT))
	{
		if (m_NokonokoState == NokonokoState::KOURA_RUN)
		{
			Walk(m_MaxWalkSpeed * 10);
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
			Walk(-m_MaxWalkSpeed * 10);
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
			/* 上から衝突しているのかどうか */
			if (UpCheck(pPlayer))
			{
				LoadTexture(L"Texture/KOURA.png");
				m_NokonokoState = NokonokoState::KOURA_STOP;
				m_InputFlag.AllReSet();
			}
			else
			{
				/* プレイヤーを殺す */
				pPlayer->Die();
			}

			break;

		case NokonokoState::KOURA_STOP:

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

			if (UpCheck(pPlayer))
			{
				m_NokonokoState = NokonokoState::KOURA_STOP;
				m_InputFlag.AllReSet();
			}
			else
			{
				//pPlayer->Die();
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