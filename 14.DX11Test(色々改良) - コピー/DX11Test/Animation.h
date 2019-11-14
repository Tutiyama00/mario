#pragma once
#include<d3d11.h>
#include<vector>
#include<string>


using namespace std;

/* �A�j���[�V�����p�̃��\�[�X�\���� */
struct AnimResource
{
public:
	ID3D11Resource*           m_pAnimTextureResource = nullptr;
	ID3D11ShaderResourceView* m_pAnimTextureSRV      = nullptr;
};

class Animation
{
public:
	Animation() {};
	~Animation() {};

	void AnimPlay();
	void AnimReset();
	void AddAnimResource(ID3D11Resource*  pTR, ID3D11ShaderResourceView* pTSVR);

public:
	/* getter */
	 ID3D11Resource*           GetAnimTextureResource()const { return m_AnimRsrcVector[m_NowAnimNamber].m_pAnimTextureResource; }
	 ID3D11ShaderResourceView* GetAnimTextureSRV     ()const { return m_AnimRsrcVector[m_NowAnimNamber].m_pAnimTextureSRV; }
	 unsigned int              GetAnimIntervalFlame  ()const { return m_AnimIntervalFlame; }
	/* setter */
	void SetAnimIntervalFlame(unsigned int value) { m_AnimIntervalFlame = value; }

private:
	vector<AnimResource> m_AnimRsrcVector;           //�A�j���[�V�����p�̃��\�[�X�\���̂̔z��
	unsigned int m_AnimIntervalFlame       = 10;     //�A�j���[�V�����ƃA�j���\�V�����̊Ԃ̃t���[����
	unsigned int m_FlameCount              = 0;      //��r�p�̃t���[���J�E���^
	unsigned int m_NowAnimNamber           = 0;      //���݂̃A�j���[�V�����̔ԍ��i�z��ԍ��j
	bool         m_AnimPlayFlag            = false;  //�A�j���[�V���������ǂ����̃t���O�itrue���v���C���Afalse���v���C���Ă��Ȃ��j
};