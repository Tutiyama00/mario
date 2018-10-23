#include"Player.h"
#include"Block.h"
#include"Enum.h"
#include"Flag.h"

Player::Player(float xPos, float yPos, float zPos, float xSize, float ySize, ID3D11Device* pDevice) : Square::Square(xPos, yPos, zPos, xSize, ySize)
{
	LoadTexture(pDevice, L"Mario.png");
	CreateShader(pDevice, L"VertexShader.vsh", L"PixelShader.psh");
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

Player::~Player() {}

void Player::Abstract() {}

void Player::Move(InputFlag* inputFlag)
{
	switch (m_PlayerState)
	{
	case MoveObjState::CHECK_GROUND:
		m_PlayerState = MoveObjState::FALL;

	case MoveObjState::ON_THE_GROUND:

		if (m_JumpLevelCount != M_MAX_JUMP_LEVEL)
		{
			m_JumpLevelCount = M_MAX_JUMP_LEVEL;
		}

		if (inputFlag->Check(InputFlagCode::INPUT_SPACE))
		{
			if (m_JumpFlag)
			{
				Jump();
				m_PlayerState = MoveObjState::JUMP;
				break;
			}
		}
		else if (!m_JumpFlag)
		{
			m_JumpFlag = true;
		}

		break;

	case MoveObjState::JUMP:
		if (!inputFlag->Check(InputFlagCode::INPUT_SPACE) || !Jump())
		{
			m_JumpFlag = false;
			m_PlayerState = MoveObjState::FALL;
		}

		break;

	case MoveObjState::FALL:

		Fall();

		if (!inputFlag->Check(InputFlagCode::INPUT_SPACE) && !m_JumpFlag)
		{
			m_JumpFlag = true;
		}

		break;
	}

	if (inputFlag->Check(InputFlagCode::INPUT_RIGHT))
	{
		if (m_NowWalkSpeed >= M_MAX_WALK_SPEED)
		{
			m_NowWalkSpeed = M_MAX_WALK_SPEED;
		}
		else
		{
			m_NowWalkSpeed += m_WalkFluctuationAmount;
		}
	}

	if (inputFlag->Check(InputFlagCode::INPUT_LEFT))
	{
		if (m_NowWalkSpeed <= -M_MAX_WALK_SPEED)
		{
			m_NowWalkSpeed = -M_MAX_WALK_SPEED;
		}
		else
		{
			m_NowWalkSpeed -= m_WalkFluctuationAmount;
		}
	}

	//横入力されていないときに移動量の減衰をする
	if (!inputFlag->Check(InputFlagCode::INPUT_LEFT) && !inputFlag->Check(InputFlagCode::INPUT_RIGHT))
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

	//横移動
	Walk(m_NowWalkSpeed);

	if (m_PlayerState == MoveObjState::ON_THE_GROUND)
	{
		m_PlayerState = MoveObjState::CHECK_GROUND;
	}
}

void Player::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
}

void Player::ThisObjCreateBuffer(ID3D11Device* pDevice)
{
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

//歩く（移動量横）
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

//ジャンプ(マリオ式)
bool Player::Jump()
{
	if (m_JumpLevelCount > 0)
	{
		float jumpAmount = m_JumpPower * (m_JumpLevelCount / M_JUMP_ABJUST_POINT);
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

//落下（マリオ式）
void Player::Fall()
{
	float fallAmount = m_JumpPower * (m_JumpLevelCount / M_JUMP_ABJUST_POINT);
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

	if (m_JumpLevelCount < M_MAX_JUMP_LEVEL)
	{
		m_JumpLevelCount++;
	}
}