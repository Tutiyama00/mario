#include"Goal.h"
#include"TextureData.h"
#include"Image.h"
#include"TextureData.h"
#include"Player.h"
#include"SoundData.h"

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">ポジション</param>
Goal::Goal(Vector3 pos)
{
	m_pPin    = new Image({ pos.x + m_PinLocalPos.x, pos.y + m_PinLocalPos.y, pos.z + m_PinLocalPos.z }, m_PinSize, TextureData::Instance()->GetGOAL_PIN_TR(), TextureData::Instance()->GetGOAL_PIN_TSRV(), false);
	m_pPole   = new Image({ pos.x + m_PoleLocalPos.x, pos.y + m_PoleLocalPos.y, pos.z + m_PoleLocalPos.z }, m_PoleSize, TextureData::Instance()->GetGOAL_POLE_TR(), TextureData::Instance()->GetGOAL_POLE_TSRV(), false);
	m_pFlag   = new Image({ pos.x + m_FlagLocalPos.x, pos.y + m_FlagLocalPos.y, pos.z + m_FlagLocalPos.z }, m_FlagSize, TextureData::Instance()->GetGOAL_FLAG_TR(), TextureData::Instance()->GetGOAL_FLAG_TSRV(), false);
	m_pCastle = new Image({ pos.x + m_CastleLocalPos.x, pos.y + m_CastleLocalPos.y, pos.z + m_CastleLocalPos.z }, m_CastleSize, TextureData::Instance()->GetGOAL_CASTLE_TR(), TextureData::Instance()->GetGOAL_CASTLE_TSRV(), false);

	ThisObjCreateBuffer();

	m_FlagDownAmount = (m_pFlag->GetyPos() - pos.y) / M_FLAG_DOWN_MAX_FRAME;
	m_downEndYPos = pos.y;
	m_CastlelineXPos = m_pCastle->GetxPos();
	m_GoalLineXPos = pos.x;
}

/// <summary>
/// デストラクタ
/// </summary>
Goal::~Goal() 
{
	if (m_pPin    != nullptr) { delete m_pPin;    m_pPin    = nullptr; }
	if (m_pPole   != nullptr) { delete m_pPole;   m_pPole   = nullptr; }
	if (m_pFlag   != nullptr) { delete m_pFlag;   m_pFlag   = nullptr; }
	if (m_pCastle != nullptr) { delete m_pCastle; m_pCastle = nullptr; }
};

/// <summary>
/// ゴールしているかチェック
/// </summary>
/// <param name="pPlayer"></param>
/// <returns></returns>
bool Goal::GoalCheck(Player* pPlayer)
{
	if (pPlayer->m_pVertexArray[1].pos[0] >= m_GoalLineXPos)
	{
		if (!m_GoalFlag)
		{
			m_GoalFlag = true;
			SoundData::Instance()->GetSTANDARD_BGMsoundBuffer()->Stop();
			SoundData::Instance()->GetSTAGE_CLEARPsoundBuffer()->SetCurrentPosition(0);
			SoundData::Instance()->GetSTAGE_CLEARPsoundBuffer()->Play(0, 0, 0);
		}

		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// ゴール演出
/// </summary>
/// <param name="pPlayer"></param>
/// <returns></returns>
bool Goal::Play(Player* pPlayer)
{
	if (m_FlagDownFrameCounter < M_FLAG_DOWN_MAX_FRAME)
	{
		m_FlagDownFrameCounter++;
		m_pFlag->Move({ 0.0f,-m_FlagDownAmount,0.0f });
		pPlayer->GoalPlay(m_FlagDownAmount, m_downEndYPos, true);
	}
	else
	{
		if (pPlayer->GetxPos() <= m_CastlelineXPos)
		{
			pPlayer->GoalPlay(m_FlagDownAmount, m_downEndYPos, false);
		}
		else
		{
			pPlayer->SetRenderFlag(false);
			if (m_LastWaitFrameCounter < M_LAST_WAIT_MAX_FRAME)
			{
				m_LastWaitFrameCounter++;
			}
			else
			{
				SoundData::Instance()->GetSTAGE_CLEARPsoundBuffer()->Stop();
				return false;
			}
		}
	}

	return true;
}

/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// このオブジェクトの描画
/// </summary>
void Goal::ThisObjRender()
{
	m_pFlag->ThisObjRender();
	m_pPin->ThisObjRender();
	m_pPole->ThisObjRender();
	m_pCastle->ThisObjRender();
}

/// <summary>
/// このオブジェクトのバッファの生成
/// </summary>
void Goal::ThisObjCreateBuffer()
{
	m_pPin   ->ThisObjCreateBuffer();
	m_pPole  ->ThisObjCreateBuffer();
	m_pFlag  ->ThisObjCreateBuffer();
	m_pCastle->ThisObjCreateBuffer();
}