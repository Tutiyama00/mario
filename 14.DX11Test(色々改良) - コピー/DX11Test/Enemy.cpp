#include"Enemy.h"
#include"Player.h"


/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// ���S����
/// </summary>
void Enemy::Die()
{
	m_LivingFlag = false;
}


/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  NotPlayer  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// �v���C���[�̃`�F�b�N
/// </summary>
/// <param name="pPlayer">�`�F�b�N����v���C���[�̃|�C���^�[</param>
/// <param name="pInputFlag">���͏��</param>
void Enemy::CheckPlayer(Player* pPlayer)
{
	if (!m_LivingFlag) { return; }

	/* �v���C���[�ƏՓ˂��Ă����� */
	if (CollisionCheck(pPlayer))
	{
		if (UpCheck(pPlayer))
		{
			Die();
		}
		else
		{
			/* �v���C���[���E�� */
			pPlayer->Die();
		}
	}
}

/// <summary>
/// Enemy�̃`�F�b�N
/// </summary>
/// <param name="pEnemy">�`�F�b�N����Ώ�</param>
void Enemy::CheckEnemy(Enemy* pEnemy)
{
	if (!m_LivingFlag) { return; }

	if (CollisionCheck(pEnemy))
	{
		/* �G�l�~�[�̃C���v�b�g�t���O�̎擾 */
		InputFlag enemyInput = pEnemy->GetInputFlag();

		/* �v���C���[���E�ɐi�����Ƃ��Ă��邩�ǂ��� */
		if (enemyInput.Check(InputFlagCode::INPUT_RIGHT))
		{
			/* ���̃v���C���[�����̃u���b�N�̍����ɏՓ˂��Ă��邩 */
			if (LeftCheck(pEnemy))
			{
				/* ���������Ȃ獶�ɐi�܂��� */
				enemyInput.ReSet(InputFlagCode::INPUT_RIGHT);
				enemyInput.Set(InputFlagCode::INPUT_LEFT);
			}
		}

		/* �v���C���[�����ɐi�����Ƃ��Ă��邩�ǂ��� */
		if (enemyInput.Check(InputFlagCode::INPUT_LEFT))
		{
			/* ���̃v���C���[�����̃u���b�N�̉E���ɏՓ˂��Ă��邩 */
			if (RightCheck(pEnemy))
			{
				/* ���������Ȃ�E�ɐi�܂��� */
				enemyInput.ReSet(InputFlagCode::INPUT_LEFT);
				enemyInput.Set(InputFlagCode::INPUT_RIGHT);
			}
		}

		/* �v���C���[��FALL�����ǂ��� */
		if (pEnemy->GetMoveObjState() == MoveObjState::FALL || pEnemy->GetMoveObjState() == MoveObjState::CHECK_GROUND)
		{
			if (UpCheck(pEnemy))
			{
				/* ���������Ȃ�X�e�[�g��ڒn���ɕς��� */
				pEnemy->SetMoveObjState(MoveObjState::ON_THE_GROUND);

				return;
			}
		}

		/* �X�V��̃C���v�b�g�t���O�𓯊� */
		pEnemy->SetInputFlag(enemyInput);
	}
}



/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

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
/// ����
/// </summary>
/// <param name="xAmount">�ړ��ʁiX���j</param>
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
/// �W�����v(�}���I��)
/// </summary>
/// <returns>�W�����v�ł������ǂ����@true=�ł����@false=�ł��Ȃ�����</returns>
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
/// �����i�}���I���j
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