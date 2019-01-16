#include"Player.h"
#include"Block.h"
#include"Enum.h"
#include"Flag.h"
#include"Animation.h"
#include<string>
#include"TextureData.h"
#include"SoundData.h"

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="size">サイズ</param>
Player::Player(Vector3 pos, Vector2 size) : Square::Square(pos, size)
{
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_pMainTextureResource = TextureData::Instance()->GetMARIO_STAND_TR();
	m_pMainTextureSRV      = TextureData::Instance()->GetMARIO_STAND_TSRV();

	/* 走るアニメーションの登録 */
	m_pRunAnimation = new Animation();
	m_pRunAnimation->AddAnimResource(TextureData::Instance()->GetMARIO_STAND_TR(), TextureData::Instance()->GetMARIO_STAND_TSRV());
	m_pRunAnimation->AddAnimResource(TextureData::Instance()->GetMARIO_RUN1_TR() , TextureData::Instance()->GetMARIO_RUN1_TSRV());
	m_pRunAnimation->AddAnimResource(TextureData::Instance()->GetMARIO_RUN2_TR() , TextureData::Instance()->GetMARIO_RUN2_TSRV());
	m_pRunAnimation->AddAnimResource(TextureData::Instance()->GetMARIO_RUN3_TR() , TextureData::Instance()->GetMARIO_RUN3_TSRV());
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	if (m_pRunAnimation != nullptr) { delete m_pRunAnimation; m_pRunAnimation = nullptr; }
}

/// <summary>
/// 死亡処理
/// </summary>
void Player::Die()
{
	/* 無敵状態だったら返す */
	if (m_InvincibleFlag) { return; }

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

		/* 死亡音流す */
		SoundData::Instance()->GetSTANDARD_BGMsoundBuffer()->Stop();
		SoundData::Instance()->GetMARIO_DIEsoundBuffer()->SetCurrentPosition(0);
		SoundData::Instance()->GetMARIO_DIEsoundBuffer()->Play(0, 0, 0);
	}
}

/// <summary>
/// ゴール時のプレイヤーの挙動
/// </summary>
/// <param name="downAmount"></param>
/// <param name="downEndYPos"></param>
/// <param name="down"></param>
void Player::GoalPlay(float downAmount, float downEndYPos, bool down)
{
	if (!m_GoalPlayFlag) { m_GoalPlayFlag = true; }

	switch (m_GoalPlayState)
	{
	case GoalPlayState::POLE_DOWN:
		if (down)
		{
			if (m_yPos > downEndYPos)
			{
				m_yPos -= downAmount;
				for (int i = 0; i < m_VertexArraySize; i++)
				{
					m_pVertexArray[i].pos[1] -= downAmount;
				}
			}
			else
			{
				m_GoalPlayState = GoalPlayState::POLE_STOP;
			}
		}
		else
		{
			m_GoalPlayState = GoalPlayState::POLE_PARALLEL_WAIT;
			ParallelInverted();
			m_xPos += m_xSize;
			for (int i = 0; i < m_VertexArraySize; i++)
			{
				m_pVertexArray[i].pos[0] += m_xSize;
			}
		} 
		break;

	case GoalPlayState::POLE_STOP:
		if (!down)
		{
			m_GoalPlayState = GoalPlayState::POLE_PARALLEL_WAIT;
			ParallelInverted();
			m_xPos += m_xSize;
			for (int i = 0; i < m_VertexArraySize; i++)
			{
				m_pVertexArray[i].pos[0] += m_xSize;
			}
		}
		break;

	case GoalPlayState::POLE_PARALLEL_WAIT:
		if (m_PoleStopWaitCounter < M_POLE_STOP_WAIT_FRAME)
		{
			m_PoleStopWaitCounter++;
		}
		else
		{
			m_GoalPlayState = GoalPlayState::WALK_TO_CASTLE;
			MiniJumpStart();
			m_InputFlag.AllReSet();
			m_InputFlag.Set(InputFlagCode::INPUT_RIGHT);
		}
		break;

	case GoalPlayState::WALK_TO_CASTLE:
		m_InputFlag.AllReSet();
		m_InputFlag.Set(InputFlagCode::INPUT_RIGHT);
		PlayerMove();
		break;
	}
}

