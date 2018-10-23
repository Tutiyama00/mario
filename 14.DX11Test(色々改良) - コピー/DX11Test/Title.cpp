#include"Title.h"

Title::Title(float xPos, float yPos, float zPos, float xSize, float ySize, ID3D11Device* pDevice) : Square::Square(xPos, yPos, zPos, xSize, ySize)
{
	LoadTexture(pDevice, L"MARIO_TITLE_LOGO.png");
	CreateShader(pDevice, L"VertexShader.vsh", L"PixelShader.psh");
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

Title::~Title() {}

void Title::Abstract() {}

void Title::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
}

void Title::ThisObjCreateBuffer(ID3D11Device* pDevice)
{
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}