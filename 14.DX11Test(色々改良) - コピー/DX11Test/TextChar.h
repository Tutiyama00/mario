#pragma once

#include"Vertex.h"
#include"RenderObj.h"

#define TC_BLACK L"Shader/TextPixelShader_Black.psh"
#define TC_WHITE L"Shader/TextPixelShader_White.psh"

class TextChar : public Square,public RenderObj
{
public:
	TextChar(float xPos, float yPos, float zPos, float xSize, float ySize, ID3D11Device* pDevice, float texLeftUp[2], float texRightDown[2], LPCWSTR TC_COLOR, char setChar);
	~TextChar();

	void CherTexSet(char setChar);

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

private:
	//---RenderObj---
	void Abstract();

private:
	ID3D11Buffer*   m_pTextureConstantBuffer = nullptr;
	const UINT m_FontHeight = 10;
	const UINT m_FontWidth  = 10;
	const UINT m_MinFontNamber = 32;
	const UINT m_MaxFontNamber = 125;
};
