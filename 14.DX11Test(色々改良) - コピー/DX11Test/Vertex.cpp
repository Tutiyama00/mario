#include<d3dcompiler.h>
#include<d3d11.h>
#include"Vertex.h"
#include"Math.h"

/*######################  Polygon  ###################################*/

/*----------------------  protected   -----------------------------------*/

/// <summary>
/// 頂点を移動させる
/// </summary>
/// <param name="xAmount">X移動量</param>
/// <param name="yAmount">Y移動量</param>
void Polygon::VertexMove(float xAmount, float yAmount)
{
	m_xPos += xAmount;
	m_yPos += yAmount;

	for (int i = 0; i < m_VertexArraySize; i++)
	{
		m_pVertexArray[i].pos.x += xAmount;
		m_pVertexArray[i].pos.y += yAmount;
	}
}


/*######################  Square  ###################################*/

/*----------------------  public   -----------------------------------*/

void Square::Abstract(){}

//コンストラクタ
Square::Square(Vector3 pos, Vector2 size)
{
	m_VertexArraySize = 4;
	m_IndexArraySize  = 6;

	m_pVertexArray = new vertex[m_VertexArraySize];
	m_pIndexArray  = new WORD  [m_IndexArraySize];

	m_xPos = pos.x;
	m_yPos = pos.y;
	m_zPos = pos.z;
	m_xSize = size.x;
	m_ySize = size.y;

	m_pVertexArray[0] = { { pos.x - (size.x / 2) , pos.y + (size.y / 2) , pos.z } ,  {0,0} }; //左上
	m_pVertexArray[1] = { { pos.x + (size.x / 2) , pos.y - (size.y / 2) , pos.z } ,  {1,1} }; //右下
	m_pVertexArray[2] = { { pos.x - (size.x / 2) , pos.y - (size.y / 2) , pos.z } ,  {0,1} }; //左下
	m_pVertexArray[3] = { { pos.x + (size.x / 2) , pos.y + (size.y / 2) , pos.z } ,  {1,0} }; //右上

	m_pIndexArray[0] = { 0 };
	m_pIndexArray[1] = { 1 };
	m_pIndexArray[2] = { 2 };
	m_pIndexArray[3] = { 0 };
	m_pIndexArray[4] = { 3 };
	m_pIndexArray[5] = { 1 };

	m_DiagonalLength = OriginalMath::Math::CosineTheorem90(m_pVertexArray[0].pos.x - m_pVertexArray[1].pos.x, m_pVertexArray[0].pos.y - m_pVertexArray[1].pos.y);
}

//デストラクタ
Square::~Square()
{
	if (m_pVertexArray != nullptr) { delete[] m_pVertexArray; m_pVertexArray = nullptr; }  //この行を基底クラス側でやるとエラーがでる←newしたクラス側でdeleteしなければならない
	if (m_pIndexArray  != nullptr) { delete[] m_pIndexArray;  m_pIndexArray  = nullptr; }  //この行を基底クラス側でやるとエラーがでる←newしたクラス側でdeleteしなければならない
}

//衝突判定
bool Square::CollisionCheck(Polygon* checkPolygon)
{
	//調査対象と自分の距離を比較して衝突の可能性があるかどうか判断
	if (OriginalMath::Math::CosineTheorem90(checkPolygon->GetxPos() - m_xPos, checkPolygon->GetyPos() - m_yPos) <= m_DiagonalLength)
	{
		for (int i = 0; i < checkPolygon->GetVertexArraySize(); i++)
		{
			//自分の内側に重なっているかどうか
			if(AABBCheck(m_pVertexArray[0].pos, m_pVertexArray[1].pos, checkPolygon->m_pVertexArray[i].pos, m_ColAdjustedValue))
			{
				return true;
			}
		}

		Vector3 leftUpVertex    = m_pVertexArray[0].pos;
		Vector3 rightDownVertex = m_pVertexArray[1].pos;
		Vector3 leftDownVertex  = m_pVertexArray[2].pos;
		Vector3 rightUpVertex   = m_pVertexArray[3].pos;

		leftUpVertex.x    -= m_ColAdjustedValue;
		leftUpVertex.y    += m_ColAdjustedValue;
		rightDownVertex.x += m_ColAdjustedValue;
		rightDownVertex.y -= m_ColAdjustedValue;
		leftDownVertex.x  -= m_ColAdjustedValue;
		leftDownVertex.y  -= m_ColAdjustedValue;
		rightUpVertex.x   += m_ColAdjustedValue;
		rightUpVertex.y   += m_ColAdjustedValue;

		if (AABBCheck(checkPolygon->m_pVertexArray[0].pos, checkPolygon->m_pVertexArray[1].pos, leftUpVertex, 0.0f)
			|| AABBCheck(checkPolygon->m_pVertexArray[0].pos, checkPolygon->m_pVertexArray[1].pos, rightDownVertex, 0.0f)
			|| AABBCheck(checkPolygon->m_pVertexArray[0].pos, checkPolygon->m_pVertexArray[1].pos, leftDownVertex, 0.0f)
			|| AABBCheck(checkPolygon->m_pVertexArray[0].pos, checkPolygon->m_pVertexArray[1].pos, rightUpVertex, 0.0f))
		{
			return true;
		}

	}

	return false;
}

