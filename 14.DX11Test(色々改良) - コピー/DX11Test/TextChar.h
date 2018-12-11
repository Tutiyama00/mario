#pragma once

#include"Vertex.h"
#include"RenderObj.h"
#include"Math.h"

using namespace OriginalMath;

#define TPS_BLACK L"Shader/TextPixelShader_Black.psh"
#define TPS_WHITE L"Shader/TextPixelShader_White.psh"

class TextChar : public Square,public RenderObj
{
public:
	TextChar(Vector3 pos, Vector2 size, LPCWSTR TPS_COLOR, char setChar);
	~TextChar() {};

	void CherTexSet(char setChar);

private:
	ID3D11Buffer*   m_pTextureConstantBuffer = nullptr;  //このオブジェクトのバッファ
	const UINT      m_FontHeight             = 10;       //1文字分の高さ
	const UINT      m_FontWidth              = 10;       //1文字分の幅
	const UINT      m_MinFontNamber          = 32;       //文字コード変換用に使用する最小文字番号
	const UINT      m_MaxFontNamber          = 125;      //文字コード変換用に使用する最大文字番号


/*------RenderObj------*/
public:
	void ThisObjRender();
	void ThisObjCreateBuffer();

private:
	void Abstract() {};
};
