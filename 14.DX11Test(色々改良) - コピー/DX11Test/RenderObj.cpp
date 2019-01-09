#include"RenderObj.h"
#include<d3dcompiler.h>
#include"WICTextureLoader.h"
//#include "WICTextureLoader.cpp"
#include"Vertex.h"
#include"Math.h"
#include"Dx11.h"

D3D11_INPUT_ELEMENT_DESC TextureVertexDesc[]
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXTURE" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR"   , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};


/*#####################################             #####################################*/
/*#####################################  PROTECTED  #####################################*/
/*#####################################             #####################################*/

/// <summary>
/// �f�X�g���N�^
/// </summary>
RenderObj::~RenderObj()
{
	if (m_pVertexBuffer        != nullptr) { m_pVertexBuffer        ->Release();  m_pVertexBuffer        = nullptr; }
	if (m_pIndexBuffer         != nullptr) { m_pIndexBuffer         ->Release();  m_pIndexBuffer         = nullptr; }

	if (m_pTextureVertexShader != nullptr) { m_pTextureVertexShader ->Release();  m_pTextureVertexShader = nullptr; }
	if (m_pTexturePixelShader  != nullptr) { m_pTexturePixelShader  ->Release();  m_pTexturePixelShader  = nullptr; }
	if (m_pTextureInputLayout  != nullptr) { m_pTextureInputLayout  ->Release();  m_pTextureInputLayout  = nullptr; }
}

/// <summary>
/// �V�F�[�_�[�̐���
/// </summary>
/// <param name="pVSFileName">�o�[�e�b�N�X�V�F�[�_�[�t�@�C���̃p�X</param>
/// <param name="pPSFileName">�s�N�Z���V�F�[�_�[�t�@�C���̃p�X</param>
void RenderObj::CreateShader(LPCWSTR pVSFileName, LPCWSTR pPSFileName)
{
	HRESULT hr = TRUE;

	//���_�V�F�[�_�[�̃R���p�C��
	ID3DBlob* vs_pBlob = nullptr;
	hr = D3DCompileFromFile(pVSFileName, 0, 0, "vs_main", "vs_5_0", 0, 0, &vs_pBlob, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : D3DCompileFromFile()vertexShader Failed.", "ERRER", MB_OK);
	}

	//�s�N�Z���V�F�[�_�[�̃R���p�C��
	ID3DBlob* ps_pBlob = nullptr;
	hr = D3DCompileFromFile(pPSFileName, 0, 0, "ps_main", "ps_5_0", 0, 0, &ps_pBlob, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : D3DCompileFromFile()pixelShader Failed.", "ERRER", MB_OK);
	}

	//���_���C�A�E�g�쐬
	hr = Dx11::Instance()->m_pDevice->CreateInputLayout(TextureVertexDesc, ARRAYSIZE(TextureVertexDesc), vs_pBlob->GetBufferPointer(), vs_pBlob->GetBufferSize(), &m_pTextureInputLayout);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateInputLayout() Failed.", "ERRER", MB_OK);
	}

	//���_�V�F�[�_�[����
	hr = Dx11::Instance()->m_pDevice->CreateVertexShader(vs_pBlob->GetBufferPointer(), vs_pBlob->GetBufferSize(), NULL, &m_pTextureVertexShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateVertexShader() Failed.", "ERRER", MB_OK);
	}

	//�s�N�Z���V�F�[�_�[����
	hr = Dx11::Instance()->m_pDevice->CreatePixelShader(ps_pBlob->GetBufferPointer(), ps_pBlob->GetBufferSize(), NULL, &m_pTexturePixelShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreatePixelShader() Failed.", "ERRER", MB_OK);
	}

	//�������
	vs_pBlob->Release();
	vs_pBlob = nullptr;
	ps_pBlob->Release();
	ps_pBlob = nullptr;
}

/// <summary>
/// �o�b�t�@�̐���
/// </summary>
/// <param name="pVertexArray">���_���z��̃|�C���^</param>
/// <param name="vertexArraySize">���_���z��̗v�f��</param>
/// <param name="pIndexArray">���_�C���f�b�N�X���z��̃|�C���^</param>
/// <param name="indexArraySize">���_�C���f�b�N�X���z��̗v�f��</param>
void RenderObj::CreateBuffer(vertex* pVertexArray,UINT vertexArraySize,WORD* pIndexArray,UINT indexArraySize)
{
	HRESULT hr = S_OK;

	//�o�b�t�@�̐ݒ�
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

	//�o�b�t�@�̍쐬
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
/// �`��
/// </summary>
/// <param name="pVertexArray">���_���z��̃|�C���^</param>
/// <param name="indexArraySize">���_�C���f�b�N�X���z��̗v�f��</param>
void RenderObj::Render(vertex* pVertexArray, UINT indexArraySize)
{
	if (!m_RenderFlag) { return; }

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