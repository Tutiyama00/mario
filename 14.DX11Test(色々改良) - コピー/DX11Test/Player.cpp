#include"Player.h"
#include"Block.h"
#include"Enum.h"
#include"Flag.h"

/*コンストラクタ*/
Player::Player(Vector3 pos, Vector2 size) : Square::Square(pos, size)
{
	LoadTexture(L"Texture/Mario.png");
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/*デストラクタ*/
Player::~Player() {}

/*死亡処理*/
void Player::Die()
{
	/*まだ生きていた場合処理する*/
	if (m_LivingFlag)
	{
		/*生存フラグを折る*/
		m_LivingFlag = false;

		/*残機が０以上だったら残機を減らす*/
		if (m_Life > 0)
		{
			m_Life--;
		}
	}
}

/*抽象化関数*/
void Player::Abstract() {}

/*動作関数*/
void Player::Move(InputFlag* inputFlag)
{
	/*生きていない状態だったらリターンして動かさない*/
	if (!m_LivingFlag)
	{
		return;
	}

	switch (m_MoveObjState)
	{
	case MoveObjState::CHECK_GROUND:
		m_MoveObjState = MoveObjState::FALL;

	case MoveObjState::ON_THE_GROUND:

		if (m_JumpLevelCount != m_MaxJumpLevel)
		{
			m_JumpLevelCount = m_MaxJumpLevel;
		}

		if (inputFlag->Check(InputFlagCode::INPUT_SPACE))
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
		if (!inputFlag->Check(InputFlagCode::INPUT_SPACE) || !Jump())
		{
			m_JumpFlag = false;
			m_MoveObjState = MoveObjState::FALL;
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
		if (m_NowWalkSpeed >= m_MaxWalkSpeed)
		{
			m_NowWalkSpeed = m_MaxWalkSpeed;
		}
		else
		{
			m_NowWalkSpeed += m_WalkFluctuationAmount;
		}
	}

	if (inputFlag->Check(InputFlagCode::INPUT_LEFT))
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

	if (m_MoveObjState == MoveObjState::ON_THE_GROUND)
	{
		m_MoveObjState = MoveObjState::CHECK_GROUND;
	}
}

void Player::ThisObjRender()
{
	Render(m_pVertexArray, m_IndexArraySize);
}

void Player::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/*歩く
 *第一引数・移動量横*/
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

/*ジャンプ(マリオ式)*/
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

/*落下（マリオ式）*/
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