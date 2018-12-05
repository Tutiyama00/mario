#include"Animation.h"
#include"Dx11.h"
#include"WICTextureLoader.h"
#include"Timer.h"

/// <summary>
/// �A�j���[�V�������v���C����
/// </summary>
/// <returns>���̃t���[���̃��\�[�X</returns>
AnimResource Animation::AnimPlay()
{
	unsigned int animAmount = 0;

	/* �t���[���̃J�E���g�A�b�v */
	m_FlameCount++;

	/* ���A�j���[�V�������@���@�t���[���J�E���^�@�^�@�A�j���[�V�����ԃt���[���� */
	animAmount = m_FlameCount / m_AnimIntervalFlame;

	/* �O�̏ꍇ����Z���ł��Ȃ����� */
	animAmount++;

	/* ���݂̃A�j���[�V�����ԍ��@���@���A�j���[�V�������@���@�P�A�j���[�V������ */
	m_NowAnimNamber = animAmount % m_AnimRsrcVector.size();

	return m_AnimRsrcVector[m_NowAnimNamber];
}

/// <summary>
/// �A�j���[�V������������Ԃɖ߂�
/// </summary>
void Animation::AnimReset()
{
	m_FlameCount    = 0;
	m_NowAnimNamber = 0;
}

/// <summary>
/// �A�j���[�V�����P�J�b�g��ǉ�����
/// </summary>
/// <param name="pFileNames">�ǉ��������J�b�g�̃e�N�X�`���t�@�C���̃p�X</param>
void Animation::AddAnimResource(const wchar_t* pFileNames)
{
	//�e�N�X�`���̓ǂݍ���
	CoInitialize(NULL);   //COM���C�u�����̏��������K�v(��΂����ł��΂炭�l��)
	AnimResource animResource;

	HRESULT hr = S_OK;

	//�e�N�X�`���̓ǂݍ���
	hr = DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, pFileNames, &animResource.m_pAnimTextureResource, &animResource.m_pAnimTextureSRV);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateWICTextureFromFile() Anime Failed.", "ERRER", MB_OK);
	}

	/* �z��ɒǉ� */
	m_AnimRsrcVector.push_back(animResource);


	//CoInitialize�����̂ŌĂ�
	CoUninitialize();
}