#include"TextCharacters.h"
#include"Characters.h"
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
/// <param name="text">表示する文字列</param>
/// <param name="TPS_COLOR">文字の色（ピクセルシェーダのパス）</param>
TextCharacters::TextCharacters(Vector3 pos, Vector2 size,std::string text,  LPCWSTR TPS_COLOR) : M_POS(pos), M_SIZE(size), M_TPS_COLOR(TPS_COLOR)
{
	m_pCharacters = new Characters<TextChar>(TextureData::Instance()->GetDOT_FONT_TR(), TextureData::Instance()->GetDOT_FONT_TSRV(), L"Shader/TextVertexShader.vsh", TPS_COLOR);

	int textSize = text.size();
	for (int i = 0; i < textSize; i++)
	{
		m_pCharacters->m_ObjectVector.push_back(new TextChar(pos, size, TPS_COLOR, text[i]));
		pos.x += size.x;
	}

	m_pCharacters->ThisObjCreateBuffer();
}

/// <summary>
/// デストラクタ
/// </summary>
TextCharacters::~TextCharacters()
{
	if (m_pCharacters != nullptr) { delete m_pCharacters; m_pCharacters = nullptr; }
}

/// <summary>
/// 描画
/// </summary>
void TextCharacters::Render()
{
	m_pCharacters->ThisObjRender();
}

/// <summary>
/// 表示する文字の変更
/// </summary>
/// <param name="text">変更後の文字列</param>
void TextCharacters::ChangeText(std::string text)
{
	/* 各々のサイズの保存 */
	int objSize  = m_pCharacters->m_ObjectVector.size();
	int newTextSize = text.size();

	Vector3 setPos = M_POS;

	/* 元の文字と新しい文字はどちらが文字数多いか */
	if (newTextSize <= objSize)
	{
		/* 新しい文字の方が短かった場合 */

		/* 長い方基準でfor分を回す */
		for (int i = 0; i < objSize; i++)
		{
			/* 表示したい文字がまだあるかどうか */
			if (i >= newTextSize)
			{
				/* なかったら余分なオブジェクトをdeleteする */
				if (m_pCharacters->m_ObjectVector[i] != nullptr) 
				{
					delete m_pCharacters->m_ObjectVector[i];
					m_pCharacters->m_ObjectVector[i] = nullptr; 
				}
			}
			else
			{
				/* あったら文字を変える */
				m_pCharacters->m_ObjectVector[i]->CherTexSet(text[i]);
			}
		}

		/* 元文字の余分な分を配列から消去する */
		while (m_pCharacters->m_ObjectVector.back() == nullptr)
		{
			m_pCharacters->m_ObjectVector.pop_back();
		}
	}
	else
	{
		/* 新しい文字の方が長かった場合 */

		/* 長い方基準でfor分を回す */
		for (int i = 0; i < newTextSize ; i++)
		{
			/* objSizeの大きさを超えているかどうか */
			if (i >= objSize)
			{
				/* 
				 * 超えている場合
				 * オブジェクトを追加
				 */
				setPos.x = M_POS.x + M_SIZE.x * i;
				m_pCharacters->m_ObjectVector.push_back(new TextChar(setPos, M_SIZE, M_TPS_COLOR, text[i]));
			}
			else
			{
				/*
				 * 超えていない場合
				 * 元からあるオブジェクトの文字を変える
				 */
				m_pCharacters->m_ObjectVector[i]->CherTexSet(text[i]);
			}
		}
	}

	m_pCharacters->UpdateVIBuffer();
}