#include"Image.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="size">�T�C�Y</param>
/// <param name="pDevice">�g�p����f�o�C�X</param>
/// <param name="pTextureFileName">�e�N�X�`���t�@�C���̃p�X</param>
Image::Image(Vector3 pos, Vector2 size, const wchar_t* pTextureFileName) : Square(pos,size)
{
	LoadTexture(pTextureFileName);
	CreateShader(L"Shader/TextVertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
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