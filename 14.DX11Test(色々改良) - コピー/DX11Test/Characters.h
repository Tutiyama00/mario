#pragma once

#include"RenderObj.h"
#include<vector>

template<class T> class Characters : public RenderObj
{
public:
	Characters(ID3D11Device* pDevice, const wchar_t* pTextureFileName, LPCWSTR pVSFileName, LPCWSTR pPSFileName)
	{
		LoadTexture(pDevice, pTextureFileName);
		CreateShader(pDevice, pVSFileName, pPSFileName);
	}

	~Characters()
	{
		for (int i = 0; i < m_ObjectVector.size(); i++)
		{
			if (m_ObjectVector[i] != nullptr) { delete m_ObjectVector[i]; m_ObjectVector[i] = nullptr; }
		}

		if (m_pVertexArray != nullptr) { delete[] m_pVertexArray; m_pVertexArray = nullptr; }
		if (m_pIndexArray != nullptr) { delete[] m_pIndexArray;  m_pIndexArray = nullptr; }
	}

	void UpdateVIBuffer(ID3D11Device* pDevice)
	{
		HRESULT hr = S_OK;

		//���_�ƃC���f�b�N�X�����X�V
		SetVertexIndex();

		//�T�C�Y�̍Đݒ�
		m_VertexBufferDesc.ByteWidth = sizeof(vertex) * m_VertexArraySize;
		m_IndexBufferDesc.ByteWidth = sizeof(WORD)   * m_IndexArraySize;

		//�z��̍Đݒ�
		m_VertexSubResourData.pSysMem = m_pVertexArray;
		m_IndexSubResourData.pSysMem = m_pIndexArray;

		//�O�̃o�b�t�@�������[�X
		if (m_pVertexBuffer != nullptr) { m_pVertexBuffer->Release(); m_pVertexBuffer = nullptr; }
		if (m_pIndexBuffer != nullptr) { m_pIndexBuffer->Release(); m_pIndexBuffer = nullptr; }

		//�V�����o�b�t�@���쐬
		hr = pDevice->CreateBuffer(&m_VertexBufferDesc, &m_VertexSubResourData, &m_pVertexBuffer);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Error : CreateBuffer()m_pVertexBuffer Failed.", "ERRER", MB_OK);
		}
		hr = pDevice->CreateBuffer(&m_IndexBufferDesc, &m_IndexSubResourData, &m_pIndexBuffer);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Error : CreateBuffer()m_pIndexBuffer Failed.", "ERRER", MB_OK);
		}
	}

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
	{
		Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
	}

	void ThisObjCreateBuffer(ID3D11Device* pDevice)
	{
		SetVertexIndex();
		CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
	}

public:
	std::vector<T*> m_ObjectVector;

private:
	void SetVertexIndex()
	{
		//���̃N���X�̔z�񐔂��m��
		int size = m_ObjectVector.size();
		int vertexSize = m_ObjectVector[0]->GetVertexArraySize();

		if (m_pVertexArray != nullptr) { delete[] m_pVertexArray; m_pVertexArray = nullptr; }
		if (m_pIndexArray != nullptr) { delete[] m_pIndexArray;  m_pIndexArray = nullptr; }
		m_VertexArraySize = 0;
		m_IndexArraySize = 0;

		m_pVertexArray = new vertex[vertexSize * size]();
		m_pIndexArray = new WORD[(vertexSize * size - 3) * 3 + 3]();

		//���ׂẴI�u�W�F�N�g�̒��_�A�C���f�b�N�X���̊i�[
		for (int i = 0; i < m_ObjectVector.size(); i++)
		{
			//Index
			for (int j = 0; j < m_ObjectVector[i]->GetIndexArraySize(); j++)
			{
				//���i�[����Ă��钸�_��񐔂ɂ���ăC���f�b�N�X�̔ԍ����ϓ�����̂ŒP���Ȍv�Z�����Ă���
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

	//---RenderObj---
	void Abstract() {};

private:
	vertex*                   m_pVertexArray    = nullptr;
	UINT                      m_VertexArraySize = 0;
	WORD*                     m_pIndexArray     = nullptr;
	UINT                      m_IndexArraySize  = 0;
};