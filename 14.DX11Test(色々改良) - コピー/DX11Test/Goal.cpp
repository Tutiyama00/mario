#include"Goal.h"

/*コンストラクタ*/
Goal::Goal(Vector3 pos, Vector2 size) : Square(pos,size)
{
	LoadTexture(L"Texture/MARIO_GOAL.png");
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/*デストラクタ*/
Goal::~Goal() {};

/*描画*/
void Goal::ThisObjRender()
{
	Render(m_pVertexArray, m_IndexArraySize);
}

/*バッファの生成*/
void Goal::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

void Goal::Abstract() {};