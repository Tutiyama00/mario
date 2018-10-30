#pragma once

#include"Vertex.h"
#include"RenderObj.h"

#define TC_BLACK L"Shader/TextPixelShader_Black.psh"
#define TC_WHITE L"Shader/TextPixelShader_White.psh"

class TextChar : public Square,public RenderObj
{
public:
	TextChar(float xPos, float yPos, float zPos, float xSize, float ySize, ID3D11Device* pDevice, float texLeftUp[2], float texRightDown[2], LPCWSTR TC_COLOR);
	~TextChar();

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

public:
	float m_Color[4];

private:
	//---RenderObj---
	void Abstract();

private:
	ID3D11Buffer*   m_pTextureConstantBuffer = nullptr;
};
