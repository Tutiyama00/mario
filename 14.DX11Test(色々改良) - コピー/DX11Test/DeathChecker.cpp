#include"DeathChecker.h"

DeathChecker::DeathChecker(Vector3 pos, Vector2 size,ID3D11Device* pDevice) : Square(pos, size)
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