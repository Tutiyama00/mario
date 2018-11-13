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
	//�����R�[�h�ɕϊ�
	int charNamber = setChar;

	//�\���\����������
	if (charNamber < m_MinFontNamber || charNamber > m_MaxFontNamber)
	{
		MessageBox(NULL, "�����R�[�h���\���\�����ł͂���܂���B", "ERRER", MB_OK);
		charNamber = m_MinFontNamber;
	}

	//1�����̍����ƕ������߂�
	float charHeight = 1.0f / m_FontHeight;
	float charWidth  = 1.0f / m_FontWidth;

	//�����R�[�h��Ή������R�[�h��ɂ���
	charNamber -= m_MinFontNamber;

	//tex���W�̐ݒ�
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