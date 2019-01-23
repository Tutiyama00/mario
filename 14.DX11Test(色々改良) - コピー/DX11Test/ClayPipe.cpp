#include"ClayPipe.h"

ClayPipe::ClayPipe(Vector3 pos, Vector2 size, unsigned int height) : Block(pos, size)
{
	m_pVertexArray[0].pos[1] += (size.y * (height - 1));  //左上をheightマス分にする
	m_pVertexArray[1].pos[0] += size.x;             //右下を2マス分にする
	m_pVertexArray[3].pos[0] += size.x;             //右上を2マス分にする(x)
	m_pVertexArray[3].pos[1] += (size.y * (height - 1));  //右上をheightマス分にする(y)

	m_xPos += (size.x / 2);
	m_yPos += ((size.y * (height - 1)) / 2);

	size.x = size.x * 2;
	size.y = size.y * height;

	m_DiagonalLength = OriginalMath::Math::CosineTheorem90(m_pVertexArray[0].pos[0] - m_pVertexArray[1].pos[0], m_pVertexArray[0].pos[1] - m_pVertexArray[1].pos[1]);
}