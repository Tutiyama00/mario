#include"Image.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="size">サイズ</param>
/// <param name="pDevice">使用するデバイス</param>
/// <param name="pTextureFileName">テクスチャファイルのパス</param>
Image::Image(Vector3 pos, Vector2 size, ID3D11Device* pDevice, const wchar_t* pTextureFileName) : Square(pos,size)
{
	LoadTexture(pDevice, pTextureFileName);
	CreateShader(pDevice, L"Shader/TextVertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/// <summary>
/// デストラクタ
/// </summary>
Image::~Image() {}

/// <summary>
/// 抽象化するために純粋仮想関数だったもの
/// </summary>
void Image::Abstract() {}

/// <summary>
/// このオブジェクトの描画
/// </summary>
/// <param name="pDeviceContext">デバイスコンテキスト</param>
/// <param name="strides"></param>
/// <param name="offsets"></param>
void Image::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// このオブジェクトのバッファの生成
/// </summary>
/// <param name="pDevice">デバイス</param>
void Image::ThisObjCreateBuffer(ID3D11Device* pDevice)
{
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}
