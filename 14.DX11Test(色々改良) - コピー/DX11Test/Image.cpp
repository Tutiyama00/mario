#include"Image.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="size">�T�C�Y</param>
/// <param name="pDevice">�g�p����f�o�C�X</param>
/// <param name="pTextureFileName">�e�N�X�`���t�@�C���̃p�X</param>
Image::Image(Vector3 pos, Vector2 size, ID3D11Device* pDevice, const wchar_t* pTextureFileName) : Square(pos,size)
{
	LoadTexture(pDevice, pTextureFileName);
	CreateShader(pDevice, L"Shader/TextVertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Image::~Image() {}

/// <summary>
/// ���ۉ����邽�߂ɏ������z�֐�����������
/// </summary>
void Image::Abstract() {}

/// <summary>
/// ���̃I�u�W�F�N�g�̕`��
/// </summary>
/// <param name="pDeviceContext">�f�o�C�X�R���e�L�X�g</param>
/// <param name="strides"></param>
/// <param name="offsets"></param>
void Image::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// ���̃I�u�W�F�N�g�̃o�b�t�@�̐���
/// </summary>
/// <param name="pDevice">�f�o�C�X</param>
void Image::ThisObjCreateBuffer(ID3D11Device* pDevice)
{
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}
