#include"Enemy.h"
#include"Player.h"
#include"SoundData.h"
#include"ScoreManager.h"

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
	if (CollisionCheck(pPlayer))
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
	if (!m_LivingFlag) { return; }

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

	m_xPos += xAmount;

	m_pVertexArray[0] = {
	{ m_pVertexArray[0].pos[0] + xAmount, m_pVertexArray[0].pos[1] , m_pVertexArray[0].pos[2] } ,
	{ m_pVertexArray[0].tex[0],m_pVertexArray[0].tex[1]} };

	m_pVertexArray[1] = {
	{ m_pVertexArray[1].pos[0] + xAmount, m_pVertexArray[1].pos[1] , m_pVertexArray[1].pos[2] } ,
	{ m_pVertexArray[1].tex[0],m_pVertexArray[1].tex[1]} };

	m_pVertexArray[2] = {
	{ m_pVertexArray[2].pos[0] + xAmount, m_pVertexArray[2].pos[1] , m_pVertexArray[2].pos[2] } ,
	{ m_pVertexArray[2].tex[0],m_pVertexArray[2].tex[1]} };

	m_pVertexArray[3] = {
	{ m_pVertexArray[3].pos[0] + xAmount, m_pVertexArray[3].pos[1] , m_pVertexArray[3].pos[2] } ,
	{ m_pVertexArray[3].tex[0],m_pVertexArray[3].tex[1]} };
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
		m_yPos += jumpAmount;

		m_pVertexArray[0] = {
		{ m_pVertexArray[0].pos[0], m_pVertexArray[0].pos[1] + jumpAmount , m_pVertexArray[0].pos[2] } ,
		{ m_pVertexArray[0].tex[0],m_pVertexArray[0].tex[1]} };

		m_pVertexArray[1] = {
		{ m_pVertexArray[1].pos[0], m_pVertexArray[1].pos[1] + jumpAmount , m_pVertexArray[1].pos[2] } ,
		{ m_pVertexArray[1].tex[0],m_pVertexArray[1].tex[1]} };

		m_pVertexArray[2] = {
		{ m_pVertexArray[2].pos[0], m_pVertexArray[2].pos[1] + jumpAmount , m_pVertexArray[2].pos[2] } ,
		{ m_pVertexArray[2].tex[0],m_pVertexArray[2].tex[1]} };

		m_pVertexArray[3] = {
		{ m_pVertexArray[3].pos[0], m_pVertexArray[3].pos[1] + jumpAmount , m_pVertexArray[3].pos[2] } ,
		{ m_pVertexArray[3].tex[0],m_pVertexArray[3].tex[1]} };

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
	m_yPos -= fallAmount;

	m_pVertexArray[0] = {
	{ m_pVertexArray[0].pos[0], m_pVertexArray[0].pos[1] - fallAmount , m_pVertexArray[0].pos[2] } ,
	{ m_pVertexArray[0].tex[0],m_pVertexArray[0].tex[1]} };

	m_pVertexArray[1] = {
	{ m_pVertexArray[1].pos[0], m_pVertexArray[1].pos[1] - fallAmount , m_pVertexArray[1].pos[2] } ,
	{ m_pVertexArray[1].tex[0],m_pVertexArray[1].tex[1]} };

	m_pVertexArray[2] = {
	{ m_pVertexArray[2].pos[0], m_pVertexArray[2].pos[1] - fallAmount , m_pVertexArray[2].pos[2] } ,
	{ m_pVertexArray[2].tex[0],m_pVertexArray[2].tex[1]} };

	m_pVertexArray[3] = {
	{ m_pVertexArray[3].pos[0], m_pVertexArray[3].pos[1] - fallAmount , m_pVertexArray[3].pos[2] } ,
	{ m_pVertexArray[3].tex[0],m_pVertexArray[3].tex[1]} };

	if (m_JumpLevelCount < m_MaxJumpLevel)
	{
		m_JumpLevelCount++;
	}
}