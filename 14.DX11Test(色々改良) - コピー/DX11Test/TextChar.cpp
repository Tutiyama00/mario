#include"TextChar.h"
#include"TextureData.h"

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="size">サイズ</param>
/// <param name="TPS_COLOR">文字の色（使用するピクセルシェーダのパス）</param>
/// <param name="setChar">表示する文字</param>
TextChar::TextChar(Vector3 pos, Vector2 size, LPCWSTR TPS_COLOR,char setChar)
	     :Square(pos, size)
{
	CherTexSet(setChar);
	CreateShader(L"Shader/TextVertexShader.vsh",TPS_COLOR);
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_pMainTextureResource = TextureData::Instance()->GetDOT_FONT_TR();
	m_pMainTextureSRV      = TextureData::Instance()->GetDOT_FONT_TSRV();
}

/// <summary>
/// このオブジェクトの文字をセット
/// </summary>
/// <param name="setChar"></param>
void TextChar::CherTexSet(char setChar)
{
	/* 文字コードに変換 */
	int charNamber = setChar;

	/* 表示可能文字か判別 */
	if (charNamber < m_MinFontNamber || charNamber > m_MaxFontNamber)
	{
		MessageBox(NULL, "文字コードが表示可能文字ではありません。", "ERRER", MB_OK);
		charNamber = m_MinFontNamber;
	}

	/* 1文字の高さと幅を求める */
	float charHeight = 1.0f / m_FontHeight;
	float charWidth  = 1.0f / m_FontWidth;

	/* 文字コードを対応文字コード基準にする */
	charNamber -= m_MinFontNamber;

	/* tex座標の設定 */
	m_pVertexArray[0].tex[0] = (charNamber % m_FontWidth) * charWidth;
	m_pVertexArray[0].tex[1] = (charNamber / m_FontWidth) * charHeight;
	m_pVertexArray[1].tex[0] = m_pVertexArray[0].tex[0] + charWidth;
	m_pVertexArray[1].tex[1] = m_pVertexArray[0].tex[1] + charHeight;
	m_pVertexArray[2].tex[0] = m_pVertexArray[0].tex[0];
	m_pVertexArray[2].tex[1] = m_pVertexArray[1].tex[1];
	m_pVertexArray[3].tex[0] = m_pVertexArray[1].tex[0];
	m_pVertexArray[3].tex[1] = m_pVertexArray[0].tex[1];
}

/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// このオブジェクトの描画
/// </summary>
void TextChar::ThisObjRender()
{
	Render(m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// このオブジェクトのバッファの生成
/// </summary>
void TextChar::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}