#include"Goal.h"


/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="size">�T�C�Y</param>
Goal::Goal(Vector3 pos, Vector2 size) : Square(pos,size)
{
	LoadTexture(L"Texture/MARIO_GOAL.png");
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Goal::~Goal() {};


/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// ���̃I�u�W�F�N�g�̕`��
/// </summary>
void Goal::ThisObjRender()
{
	Render(m_pVertexArray, m_IndexArraySize);
}

/// <summary>
/// ���̃I�u�W�F�N�g�̃o�b�t�@�̐���
/// </summary>
void Goal::ThisObjCreateBuffer()
{
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}