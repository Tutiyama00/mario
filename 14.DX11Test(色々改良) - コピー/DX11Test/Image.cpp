#include"Image.h"

Image::Image(Vector3 pos, Vector2 size, ID3D11Device* pDevice, const wchar_t* pTextureFileName) : Square(pos,size)
{
	LoadTexture(pDevice, pTextureFileName);
	CreateShader(pDevice, L"Shader/TextVertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

Image::~Image() {}

void Image::Abstract() {}

void Image::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
}

void Image::ThisObjCreateBuffer(ID3D11Device* pDevice)
{
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}
