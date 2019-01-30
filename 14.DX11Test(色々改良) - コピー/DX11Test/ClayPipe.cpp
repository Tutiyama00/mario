#include"ClayPipe.h"

ClayPipe::ClayPipe(Vector3 pos, Vector2 size, unsigned int height) : Block(pos, size)
{
	m_pVertexArray[0].pos.y += (size.y * (height - 1));  //�����height�}�X���ɂ���
	m_pVertexArray[1].pos.x += size.x;             //�E����2�}�X���ɂ���
	m_pVertexArray[3].pos.x += size.x;             //�E���2�}�X���ɂ���(x)
	m_pVertexArray[3].pos.y += (size.y * (height - 1));  //�E���height�}�X���ɂ���(y)

	m_xPos += (size.x / 2);
	m_yPos += ((size.y * (height - 1)) / 2);

	size.x = size.x * 2;
	size.y = size.y * height;

	m_DiagonalLength = OriginalMath::Math::CosineTheorem90(m_pVertexArray[0].pos.x - m_pVertexArray[1].pos.x, m_pVertexArray[0].pos.y - m_pVertexArray[1].pos.y);
}