#include"Image.h"
#include<d3d11.h>

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="size">�T�C�Y</param>
/// <param name="pDevice">�g�p����f�o�C�X</param>
/// <param name="pTextureFileName">�e�N�X�`���t�@�C���̃p�X</param>
Image::Image(Vector3 pos, Vector2 size, ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV) : Square(pos,size)
{
	CreateShader(L"Shader/TextVertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);

	m_pMainTextureResource = pTR;
	m_pMainTextureSRV = pTSRV;
}

/// <summary>
/// �ړ�
/// </summary>
/// <param name="amount">�ړ���</param>
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
/// ���̃I�u�W�F�N�g�̕`��
/// </summary>
void Image::ThisObjRender()
{
	Render(m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// ���̃I�u�W�F�N�g�̃o�b�t�@�̐���
/// </summary>
void Image::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}