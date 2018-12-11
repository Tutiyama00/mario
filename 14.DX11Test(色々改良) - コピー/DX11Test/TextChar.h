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
	ID3D11Buffer*   m_pTextureConstantBuffer = nullptr;  //���̃I�u�W�F�N�g�̃o�b�t�@
	const UINT      m_FontHeight             = 10;       //1�������̍���
	const UINT      m_FontWidth              = 10;       //1�������̕�
	const UINT      m_MinFontNamber          = 32;       //�����R�[�h�ϊ��p�Ɏg�p����ŏ������ԍ�
	const UINT      m_MaxFontNamber          = 125;      //�����R�[�h�ϊ��p�Ɏg�p����ő啶���ԍ�


/*------RenderObj------*/
public:
	void ThisObjRender();
	void ThisObjCreateBuffer();

private:
	void Abstract() {};
};
