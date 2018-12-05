#pragma once
#include<d3d11.h>
#include<vector>
#include<string>


using namespace std;

/* �A�j���[�V�����p�̃��\�[�X�\���� */
struct AnimResource
{
	ID3D11Resource*           m_pAnimTextureResource = nullptr;
	ID3D11ShaderResourceView* m_pAnimTextureSRV      = nullptr;
};

class Animation
{
public:
	Animation() {};
	~Animation() {};

	AnimResource AnimPlay();
	void AnimReset();
	void AddAnimResource(const wchar_t* pFileNames);

public:
	/* setter */
	void SetAnimIntervalFlame(unsigned int value) { m_AnimIntervalFlame = value; }

private:
	vector<AnimResource> m_AnimRsrcVector;           //�A�j���[�V�����p�̃��\�[�X�\���̂̔z��
	unsigned int m_AnimIntervalFlame       = 10;      //�A�j���[�V�����ƃA�j���\�V�����̊Ԃ̃t���[����
	unsigned int m_FlameCount              = 0;      //��r�p�̃t���[���J�E���^
	unsigned int m_NowAnimNamber           = 0;      //���݂̃A�j���[�V�����̔ԍ��i�z��ԍ��j
	bool         m_AnimPlayFlag            = false;  //�A�j���[�V���������ǂ����̃t���O�itrue���v���C���Afalse���v���C���Ă��Ȃ��j
};