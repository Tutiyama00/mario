#include<d3dcompiler.h>
#include<d3d11.h>
#include"Vertex.h"
#include"Math.h"

/*######################  Polygon  ###################################*/

Polygon::~Polygon(){}

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

	m_DiagonalLength = OriginalMath::Math::CosineTheorem90(m_pVertexArray[0].pos[0] - m_pVertexArray[1].pos[0], m_pVertexArray[0].pos[1] - m_pVertexArray[1].pos[1]);
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
			//自分の内側に重なっていた場合
			if (m_pVertexArray[0].pos[0] <= checkPolygon->m_pVertexArray[i].pos[0] && m_pVertexArray[1].pos[0] >= checkPolygon->m_pVertexArray[i].pos[0])
			{
				if (m_pVertexArray[0].pos[1] >= checkPolygon->m_pVertexArray[i].pos[1] && m_pVertexArray[1].pos[1] <= checkPolygon->m_pVertexArray[i].pos[1])
				{
					return true;
				}
			}

			if (m_pVertexArray[i].pos[0] >= checkPolygon->m_pVertexArray[0].pos[0] && m_pVertexArray[i].pos[0] <= checkPolygon->m_pVertexArray[1].pos[0])
			{
				if (m_pVertexArray[i].pos[1] <= checkPolygon->m_pVertexArray[0].pos[1] && m_pVertexArray[i].pos[1] >= checkPolygon->m_pVertexArray[1].pos[1])
				{
					return true;
				}
			}
		}
	}

	return false;
}