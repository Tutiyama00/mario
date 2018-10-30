#include"TextChar.h"

TextChar::TextChar(float xPos, float yPos, float zPos, float xSize, float ySize, ID3D11Device* pDevice, float texLeftUp[2], float texRightDown[2], LPCWSTR TC_COLOR)
	     :Square(xPos, yPos, zPos, xSize, ySize)
{
	LoadTexture(pDevice, L"Texture/DOT_FONT.png");
	CreateShader(pDevice, L"Shader/TextVertexShader.vsh",TC_COLOR);
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	HRESULT hr = S_OK;
}

TextChar::~TextChar() {}

void TextChar::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
}

void TextChar::ThisObjCreateBuffer(ID3D11Device* pDevice)
{
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

void TextChar::Abstract() {}