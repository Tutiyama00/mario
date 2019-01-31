#include"BackGround.h"
#include"Image.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�ꖇ�ڂ̔w�i�̃|�W�V����</param>
/// <param name="size">�ꖇ�ڂ̔w�i�̃T�C�Y</param>
/// <param name="pTR">�ꖇ�ڂ̔w�i��TR</param>
/// <param name="pTSRV">�ꖇ�ڂ̔w�i��TSRV</param>
BackGround::BackGround(Vector3 pos, Vector2 size, ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV)
{
	/*�ꖇ�ڂ�ǉ�*/
	m_BackGroundVector.push_back(new Image(pos, size, pTR, pTSRV, false));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BackGround::~BackGround()
{
	for (int i = 0; i < m_BackGroundVector.size(); i++)
	{
		if (m_BackGroundVector[i] != nullptr) { delete m_BackGroundVector[i]; m_BackGroundVector[i] = nullptr; }
	}
	m_BackGroundVector.clear();
}

/// <summary>
/// �w�i�̃|�W�V�����ς����s���Ă悢���̃`�F�b�N
/// </summary>
/// <param name="lookMinXPos">���\�͈͂̍����E�l</param>
void BackGround::NextCheck(float lookMinXPos)
{
	/*�擪�w�i�������E�l��荶���ɂ��邩���܂��ʂɉf���Ă��Ȃ���*/
	if (m_BackGroundVector[m_HeadBackGroundNamber]->m_pVertexArray[1].pos.x < lookMinXPos)
	{
		LoopBackGround();
	}
}

/// <summary>
/// �w�i�̒ǉ�
/// </summary>
/// <param name="pTR">�e�N�X�`�����\�[�X</param>
/// <param name="pTSRV">�e�N�X�`���V�F�[�_���\�[�X�r���[</param>
void BackGround::AddBackGround(ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV)
{
	Vector3 pos = { m_BackGroundVector[m_BackGroundVector.size() - 1]->GetxPos() + m_BackGroundVector[m_BackGroundVector.size() - 1]->GetxSize(),
					m_BackGroundVector[m_BackGroundVector.size() - 1]->GetyPos() ,
					m_BackGroundVector[m_BackGroundVector.size() - 1]->GetzPos() };
	Vector2 size = { m_BackGroundVector[m_BackGroundVector.size() - 1]->GetxSize(),
					 m_BackGroundVector[m_BackGroundVector.size() - 1]->GetySize() };

	m_BackGroundVector.push_back(new Image(pos, size, pTR, pTSRV, false));
}

/// <summary>
/// �w�i�C���[�W�����[�v������
/// </summary>
void BackGround::LoopBackGround()
{
	/*���̐擪�z��ԍ�*/
      	unsigned int nextHeadBackGroundNamber = m_HeadBackGroundNamber + 1;

	/*���̐擪�z��ԍ����z�񐔂𒴂��Ă��邩�ǂ���*/
	if (nextHeadBackGroundNamber == m_BackGroundVector.size())
	{
		/*�z��ԍ����O�ɖ߂�*/
		nextHeadBackGroundNamber = 0;
	}

	/*�擪�w�i���Ō���ʒu�Ɉړ�������*/
	m_BackGroundVector[m_HeadBackGroundNamber]->VertexMove(m_BackGroundVector[nextHeadBackGroundNamber]->GetxSize() * m_BackGroundVector.size(), 0.0f);

	/*�擪�z��ԍ��̍X�V*/
	m_HeadBackGroundNamber = nextHeadBackGroundNamber;
}

void BackGround::ThisObjCreateBuffer()
{
	for (int i = 0; i < m_BackGroundVector.size(); i++)
	{
		m_BackGroundVector[i]->ThisObjCreateBuffer();
	}
}

void BackGround::ThisObjRender()
{
	for (int i = 0; i < m_BackGroundVector.size(); i++)
	{
		m_BackGroundVector[i]->ThisObjRender();
	}
}