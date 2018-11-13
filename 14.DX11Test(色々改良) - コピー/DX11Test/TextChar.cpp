#include"TextChar.h"

TextChar::TextChar(Vector3 pos, Vector2 size, LPCWSTR TPS_COLOR,char setChar)
	     :Square(pos, size)
{
	LoadTexture(L"Texture/DOT_FONT.png");
	CherTexSet(setChar);
	CreateShader(L"Shader/TextVertexShader.vsh",TPS_COLOR);
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	HRESULT hr = S_OK;
}

TextChar::~TextChar() {}

void TextChar::ThisObjRender()
{
	Render(m_pVertexArray, m_IndexArraySize);
}

void TextChar::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

void TextChar::CherTexSet(char setChar)
{
	//文字コードに変換
	int charNamber = setChar;

	//表示可能文字か判別
	if (charNamber < m_MinFontNamber || charNamber > m_MaxFontNamber)
	{
		MessageBox(NULL, "文字コードが表示可能文字ではありません。", "ERRER", MB_OK);
		charNamber = m_MinFontNamber;
	}

	//1文字の高さと幅を求める
	float charHeight = 1.0f / m_FontHeight;
	float charWidth  = 1.0f / m_FontWidth;

	//文字コードを対応文字コード基準にする
	charNamber -= m_MinFontNamber;

	//tex座標の設定
	m_pVertexArray[0].tex[0] = (charNamber % m_FontWidth) * charWidth;
	m_pVertexArray[0].tex[1] = (charNamber / m_FontWidth) * charHeight;
	m_pVertexArray[1].tex[0] = m_pVertexArray[0].tex[0] + charWidth;
	m_pVertexArray[1].tex[1] = m_pVertexArray[0].tex[1] + charHeight;
	m_pVertexArray[2].tex[0] = m_pVertexArray[0].tex[0];
	m_pVertexArray[2].tex[1] = m_pVertexArray[1].tex[1];
	m_pVertexArray[3].tex[0] = m_pVertexArray[1].tex[0];
	m_pVertexArray[3].tex[1] = m_pVertexArray[0].tex[1];
}

void TextChar::Abstract() {}