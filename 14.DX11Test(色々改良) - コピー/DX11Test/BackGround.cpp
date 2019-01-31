#include"BackGround.h"
#include"Image.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">一枚目の背景のポジション</param>
/// <param name="size">一枚目の背景のサイズ</param>
/// <param name="pTR">一枚目の背景のTR</param>
/// <param name="pTSRV">一枚目の背景のTSRV</param>
BackGround::BackGround(Vector3 pos, Vector2 size, ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV)
{
	/*一枚目を追加*/
	m_BackGroundVector.push_back(new Image(pos, size, pTR, pTSRV, false));
}

/// <summary>
/// デストラクタ
/// </summary>
BackGround::~BackGround()
{
	for (int i = 0; i < m_BackGroundVector.size(); i++)
	{
		if (m_BackGroundVector[i] != nullptr) { delete m_BackGroundVector[i]; m_BackGroundVector[i] = nullptr; }
	}
	m_BackGroundVector.clear();
}

/// <summary>
/// 背景のポジション変えを行ってよいかのチェック
/// </summary>
/// <param name="lookMinXPos">可視可能範囲の左限界値</param>
void BackGround::NextCheck(float lookMinXPos)
{
	/*先頭背景が左限界値より左側にあるか←つまり画面に映っていないか*/
	if (m_BackGroundVector[m_HeadBackGroundNamber]->m_pVertexArray[1].pos.x < lookMinXPos)
	{
		LoopBackGround();
	}
}

/// <summary>
/// 背景の追加
/// </summary>
/// <param name="pTR">テクスチャリソース</param>
/// <param name="pTSRV">テクスチャシェーダリソースビュー</param>
void BackGround::AddBackGround(ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV)
{
	Vector3 pos = { m_BackGroundVector[m_BackGroundVector.size() - 1]->GetxPos() + m_BackGroundVector[m_BackGroundVector.size() - 1]->GetxSize(),
					m_BackGroundVector[m_BackGroundVector.size() - 1]->GetyPos() ,
					m_BackGroundVector[m_BackGroundVector.size() - 1]->GetzPos() };
	Vector2 size = { m_BackGroundVector[m_BackGroundVector.size() - 1]->GetxSize(),
					 m_BackGroundVector[m_BackGroundVector.size() - 1]->GetySize() };

	m_BackGroundVector.push_back(new Image(pos, size, pTR, pTSRV, false));
}

/// <summary>
/// 背景イメージをループさせる
/// </summary>
void BackGround::LoopBackGround()
{
	/*次の先頭配列番号*/
      	unsigned int nextHeadBackGroundNamber = m_HeadBackGroundNamber + 1;

	/*次の先頭配列番号が配列数を超えているかどうか*/
	if (nextHeadBackGroundNamber == m_BackGroundVector.size())
	{
		/*配列番号を０に戻す*/
		nextHeadBackGroundNamber = 0;
	}

	/*先頭背景を最後尾位置に移動させる*/
	m_BackGroundVector[m_HeadBackGroundNamber]->VertexMove(m_BackGroundVector[nextHeadBackGroundNamber]->GetxSize() * m_BackGroundVector.size(), 0.0f);

	/*先頭配列番号の更新*/
	m_HeadBackGroundNamber = nextHeadBackGroundNamber;
}

void BackGround::ThisObjCreateBuffer()
{
	for (int i = 0; i < m_BackGroundVector.size(); i++)
	{
		m_BackGroundVector[i]->ThisObjCreateBuffer();
	}
}

void BackGround::ThisObjRender()
{
	for (int i = 0; i < m_BackGroundVector.size(); i++)
	{
		m_BackGroundVector[i]->ThisObjRender();
	}
}