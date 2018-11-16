#include"Enemy.h"
#include"Player.h"

/// <summary>
/// プレイヤーのチェック
/// </summary>
/// <param name="pPlayer">チェックするプレイヤーのポインター</param>
/// <param name="pInputFlag">入力情報</param>
void Enemy::CheckPlayer(Player* pPlayer, InputFlag* pInputFlag)
{
	/* プレイヤーと衝突していたら */
	if (CollisionCheck(pPlayer))
	{
		/* プレイヤーを殺す */
		pPlayer->Die();
	}
}

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
	Render(m_pVertexArray, m_IndexArraySize);
}