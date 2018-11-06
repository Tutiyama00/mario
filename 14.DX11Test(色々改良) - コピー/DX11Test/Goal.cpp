#include"Goal.h"

/*�R���X�g���N�^*/
Goal::Goal(Vector3 pos, Vector2 size, ID3D11Device* pDevice) : Square(pos,size)
{
	LoadTexture(pDevice, L"Texture/MARIO_GOAL.png");
	CreateShader(pDevice, L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/*�f�X�g���N�^*/
Goal::~Goal() {};

/*�`��*/
void Goal::ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	Render(pDeviceContext, strides, offsets, m_pVertexArray, m_IndexArraySize);
}

/*�o�b�t�@�̐���*/
void Goal::ThisObjCreateBuffer(ID3D11Device* pDevice)
{
	CreateBuffer(pDevice, m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

void Goal::Abstract() {};