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
Square::Square(float xPos, float yPos, float zPos, float xSize, float ySize)
{
	m_VertexArraySize = 4;
	m_IndexArraySize  = 6;

	m_pVertexArray = new vertex[m_VertexArraySize];
	m_pIndexArray  = new WORD  [m_IndexArraySize];

	m_xPos = xPos;
	m_yPos = yPos;
	m_zPos = zPos;
	m_xSize = xSize;
	m_ySize = ySize;

	m_pVertexArray[0] = { { xPos - (xSize / 2) , yPos + (ySize / 2) , zPos } ,  {0,0} }; //左上
	m_pVertexArray[1] = { { xPos + (xSize / 2) , yPos - (ySize / 2) , zPos } ,  {1,1} }; //右下
	m_pVertexArray[2] = { { xPos - (xSize / 2) , yPos - (ySize / 2) , zPos } ,  {0,1} }; //左下
	m_pVertexArray[3] = { { xPos + (xSize / 2) , yPos + (ySize / 2) , zPos } ,  {1,0} }; //右上

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
	if (OriginalMath::Math::CosineTheorem90(checkPolygon->m_xPos - m_xPos, checkPolygon->m_yPos - m_yPos) <= m_DiagonalLength)
	{
		for (int i = 0; i < checkPolygon->m_VertexArraySize; i++)
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



/*######################  Triangle  ###################################*/

/*----------------------  public   -----------------------------------*/

void Triangle::Abstract() {}

Triangle::Triangle(float xPos, float yPos, float zPos, float xSize, float ySize)
{
	m_VertexArraySize = 3;
	m_IndexArraySize  = 3;

	m_pVertexArray = new vertex[m_VertexArraySize];
	m_pIndexArray  = new WORD  [m_IndexArraySize];

	m_xPos  = xPos;
	m_yPos  = yPos;
	m_zPos  = zPos;
	m_xSize = xSize;
	m_ySize = ySize;

	m_pVertexArray[0] = { {               xPos, yPos + (ySize / 2), zPos} , {0,0} };
	m_pVertexArray[1] = { { xPos + (xSize / 2), yPos - (ySize / 2), zPos} , {1,1} };
	m_pVertexArray[2] = { { xPos - (xSize / 2), yPos - (ySize / 2), zPos} , {1,0} };

	m_pIndexArray[0] = { 0 };
	m_pIndexArray[1] = { 1 };
	m_pIndexArray[2] = { 2 };
}

//デストラクタ
Triangle::~Triangle()
{
	delete[] m_pVertexArray;  //この行を基底クラス側でやるとエラーがでる←newしたクラス側でdeleteしなければならない
	delete[] m_pIndexArray;   //この行を基底クラス側でやるとエラーがでる←newしたクラス側でdeleteしなければならない
}