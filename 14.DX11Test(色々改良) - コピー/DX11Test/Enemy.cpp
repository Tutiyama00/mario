#include"Enemy.h"
#include"Player.h"

/// <summary>
/// プレイヤーのチェック
/// </summary>
/// <param name="pPlayer">チェックするプレイヤーのポインター</param>
/// <param name="pInputFlag">入力情報</param>
void Enemy::CheckPlayer(Player* pPlayer)
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

/// <summary>
/// 歩く
/// </summary>
/// <param name="xAmount">移動量（X軸）</param>
void Enemy::Walk(float xAmount)
{
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