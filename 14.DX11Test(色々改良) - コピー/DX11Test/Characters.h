#pragma once

#include"RenderObj.h"
#include<vector>
#include"Dx11.h"
#include"TextureData.h"

template<class T> class Characters : public RenderObj
{
public:
	Characters(ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV, LPCWSTR pVSFileName, LPCWSTR pPSFileName)
	{
		CreateShader(pVSFileName, pPSFileName);

		m_pMainTextureResource = pTR;
		m_pMainTextureSRV      = pTSRV;
	}

	~Characters()
	{
		for (int i = 0; i < m_ObjectVector.size(); i++)
		{
			if (m_ObjectVector[i] != nullptr) { delete m_ObjectVector[i]; m_ObjectVector[i] = nullptr; }
		}

		if (m_pVertexArray != nullptr) { delete[] m_pVertexArray; m_pVertexArray = nullptr; }
		if (m_pIndexArray  != nullptr) { delete[] m_pIndexArray;  m_pIndexArray  = nullptr; }
	}

	void UpdateVIBuffer()
	{
		HRESULT hr = S_OK;

		//頂点とインデックス情報を更新
		SetVertexIndex();

		//サイズの再設定
		m_VertexBufferDesc.ByteWidth = sizeof(vertex) * m_VertexArraySize;
		m_IndexBufferDesc.ByteWidth = sizeof(WORD)   * m_IndexArraySize;

		//配列の再設定
		m_VertexSubResourData.pSysMem = m_pVertexArray;
		m_IndexSubResourData.pSysMem = m_pIndexArray;

		//前のバッファをリリース
		if (m_pVertexBuffer != nullptr) { m_pVertexBuffer->Release(); m_pVertexBuffer = nullptr; }
		if (m_pIndexBuffer  != nullptr) { m_pIndexBuffer ->Release(); m_pIndexBuffer  = nullptr; }

		//新しくバッファを作成
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

public:
	std::vector<T*> m_ObjectVector;

private:
	void SetVertexIndex()
	{
		//このクラスの配列数を確定
		int size       = m_ObjectVector.size();
		int vertexSize = m_ObjectVector[0]->GetVertexArraySize();

		if (m_pVertexArray != nullptr) { delete[] m_pVertexArray; m_pVertexArray = nullptr; }
		if (m_pIndexArray  != nullptr) { delete[] m_pIndexArray;  m_pIndexArray  = nullptr; }
		m_VertexArraySize = 0;
		m_IndexArraySize  = 0;

		m_pVertexArray = new vertex[vertexSize * size]();
		m_pIndexArray  = new WORD[(vertexSize * size - 3) * 3 + 3]();

		//すべてのオブジェクトの頂点、インデックス情報の格納
		for (int i = 0; i < m_ObjectVector.size(); i++)
		{
			//Index
			for (int j = 0; j < m_ObjectVector[i]->GetIndexArraySize(); j++)
			{
				//今格納されている頂点情報数によってインデックスの番号が変動するので単純な計算をしている
				m_pIndexArray[m_IndexArraySize] = m_ObjectVector[i]->m_pIndexArray[j] + m_VertexArraySize;
				m_IndexArraySize++;
			}
			//Vertex
			for (int j = 0; j < m_ObjectVector[i]->GetVertexArraySize(); j++)
			{
				m_pVertexArray[m_VertexArraySize] = m_ObjectVector[i]->m_pVertexArray[j];
				m_VertexArraySize++;
			}
		}
	}

private:
	vertex*                   m_pVertexArray    = nullptr;
	UINT                      m_VertexArraySize = 0;
	WORD*                     m_pIndexArray     = nullptr;
	UINT                      m_IndexArraySize  = 0;


/*------RenderObj------*/
public:
	void ThisObjRender()
	{
		Render(m_pVertexArray, m_IndexArraySize);
	}

	void ThisObjCreateBuffer()
	{
		SetVertexIndex();
		CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
	}

private:
	void Abstract() {};
};