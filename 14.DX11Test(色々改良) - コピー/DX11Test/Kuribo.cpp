#include"Kuribo.h"
#include"Enum.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="size">�T�C�Y</param>
Kuribo::Kuribo(Vector3 pos, Vector2 size) : Enemy(pos,size)
{
	LoadTexture(L"Texture/KURIBO.png");
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}