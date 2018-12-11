#include"Player.h"
#include"Block.h"
#include"Enum.h"
#include"Flag.h"
#include"Animation.h"
#include<string>
#include"TextureData.h"

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="size">�T�C�Y</param>
Player::Player(Vector3 pos, Vector2 size) : Square::Square(pos, size)
{
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_pMainTextureResource = TextureData::Instance()->GetMARIO_STAND_TR();
	m_pMainTextureSRV = TextureData::Instance()->GetMARIO_STAND_TSRV();

	/* ����A�j���[�V�����̓o�^ */
	m_pRunAnimation = new Animation();
	m_pRunAnimation->AddAnimResource(TextureData::Instance()->GetMARIO_STAND_TR(), TextureData::Instance()->GetMARIO_STAND_TSRV());
	m_pRunAnimation->AddAnimResource(TextureData::Instance()->GetMARIO_RUN1_TR() , TextureData::Instance()->GetMARIO_RUN1_TSRV());
	m_pRunAnimation->AddAnimResource(TextureData::Instance()->GetMARIO_RUN2_TR() , TextureData::Instance()->GetMARIO_RUN2_TSRV());
	m_pRunAnimation->AddAnimResource(TextureData::Instance()->GetMARIO_RUN3_TR() , TextureData::Instance()->GetMARIO_RUN3_TSRV());
}

Player::~Player()
{
	if (m_pRunAnimation != nullptr) { delete m_pRunAnimation; m_pRunAnimation = nullptr; }
}

/// <summary>
/// ���S����
/// </summary>
void Player::Die()
{
	/* ���G��Ԃ�������Ԃ� */
	if (m_InvincibleFlag) { return; }

	/*�܂������Ă����ꍇ��������*/
	if (m_LivingFlag)
	{
		/*�����t���O��܂�*/
		m_LivingFlag = false;

		/*�c�@���O�ȏゾ������c�@�����炷*/
		if (m_Life > 0)
		{
			m_Life--;
		}
	}
}

/*-------------------------------------            ----------------------------------*/
/*-------------------------------------  IMoveObj  ----------------------------------*/
/*-------------------------------------            ----------------------------------*/

/// <summary>
/// ����
/// </summary>
void Player::Move()
{
	/*�����Ă��Ȃ���Ԃ������烊�^�[�����ē������Ȃ�*/
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

		if (m_InputFlag.Check(InputFlagCode::INPUT_SPACE))
		{
			if (m_JumpFlag)
			{
				Jump();
				m_MoveObjState = MoveObjState::JUMP;
				break;
			}
		}
		else if (!m_JumpFlag)
		{
			m_JumpFlag = true;
		}

		break;

	case MoveObjState::JUMP:

		if (m_MiniJumpFlag)
		{
			if (!MiniJump())
			{
				m_JumpFlag = false;
				m_MoveObjState = MoveObjState::FALL;
			}
		}
		else
		{
			if (!m_InputFlag.Check(InputFlagCode::INPUT_SPACE) || !Jump())
			{
				m_JumpFlag = false;
				m_MoveObjState = MoveObjState::FALL;
			}
		}

		break;

	case MoveObjState::FALL:

		if (m_MiniJumpFlag) { m_MiniJumpFlag = false; }

		Fall();

		if (!m_InputFlag.Check(InputFlagCode::INPUT_SPACE) && !m_JumpFlag)
		{
			m_JumpFlag = true;
		}

		break;
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_RIGHT))
	{
		if (m_NowWalkSpeed >= m_MaxWalkSpeed)
		{
			m_NowWalkSpeed = m_MaxWalkSpeed;
		}
		else
		{
			m_NowWalkSpeed += m_WalkFluctuationAmount;
		}
	}

	if (m_InputFlag.Check(InputFlagCode::INPUT_LEFT))
	{
		if (m_NowWalkSpeed <= -m_MaxWalkSpeed)
		{
			m_NowWalkSpeed = -m_MaxWalkSpeed;
		}
		else
		{
			m_NowWalkSpeed -= m_WalkFluctuationAmount;
		}
	}

	//�����͂���Ă��Ȃ��Ƃ��Ɉړ��ʂ̌���������
	if (!m_InputFlag.Check(InputFlagCode::INPUT_LEFT) && !m_InputFlag.Check(InputFlagCode::INPUT_RIGHT))
	{
		if (m_NowWalkSpeed > m_SlipStopThreshold)
		{
			m_NowWalkSpeed -= m_SlipStopAmount;
		}
		else if (m_NowWalkSpeed < -m_SlipStopThreshold)
		{
			m_NowWalkSpeed += m_SlipStopAmount;
		}
		else
		{
			m_NowWalkSpeed = 0;
		}
	}

	//���ړ�
	Walk(m_NowWalkSpeed);

	if (m_MoveObjState == MoveObjState::ON_THE_GROUND)
	{
		m_MoveObjState = MoveObjState::CHECK_GROUND;
	}
}


