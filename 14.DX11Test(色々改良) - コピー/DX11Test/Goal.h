#pragma once

#include"Vertex.h"
#include"RenderObj.h"

/* 前方宣言 */
class Image;

class Goal : public RenderObj
{
public:
	Goal(Vector3 pos);
	~Goal();

private:
	Image* m_pPin    = nullptr;
	Image* m_pPole   = nullptr;
	Image* m_pFlag   = nullptr;
	Image* m_pCastle = nullptr;

	Vector3 m_PinLocalPos    = { 0.0f, 1.0f, 0.0f };
	Vector2 m_PinSize        = { 0.2f, 0.2f       };
	Vector3 m_PoleLocalPos   = { 0.0f, 0.0f, 0.0f };
	Vector2 m_PoleSize       = { 0.1f, 1.0f       };
	Vector3 m_FlagLocalPos   = { 0.0f, 1.0f, 0.0f };
	Vector2 m_FlagSize       = { 0.2f, 0.2f       };
	Vector3 m_CastleLocalPos = { 1.0f, -0.1f, 0.0f };
	Vector2 m_CastleSize     = { 0.5f, 0.5f       };

	float m_GoalLineXPos   = 0.0f;  //ゴール判定のX座標
	float m_CastlelineXPos = 0.0f;  //城の入り口のX座標

/*------RenderObj------*/
public:
	void ThisObjRender();
	void ThisObjCreateBuffer();

protected:
	void Abstract() {};
};