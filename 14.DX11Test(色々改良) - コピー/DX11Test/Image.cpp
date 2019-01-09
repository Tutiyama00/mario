#include"Image.h"
#include<d3d11.h>

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="size">サイズ</param>
/// <param name="pDevice">使用するデバイス</param>
/// <param name="pTextureFileName">テクスチャファイルのパス</param>
Image::Image(Vector3 pos, Vector2 size, ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV) : Square(pos,size)
{
	CreateShader(L"Shader/TextVertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_pMainTextureResource = pTR;
	m_pMainTextureSRV = pTSRV;
}

/// <summary>
/// 移動
/// </summary>
/// <param name="amount">移動量</param>
void Image::Move(Vector3 amount)
{
	m_xPos += amount.x;
	m_yPos += amount.y;

	for (int i = 0; i < m_VertexArraySize; i++)
	{
		m_pVertexArray[i].pos[0] += amount.x;
		m_pVertexArray[i].pos[1] += amount.y;
		m_pVertexArray[i].pos[2] += amount.z;
	}
}

/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// このオブジェクトの描画
/// </summary>
void Image::ThisObjRender()
{
	Render(m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// このオブジェクトのバッファの生成
/// </summary>
void Image::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}