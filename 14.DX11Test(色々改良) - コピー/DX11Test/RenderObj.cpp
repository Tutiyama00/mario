#include"RenderObj.h"
#include<d3dcompiler.h>
#include"WICTextureLoader.h"
#include "WICTextureLoader.cpp"
#include"Vertex.h"
#include"Math.h"
#include"Dx11.h"

D3D11_INPUT_ELEMENT_DESC TextureVertexDesc[]
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXTURE" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR"   , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

/// <summary>
/// デストラクタ
/// </summary>
RenderObj::~RenderObj()
{
	if (m_pVertexBuffer        != nullptr) { m_pVertexBuffer        ->Release();  m_pVertexBuffer        = nullptr; }
	if (m_pIndexBuffer         != nullptr) { m_pIndexBuffer         ->Release();  m_pIndexBuffer         = nullptr; }

	if (m_pTextureVertexShader != nullptr) { m_pTextureVertexShader ->Release();  m_pTextureVertexShader = nullptr; }
	if (m_pTexturePixelShader  != nullptr) { m_pTexturePixelShader  ->Release();  m_pTexturePixelShader  = nullptr; }
	if (m_pTextureInputLayout  != nullptr) { m_pTextureInputLayout  ->Release();  m_pTextureInputLayout  = nullptr; }

	if (m_pMainTextureResource != nullptr) { m_pMainTextureResource ->Release();  m_pMainTextureResource = nullptr; }
	if (m_pMainTextureSRV      != nullptr) { m_pMainTextureSRV      ->Release();  m_pMainTextureSRV      = nullptr; }
}

/// <summary>
/// テクスチャの読み込み
/// </summary>
/// <param name="pFileName">テクスチャファイルのパス</param>
void RenderObj::LoadTexture(const wchar_t* pFileName)
{
	HRESULT hr = S_OK;

	//テクスチャの読み込み
	CoInitialize(NULL);   //COMライブラリの初期化が必要(絶対ここでしばらく詰んだ)

	//テクスチャの読み込み
	hr = CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, pFileName, &m_pMainTextureResource, &m_pMainTextureSRV);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateWICTextureFromFile() Failed.", "ERRER", MB_OK);
	}

	//CoInitializeしたので呼ぶ
	CoUninitialize();
}

/// <summary>
/// シェーダーの生成
/// </summary>
/// <param name="pVSFileName">バーテックスシェーダーファイルのパス</param>
/// <param name="pPSFileName">ピクセルシェーダーファイルのパス</param>
void RenderObj::CreateShader(LPCWSTR pVSFileName, LPCWSTR pPSFileName)
{
	HRESULT hr = TRUE;

	//頂点シェーダーのコンパイル
	ID3DBlob* vs_pBlob = nullptr;
	hr = D3DCompileFromFile(pVSFileName, 0, 0, "vs_main", "vs_5_0", 0, 0, &vs_pBlob, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : D3DCompileFromFile()vertexShader Failed.", "ERRER", MB_OK);
	}

	//ピクセルシェーダーのコンパイル
	ID3DBlob* ps_pBlob = nullptr;
	hr = D3DCompileFromFile(pPSFileName, 0, 0, "ps_main", "ps_5_0", 0, 0, &ps_pBlob, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : D3DCompileFromFile()pixelShader Failed.", "ERRER", MB_OK);
	}

	//頂点レイアウト作成
	hr = Dx11::Instance()->m_pDevice->CreateInputLayout(TextureVertexDesc, ARRAYSIZE(TextureVertexDesc), vs_pBlob->GetBufferPointer(), vs_pBlob->GetBufferSize(), &m_pTextureInputLayout);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateInputLayout() Failed.", "ERRER", MB_OK);
	}

	//頂点シェーダー生成
	hr = Dx11::Instance()->m_pDevice->CreateVertexShader(vs_pBlob->GetBufferPointer(), vs_pBlob->GetBufferSize(), NULL, &m_pTextureVertexShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateVertexShader() Failed.", "ERRER", MB_OK);
	}

	//ピクセルシェーダー生成
	hr = Dx11::Instance()->m_pDevice->CreatePixelShader(ps_pBlob->GetBufferPointer(), ps_pBlob->GetBufferSize(), NULL, &m_pTexturePixelShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreatePixelShader() Failed.", "ERRER", MB_OK);
	}

	//解放処理
	vs_pBlob->Release();
	vs_pBlob = nullptr;
	ps_pBlob->Release();
	ps_pBlob = nullptr;
}