/// <summary>
/// プレイヤーの移動
/// </summary>
void Player::PlayerMove()
{
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
				SoundData::Instance()->GetMARIO_JUMP_SMALLsoundBuffer()->SetCurrentPosition(0);
				SoundData::Instance()->GetMARIO_JUMP_SMALLsoundBuffer()->Play(0, 0, 0);
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

	//横入力されていないときに移動量の減衰をする
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

	//横移動
	Walk(m_NowWalkSpeed);

	if (m_MoveObjState == MoveObjState::ON_THE_GROUND)
	{
		m_MoveObjState = MoveObjState::CHECK_GROUND;
	}

	/* 右と左どちらに向いているのかの判定 */
	if (m_NowWalkSpeed > 0 && m_ParallelInvertedFlag)
	{
		ParallelInverted();
	}
	else if (m_NowWalkSpeed < 0 && !m_ParallelInvertedFlag)
	{
		ParallelInverted();
	}
}

/*-------------------------------------            ----------------------------------*/
/*-------------------------------------  IMoveObj  ----------------------------------*/
/*-------------------------------------            ----------------------------------*/

/// <summary>
/// 動作
/// </summary>
void Player::Move()
{
	/*生きていない状態だったらリターンして動かさない*/
	if (!m_LivingFlag) { return; }
	/*ゴール中だったらリターン*/
	if (m_GoalPlayFlag) { return; }

	PlayerMove();
}


/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// このオブジェクトの描画
/// </summary>
void Player::ThisObjRender()
{
	if (m_LivingFlag)
	{


		/* 描画するテクスチャの設定 */
		switch (m_MoveObjState)
		{
		case MoveObjState::CHECK_GROUND:

			/* 歩いているのかの判定 */
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
			m_pMainTextureSRV = TextureData::Instance()->GetMARIO_JUMP_TSRV();
		}
	}
	else
	{
		m_pMainTextureResource = TextureData::Instance()->GetMARIO_DEAD_TR();
		m_pMainTextureSRV = TextureData::Instance()->GetMARIO_DEAD_TSRV();
	}

	Render(m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// このオブジェクトのバッファの生成
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
/// 歩く
/// </summary>
/// <param name="xAmount">移動量（X軸）</param>
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
/// ジャンプ(マリオ式)
/// </summary>
/// <returns>ジャンプできたかどうか　true=できた　false=できなかった</returns>
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
/// 落下（マリオ式）
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
/// 小ジャンプの開始
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
/// 小ジャンプ
/// </summary>
/// <returns></returns>
bool Player::MiniJump()
{
	if (m_MiniJumpCount <= M_MINI_JUMP_COUNT_MAX)
	{
		m_MiniJumpCount++;

		/* 指定したフレーム以上になったら */
		if (m_MiniJumpCount > M_MINI_JUMP_COUNT_INVINCIBLE_MAX)
		{
			/* 無敵状態を解除する */
			m_InvincibleFlag = false;
		}

		return Jump();
	}

	return false;
}

bool Player::DieMove()
{
	if (m_LivingFlag) { return false; }

	if (m_DieMoveFrameCounter < M_DIE_MOVE_FRAME)
	{
		if (m_DieMoveFrameCounter >= M_DIE_MOVE_STOP_FRAME)
		{
			if (std::abs(m_DieMoveNowSpeed) <= M_DIE_MOVE_SPEED_MAX)
			{
				m_DieMoveNowSpeed -= m_DieMoveChangeAmount;
			}
			else
			{
				if (m_DieMoveNowSpeed < 0)
				{
					m_DieMoveNowSpeed = -M_DIE_MOVE_SPEED_MAX;
				}
				else
				{
					m_DieMoveNowSpeed = M_DIE_MOVE_SPEED_MAX;
				}
			}

			/* 移動 */
			m_yPos += m_DieMoveNowSpeed;
			for (int i = 0; i < m_VertexArraySize; i++)
			{
				m_pVertexArray[i].pos[1] += m_DieMoveNowSpeed;
			}
		}

		m_DieMoveFrameCounter++;

		return true;
	}
	else
	{
		return false;
	}
}