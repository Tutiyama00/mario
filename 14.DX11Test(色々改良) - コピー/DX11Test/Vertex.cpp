#include<d3dcompiler.h>
#include<d3d11.h>
#include"Vertex.h"
#include"Math.h"

/*######################  Polygon  ###################################*/

/*----------------------  protected   -----------------------------------*/

/// <summary>
/// ���_���ړ�������
/// </summary>
/// <param name="xAmount">X�ړ���</param>
/// <param name="yAmount">Y�ړ���</param>
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

//�R���X�g���N�^
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

	m_pVertexArray[0] = { { pos.x - (size.x / 2) , pos.y + (size.y / 2) , pos.z } ,  {0,0} }; //����
	m_pVertexArray[1] = { { pos.x + (size.x / 2) , pos.y - (size.y / 2) , pos.z } ,  {1,1} }; //�E��
	m_pVertexArray[2] = { { pos.x - (size.x / 2) , pos.y - (size.y / 2) , pos.z } ,  {0,1} }; //����
	m_pVertexArray[3] = { { pos.x + (size.x / 2) , pos.y + (size.y / 2) , pos.z } ,  {1,0} }; //�E��

	m_pIndexArray[0] = { 0 };
	m_pIndexArray[1] = { 1 };
	m_pIndexArray[2] = { 2 };
	m_pIndexArray[3] = { 0 };
	m_pIndexArray[4] = { 3 };
	m_pIndexArray[5] = { 1 };

	m_DiagonalLength = OriginalMath::Math::CosineTheorem90(m_pVertexArray[0].pos.x - m_pVertexArray[1].pos.x, m_pVertexArray[0].pos.y - m_pVertexArray[1].pos.y);
}

//�f�X�g���N�^
Square::~Square()
{
	if (m_pVertexArray != nullptr) { delete[] m_pVertexArray; m_pVertexArray = nullptr; }  //���̍s�����N���X���ł��ƃG���[���ł適new�����N���X����delete���Ȃ���΂Ȃ�Ȃ�
	if (m_pIndexArray  != nullptr) { delete[] m_pIndexArray;  m_pIndexArray  = nullptr; }  //���̍s�����N���X���ł��ƃG���[���ł適new�����N���X����delete���Ȃ���΂Ȃ�Ȃ�
}

//�Փ˔���
bool Square::CollisionCheck(Polygon* checkPolygon)
{
	//�����ΏۂƎ����̋������r���ďՓ˂̉\�������邩�ǂ������f
	if (OriginalMath::Math::CosineTheorem90(checkPolygon->GetxPos() - m_xPos, checkPolygon->GetyPos() - m_yPos) <= m_DiagonalLength)
	{
		for (int i = 0; i < checkPolygon->GetVertexArraySize(); i++)
		{
			//�����̓����ɏd�Ȃ��Ă��邩�ǂ���
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

//�Փ˔���
bool Square::CollisionCheck(Polygon* checkPolygon, float threshold)
{
	//�����ΏۂƎ����̋������r���ďՓ˂̉\�������邩�ǂ������f
	if (OriginalMath::Math::CosineTheorem90(checkPolygon->GetxPos() - m_xPos, checkPolygon->GetyPos() - m_yPos) <= m_DiagonalLength)
	{
		for (int i = 0; i < checkPolygon->GetVertexArraySize(); i++)
		{
			//�����̓����ɏd�Ȃ��Ă��邩�ǂ���
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
/// AABB�����̏Փ˔���
/// </summary>
/// <param name="leftUpVertex">���㒸�_</param>
/// <param name="rightDownVertex">�E�㒸�_</param>
/// <param name="targetVertex">�������_</param>
/// <param name="threshold">�����l�i��������傫���A�������菬�����j</param>
/// <returns>T���Փ˂��Ă���AF���Փ˂��Ă��Ȃ�</returns>
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
/// ���s�ɔ��]������
/// </summary>
void Square::ParallelInverted()
{
	if (m_ParallelInvertedFlag)
	{
		m_ParallelInvertedFlag = false;
		/* ���̏�Ԃɖ߂� */
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
		/* ���]������ */
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