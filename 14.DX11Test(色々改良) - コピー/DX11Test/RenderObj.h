#pragma once

#include<d3d11.h>

//�O���錾
struct vertex;


//�`�悷��I�u�W�F�N�g�Ɍp��������
class RenderObj
{
public:
	virtual ~RenderObj();
	virtual void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets) = 0;
	virtual void ThisObjCreateBuffer(ID3D11Device* pDevice) = 0;

protected:
	virtual void Abstract() = 0;  //�������z�֐��i����ɂ���Ă��̃N���X�̓C���X�^���X�ł��Ȃ�)
	virtual void LoadTexture(ID3D11Device* pDevice, const wchar_t* pFileName);
	virtual void CreateShader(ID3D11Device* pDevice, LPCWSTR pVSFileName, LPCWSTR pPSFileName);
	virtual void Render(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets, vertex* pVertexArray, UINT indexArraySize);
	virtual void CreateBuffer(ID3D11Device* pDevice, vertex* pVertexArray, UINT vertexArraySize, WORD* pIndexArray, UINT indexArraySize);

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