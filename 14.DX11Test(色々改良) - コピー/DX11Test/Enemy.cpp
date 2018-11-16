#include"Enemy.h"
#include"Player.h"

/// <summary>
/// �v���C���[�̃`�F�b�N
/// </summary>
/// <param name="pPlayer">�`�F�b�N����v���C���[�̃|�C���^�[</param>
/// <param name="pInputFlag">���͏��</param>
void Enemy::CheckPlayer(Player* pPlayer, InputFlag* pInputFlag)
{
	/* �v���C���[�ƏՓ˂��Ă����� */
	if (CollisionCheck(pPlayer))
	{
		/* �v���C���[���E�� */
		pPlayer->Die();
	}
}

/// <summary>
/// ���̃I�u�W�F�N�g�̃o�b�t�@�̍쐬
/// </summary>
void Enemy::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/// <summary>
/// ���̃I�u�W�F�N�g�̕`��
/// </summary>
void Enemy::ThisObjRender()
{
	Render(m_pVertexArray, m_IndexArraySize);
}