#include"DeathChecker.h"

DeathChecker::DeathChecker(float xPos, float yPos, float zPos, float xSize, float ySize,ID3D11Device* pDevice) : Square(xPos, yPos, zPos, xSize, ySize)
{
	LoadTexture (pDevice, L"Texture/MARIO_GAMEOVER.png");
	CreateShader(pDevice, L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

DeathChecker::~DeathChecker() {}

bool DeathChecker::DeathCheck(Polygon* pPolygon)
{
	return CollisionCheck(pPolygon);
}

void DeathChecker::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
}

void DeathChecker::ThisObjCreateBuffer(ID3D11Device* pDevice)
{
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}