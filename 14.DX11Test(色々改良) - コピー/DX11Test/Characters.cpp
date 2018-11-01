#include"Characters.h"
#include"Block.h"
#include"TextChar.h"

template<class T> void Characters<T>::Abstract() {};

template<class T> Characters<T>::Characters(ID3D11Device* pDevice, const wchar_t* pTextureFileName, LPCWSTR pVSFileName, LPCWSTR pPSFileName)
{
	LoadTexture(pDevice, pTextureFileName);
	CreateShader(pDevice, pVSFileName, pPSFileName);
}

template<class T> Characters<T>::~Characters()
{
	for (int i = 0; i < m_ObjectVector.size(); i++)
	{
		if (m_ObjectVector[i] != nullptr) { delete m_ObjectVector[i]; m_ObjectVector[i] = nullptr; }
	}

	if (m_pVertexArray != nullptr) { delete[] m_pVertexArray; m_pVertexArray = nullptr; }
	if (m_pIndexArray  != nullptr) { delete[] m_pIndexArray;  m_pIndexArray  = nullptr; }
}

template<class T> void Characters<T>::SetVertexIndex()
{
	//���̃N���X�̔z�񐔂��m��
	int size       = m_ObjectVector.size();
	int vertexSize = m_ObjectVector[0]->GetVertexArraySize();
	m_pVertexArray = new vertex[vertexSize * size]();
	m_pIndexArray  = new WORD[(vertexSize * size - 3) * 3 + 3]();

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

//���_�z��̍X�V�A����ɔ�����VertexBuffer�̍X�V�i���̂܂܂ł̓C���f�b�N�X���̍X�V�͂��Ă��Ȃ��j
template<class T> void Characters<T>::UpdateVIBuffer(ID3D11DeviceContext* deviceContext)
{
	ClearVArray();

	//�v���C���[��Vertex���i�[
	for (int i = 0; i < m_ObjectVector.size(); i++)
	{
		//Vertex
		for (int j = 0; j < m_ObjectVector[i]->GetVertexArraySize(); j++)
		{
			m_pVertexArray[m_VertexArraySize] = m_ObjectVector[i]->m_pVertexArray[j];
			m_VertexArraySize++;
		}
	}

	deviceContext->UpdateSubresource(m_pVertexBuffer, 0, nullptr, m_pVertexArray, 0, 0);
}

template<class T> void Characters<T>::ClearVArray()
{
	//���_�z��̒��g���O�ŃN���A
	for (int i = 0; i < m_VertexArraySize; i++)
	{
		m_pVertexArray[i] = { {0.0f,0.0f,0.0f},{0.0f,0.0f} };
	}
	m_VertexArraySize = 0;
}

template<class T> void Characters<T>::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
}

template<class T> void Characters<T>::ThisObjCreateBuffer(ID3D11Device* pDevice)
{
	SetVertexIndex();
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

#pragma region OtherType

template void Characters<Block>::Abstract();
template Characters<Block>::Characters(ID3D11Device* pDevice, const wchar_t* pTextureFileName, LPCWSTR pVSFileName, LPCWSTR pPSFileName);
template Characters<Block>::~Characters();
template void Characters<Block>::SetVertexIndex();
template void Characters<Block>::UpdateVIBuffer(ID3D11DeviceContext* deviceContext);
template void Characters<Block>::ClearVArray();
template void Characters<Block>::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
template void Characters<Block>::ThisObjCreateBuffer(ID3D11Device* pDevice);

template void Characters<TextChar>::Abstract();
template Characters<TextChar>::Characters(ID3D11Device* pDevice, const wchar_t* pTextureFileName, LPCWSTR pVSFileName, LPCWSTR pPSFileName);
template Characters<TextChar>::~Characters();
template void Characters<TextChar>::SetVertexIndex();
template void Characters<TextChar>::UpdateVIBuffer(ID3D11DeviceContext* deviceContext);
template void Characters<TextChar>::ClearVArray();
template void Characters<TextChar>::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
template void Characters<TextChar>::ThisObjCreateBuffer(ID3D11Device* pDevice);

#pragma endregion