/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// ���̃I�u�W�F�N�g�̕`��
/// </summary>
void Player::ThisObjRender()
{
	/* �`�悷��e�N�X�`���̐ݒ� */
	switch (m_MoveObjState)
	{
	case MoveObjState::CHECK_GROUND:

		/* �����Ă���̂��̔��� */
		if (m_NowWalkSpeed != 0)
		{
			m_pRunAnimation->AnimPlay();
			m_pMainTextureResource = m_pRunAnimation->GetAnimTextureResource();
			m_pMainTextureSRV = m_pRunAnimation->GetAnimTextureSRV();
		}
		else
		{
			m_pRunAnimation->AnimReset();
			m_pMainTextureResource = TextureData::Instance()->GetMARIO_STAND_TR();
			m_pMainTextureSRV = TextureData::Instance()->GetMARIO_STAND_TSRV();
		}

		break;

	default:
		m_pMainTextureResource = TextureData::Instance()->GetMARIO_JUMP_TR();
		m_pMainTextureSRV=TextureData::Instance()->GetMARIO_JUMP_TSRV();
	}

	/* �E�ƍ��ǂ���Ɍ����Ă���̂��̔��� */
	if (m_NowWalkSpeed > 0 && m_ParallelInvertedFlag)
	{
		ParallelInverted();
	}
	else if(m_NowWalkSpeed < 0 && !m_ParallelInvertedFlag)
	{
		ParallelInverted();
	}

	Render(m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// ���̃I�u�W�F�N�g�̃o�b�t�@�̐���
/// </summary>
void Player::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}


/*#####################################           #####################################*/
/*#####################################  PRIVATE  #####################################*/
/*#####################################           #####################################*/


/*-------------------------------------            ----------------------------------*/
/*-------------------------------------  IMoveObj  ----------------------------------*/
/*-------------------------------------            ----------------------------------*/


/// <summary>
/// ����
/// </summary>
/// <param name="xAmount">�ړ��ʁiX���j</param>
void Player::Walk(float xAmount)
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
/// �W�����v(�}���I��)
/// </summary>
/// <returns>�W�����v�ł������ǂ����@true=�ł����@false=�ł��Ȃ�����</returns>
bool Player::Jump()
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
/// �����i�}���I���j
/// </summary>
void Player::Fall()
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

/// <summary>
/// ���W�����v�̊J�n
/// </summary>
void Player::MiniJumpStart()
{
	m_MiniJumpFlag   = true;
	m_InvincibleFlag = true;
	m_MoveObjState   = MoveObjState::JUMP;
	m_MiniJumpCount  = 0;
	m_JumpLevelCount = M_MINI_JUMP_COUNT_MAX;
}

/// <summary>
/// ���W�����v
/// </summary>
/// <returns></returns>
bool Player::MiniJump()
{
	if (m_MiniJumpCount <= M_MINI_JUMP_COUNT_MAX)
	{
		m_MiniJumpCount++;

		/* �w�肵���t���[���ȏ�ɂȂ����� */
		if (m_MiniJumpCount > M_MINI_JUMP_COUNT_INVINCIBLE_MAX)
		{
			/* ���G��Ԃ��������� */
			m_InvincibleFlag = false;
		}

		return Jump();
	}

	return false;
}