//衝突判定
bool Square::CollisionCheck(Polygon* checkPolygon, float threshold)
{
	//調査対象と自分の距離を比較して衝突の可能性があるかどうか判断
	if (OriginalMath::Math::CosineTheorem90(checkPolygon->GetxPos() - m_xPos, checkPolygon->GetyPos() - m_yPos) <= m_DiagonalLength)
	{
		for (int i = 0; i < checkPolygon->GetVertexArraySize(); i++)
		{
			//自分の内側に重なっているかどうか
			if (AABBCheck(m_pVertexArray[0].pos, m_pVertexArray[1].pos, checkPolygon->m_pVertexArray[i].pos, threshold))
			{
				return true;
			}
		}

		Vector3 leftUpVertex    = m_pVertexArray[0].pos;
		Vector3 rightDownVertex = m_pVertexArray[1].pos;
		Vector3 leftDownVertex  = m_pVertexArray[2].pos;
		Vector3 rightUpVertex   = m_pVertexArray[3].pos;

		leftUpVertex.x    -= threshold;
		leftUpVertex.y    += threshold;
		rightDownVertex.x += threshold;
		rightDownVertex.y -= threshold;
		leftDownVertex.x  -= threshold;
		leftDownVertex.y  -= threshold;
		rightUpVertex.x   += threshold;
		rightUpVertex.y   += threshold;

		if (AABBCheck(checkPolygon->m_pVertexArray[0].pos, checkPolygon->m_pVertexArray[1].pos, leftUpVertex, 0.0f)
			|| AABBCheck(checkPolygon->m_pVertexArray[0].pos, checkPolygon->m_pVertexArray[1].pos, rightDownVertex, 0.0f)
			|| AABBCheck(checkPolygon->m_pVertexArray[0].pos, checkPolygon->m_pVertexArray[1].pos, leftDownVertex, 0.0f)
			|| AABBCheck(checkPolygon->m_pVertexArray[0].pos, checkPolygon->m_pVertexArray[1].pos, rightUpVertex, 0.0f))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// AABB方式の衝突判定
/// </summary>
/// <param name="leftUpVertex">左上頂点</param>
/// <param name="rightDownVertex">右上頂点</param>
/// <param name="targetVertex">調査頂点</param>
/// <param name="threshold">調整値（正＝判定大きく、負＝判定小さく）</param>
/// <returns>T＝衝突している、F＝衝突していない</returns>
bool Square::AABBCheck(Vector3 leftUpVertex, Vector3 rightDownVertex, Vector3 targetVertex, float threshold)
{
	if ((leftUpVertex.x - threshold) <= targetVertex.x && (rightDownVertex.x + threshold) >= targetVertex.x
		&& (leftUpVertex.y + threshold) >= targetVertex.y && (rightDownVertex.y - threshold) <= targetVertex.y)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 平行に反転させる
/// </summary>
void Square::ParallelInverted()
{
	if (m_ParallelInvertedFlag)
	{
		m_ParallelInvertedFlag = false;
		/* 元の状態に戻す */
		m_pVertexArray[0].tex.x = 0;
		m_pVertexArray[0].tex.y = 0;

		m_pVertexArray[1].tex.x = 1;
		m_pVertexArray[1].tex.y = 1;

		m_pVertexArray[2].tex.x = 0;
		m_pVertexArray[2].tex.y = 1;

		m_pVertexArray[3].tex.x = 1;
		m_pVertexArray[3].tex.y = 0;
	}
	else
	{
		m_ParallelInvertedFlag = true;
		/* 反転させる */
		m_pVertexArray[0].tex.x = 1;
		m_pVertexArray[0].tex.y = 0;

		m_pVertexArray[1].tex.x = 0;
		m_pVertexArray[1].tex.y = 1;

		m_pVertexArray[2].tex.x = 1;
		m_pVertexArray[2].tex.y = 1;

		m_pVertexArray[3].tex.x = 0;
		m_pVertexArray[3].tex.y = 0;
	}
}