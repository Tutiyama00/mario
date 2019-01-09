#pragma once

#include"Vertex.h"
#include"RenderObj.h"

/* 前方宣言 */
class Image;
class Player;

class Goal : public RenderObj
{
public:
	Goal(Vector3 pos);
	~Goal();

	bool GoalCheck(Player* pPlayer);
	bool Play(Player* pPlayer);

private:
	Image* m_pPin    = nullptr;
	Image* m_pPole   = nullptr;
	Image* m_pFlag   = nullptr;
	Image* m_pCastle = nullptr;

	Vector3 m_PinLocalPos    = { 0.0f, 0.75f, 0.0f };
	Vector2 m_PinSize        = { 0.05f, 0.05f       };
	Vector3 m_PoleLocalPos   = { 0.0f, 0.35f, 0.0f };
	Vector2 m_PoleSize       = { 0.0075f, 0.775f       };
	Vector3 m_FlagLocalPos   = { -0.04f, 0.675f, 0.0f };
	Vector2 m_FlagSize       = { 0.08f, 0.08f       };
	Vector3 m_CastleLocalPos = { 0.465f, 0.09f, 0.0f };
	Vector2 m_CastleSize     = { 0.4f, 0.4f       };

	float m_GoalLineXPos   = 0.0f;  //ゴール判定のX座標
	float m_CastlelineXPos = 0.0f;  //城の入り口のX座標

	const unsigned int M_FLAG_DOWN_MAX_FRAME = 120;  //旗が下りるのにかかるフレーム数
	unsigned int m_FlagDownFrameCounter = 0;  //旗が下りているときのフレームカウンター
	float m_FlagDownAmount = 0;  //旗が１フレームで降りてくる量
	float m_downEndYPos = 0;
	const unsigned int M_LAST_WAIT_MAX_FRAME = 360;  //プレイヤーが消えてから演出が終了するまでのフレーム数
	unsigned int m_LastWaitFrameCounter = 0;
	bool m_GoalFlag = false;

/*------RenderObj------*/
public:
	void ThisObjRender();
	void ThisObjCreateBuffer();

protected:
	void Abstract() {};
};