/// <summary>
/// バッファの生成
/// </summary>
/// <param name="pVertexArray">頂点情報配列のポインタ</param>
/// <param name="vertexArraySize">頂点情報配列の要素数</param>
/// <param name="pIndexArray">頂点インデックス情報配列のポインタ</param>
/// <param name="indexArraySize">頂点インデックス情報配列の要素数</param>
void RenderObj::CreateBuffer(vertex* pVertexArray,UINT vertexArraySize,WORD* pIndexArray,UINT indexArraySize)
{
	HRESULT hr = S_OK;

	//バッファの設定
	ZeroMemory(&m_VertexBufferDesc, sizeof(m_VertexBufferDesc));
	m_VertexBufferDesc.ByteWidth           = sizeof(vertex) * vertexArraySize;
	m_VertexBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
	m_VertexBufferDesc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
	m_VertexBufferDesc.CPUAccessFlags      = 0;
	m_VertexBufferDesc.MiscFlags           = 0;
	m_VertexBufferDesc.StructureByteStride = 0;

	m_VertexSubResourData.pSysMem          = pVertexArray;
	m_VertexSubResourData.SysMemPitch      = 0;
	m_VertexSubResourData.SysMemSlicePitch = 0;

	ZeroMemory(&m_IndexBufferDesc, sizeof(m_IndexBufferDesc));
	m_IndexBufferDesc.ByteWidth            = sizeof(WORD) * indexArraySize;
	m_IndexBufferDesc.Usage                = D3D11_USAGE_DEFAULT;
	m_IndexBufferDesc.BindFlags            = D3D11_BIND_INDEX_BUFFER;
	m_IndexBufferDesc.CPUAccessFlags       = 0;
	m_IndexBufferDesc.MiscFlags            = 0;
	m_IndexBufferDesc.StructureByteStride  = 0;

	m_IndexSubResourData.pSysMem           = pIndexArray;
	m_IndexSubResourData.SysMemPitch       = 0;
	m_IndexSubResourData.SysMemSlicePitch  = 0;

	//バッファの作成
	hr = Dx11::Instance()->m_pDevice->CreateBuffer(&m_VertexBufferDesc, &m_VertexSubResourData, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateBuffer()m_pVertexBuffer Failed.", "ERRER", MB_OK);
	}
	hr = Dx11::Instance()->m_pDevice->CreateBuffer(&m_IndexBufferDesc, &m_IndexSubResourData, &m_pIndexBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateBuffer()m_pIndexBuffer Failed.", "ERRER", MB_OK);
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="pVertexArray">頂点情報配列のポインタ</param>
/// <param name="indexArraySize">頂点インデックス情報配列の要素数</param>
void RenderObj::Render(vertex* pVertexArray, UINT indexArraySize)
{
	UINT strides = Dx11::Instance()->GetStrides();
	UINT offsets = Dx11::Instance()->GetOffsets();

	Dx11::Instance()->m_pDeviceContext->UpdateSubresource(m_pVertexBuffer, 0, nullptr, pVertexArray, 0, 0);

	Dx11::Instance()->m_pDeviceContext->IASetInputLayout(m_pTextureInputLayout);
	Dx11::Instance()->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	Dx11::Instance()->m_pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, offsets);
	Dx11::Instance()->m_pDeviceContext->VSSetShader(m_pTextureVertexShader, NULL, 0);
	Dx11::Instance()->m_pDeviceContext->PSSetShader(m_pTexturePixelShader, NULL, 0);

	Dx11::Instance()->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pMainTextureSRV);

	Dx11::Instance()->m_pDeviceContext->DrawIndexed(indexArraySize, 0, 0);
}