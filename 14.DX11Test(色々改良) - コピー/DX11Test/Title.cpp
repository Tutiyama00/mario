#include"Title.h"

Title::Title(Vector3 pos, Vector2 size) : Square::Square(pos, size)
{
	LoadTexture(L"Texture/MARIO_TITLE_LOGO.png");
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

Title::~Title() {}

void Title::Abstract() {}

void Title::ThisObjRender()
{
	Render(m_pVertexArray, m_IndexArraySize);
}

void Title::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}