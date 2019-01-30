#include"Enemy.h"
#include"Player.h"
#include"SoundData.h"
#include"ScoreManager.h"
#include<string>

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// 死亡処理
/// </summary>
void Enemy::Die()
{
	if (!m_LivingFlag) { return; }

	ScoreManager::Instance()->AddScore(m_DieScorePoint);
	m_LivingFlag = false;
}

/// <summary>
/// 通常の死亡処理演出
/// </summary>
/// <param name="direction">飛ぶ方向（true=右、false=左）</param>
void Enemy::StartStandardDie(bool direction)
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

	m_pVertexArray[0].tex.x = 0;  m_pVertexArray[0].tex.y = 1;
	m_pVertexArray[1].tex.x = 1;  m_pVertexArray[1].tex.y = 0;
	m_pVertexArray[2].tex.x = 0;  m_pVertexArray[2].tex.y = 0;
	m_pVertexArray[3].tex.x = 1;  m_pVertexArray[3].tex.y = 1;
}

/*#####################################             #####################################*/
/*#####################################  protected  #####################################*/
/*#####################################             #####################################*/

/// <summary>
/// 通常の死亡処理演出
/// </summary>
void Enemy::StandardDie()
{
	/*まだ死亡処理にかかるフレーム数内かどうか*/
	if (m_S_DieMoveFrameCounter < M_S_DIE_MOVE_FRAME)
	{
		if (std::abs(m_S_DieMoveNowSpeed) <= M_S_DIE_MOVE_SPEED_MAX)
		{
			m_S_DieMoveNowSpeed -= m_S_DieMoveChangeAmount;
		}
		else
		{
			if (m_S_DieMoveNowSpeed < 0)
			{
				m_S_DieMoveNowSpeed = -M_S_DIE_MOVE_SPEED_MAX;
			}
			else
			{
				m_S_DieMoveNowSpeed = M_S_DIE_MOVE_SPEED_MAX;
			}
		}

		/* 移動 */
		VertexMove(m_S_DieMoveXMoveAmount, m_S_DieMoveNowSpeed);
	}
	else
	{
		m_RenderFlag = false;
	}
}

/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  NotPlayer  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// プレイヤーのチェック
/// </summary>
/// <param name="pPlayer">チェックするプレイヤーのポインター</param>
/// <param name="pInputFlag">入力情報</param>
void Enemy::CheckPlayer(Player* pPlayer)
{
	if (!m_LivingFlag) { return; }
	if (!pPlayer->GetLivibgFlag()) { return; }

	/* プレイヤーと衝突していたら */
	if (CollisionCheck(pPlayer, -(pPlayer->GetxSize() / 2)))
	{
		if (UpCheck(pPlayer))
		{
			SoundData::Instance()->GetSTOMPsoundBuffer()->SetCurrentPosition(0);
			SoundData::Instance()->GetSTOMPsoundBuffer()->Play(0,0,0);
			pPlayer->MiniJumpStart();
			Die();
		}
		else
		{
			/* プレイヤーを殺す */
			pPlayer->Die();
		}
	}
}

/// <summary>
/// Enemyのチェック
/// </summary>
/// <param name="pEnemy">チェックする対象</param>
void Enemy::CheckEnemy(Enemy* pEnemy)
{
	if (!m_LivingFlag) { return; }
	if (!pEnemy->GetLivingFlag()) { return; }

	if (CollisionCheck(pEnemy))
	{
		/* エネミーのインプットフラグの取得 */
		InputFlag enemyInput = pEnemy->GetInputFlag();

		/* エネミーが右に進もうとしているかどうか */
		if (enemyInput.Check(InputFlagCode::INPUT_RIGHT))
		{
			/* このエネミーがこのブロックの左側に衝突しているか */
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
			/* このエネミーがこのブロックの右側に衝突しているか */
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

				return;
			}
		}

		/* 更新後のインプットフラグを同期 */
		pEnemy->SetInputFlag(enemyInput);
	}
}



/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// このオブジェクトのバッファの作成
/// </summary>
void Enemy::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/// <summary>
/// このオブジェクトの描画
/// </summary>
void Enemy::ThisObjRender()
{
	if (!m_RenderFlag) { return; }

	Render(m_pVertexArray, m_IndexArraySize);
}


/*#####################################             #####################################*/
/*#####################################  PROTECTED  #####################################*/
/*#####################################             #####################################*/

/*-------------------------------------            ----------------------------------*/
/*-------------------------------------  IMoveObj  ----------------------------------*/
/*-------------------------------------            ----------------------------------*/

/// <summary>
/// 歩く
/// </summary>
/// <param name="xAmount">移動量（X軸）</param>
void Enemy::Walk(float xAmount)
{
	if (!m_LivingFlag) { return; }

	VertexMove(xAmount, 0);
}

/// <summary>
/// ジャンプ(マリオ式)
/// </summary>
/// <returns>ジャンプできたかどうか　true=できた　false=できなかった</returns>
bool Enemy::Jump()
{
	if (!m_LivingFlag) { return false; }

	if (m_JumpLevelCount > 0)
	{
		float jumpAmount = m_JumpPower * (m_JumpLevelCount / m_JumpAbjustPoint);

		VertexMove(0, jumpAmount);

		m_JumpLevelCount--;

		return true;
	}

	return false;
}

/// <summary>
/// 落下（マリオ式）
/// </summary>
void Enemy::Fall()
{
	if (!m_LivingFlag) { return; }

	float fallAmount = m_JumpPower * (m_JumpLevelCount / m_JumpAbjustPoint);

	VertexMove(0, -fallAmount);

	if (m_JumpLevelCount < m_MaxJumpLevel)
	{
		m_JumpLevelCount++;
	}
}