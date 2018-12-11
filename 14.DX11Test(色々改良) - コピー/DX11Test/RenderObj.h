#pragma once

#include<d3d11.h>

//前方宣言
struct vertex;


//描画するオブジェクトに継承させる
class RenderObj
{
public:
	virtual ~RenderObj();
	virtual void ThisObjRender() = 0;
	virtual void ThisObjCreateBuffer() = 0;

protected:
	virtual void Abstract() = 0;  //純粋仮想関数（これによってこのクラスはインスタンスできない)
	virtual void CreateShader(LPCWSTR pVSFileName, LPCWSTR pPSFileName);
	virtual void Render(vertex* pVertexArray, UINT indexArraySize);
	virtual void CreateBuffer(vertex* pVertexArray, UINT vertexArraySize, WORD* pIndexArray, UINT indexArraySize);

protected:
	ID3D11Buffer*             m_pVertexBuffer        = nullptr;
	ID3D11Buffer*             m_pIndexBuffer         = nullptr;
	D3D11_BUFFER_DESC         m_VertexBufferDesc;
	D3D11_BUFFER_DESC         m_IndexBufferDesc;
	D3D11_SUBRESOURCE_DATA    m_VertexSubResourData;
	D3D11_SUBRESOURCE_DATA    m_IndexSubResourData;
	ID3D11VertexShader*       m_pTextureVertexShader = nullptr;
	ID3D11PixelShader*        m_pTexturePixelShader  = nullptr;
	ID3D11InputLayout*        m_pTextureInputLayout  = nullptr;
	ID3D11Resource*           m_pMainTextureResource = nullptr;
	ID3D11ShaderResourceView* m_pMainTextureSRV      = nullptr;
};