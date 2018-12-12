#pragma once

#include<dsound.h>
#include"Singleton.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")

class SoundData : public Singleton<SoundData>
{
public:
	friend class Singleton<SoundData>;

public:
	void Initialize(HWND hwnd);

public:
	/* getter */
	LPDIRECTSOUNDBUFFER GetKICKsoundBuffer            ()const { return m_KICKsoundBuffer;             }
	LPDIRECTSOUNDBUFFER GetMARIO_JUMP_SMALLsoundBuffer()const { return m_MARIO_JUMP_SMALLsoundBuffer; }
	LPDIRECTSOUNDBUFFER GetSTANDARD_BGMsoundBuffer    ()const { return m_STANDARD_BGMsoundBuffer;     }
	LPDIRECTSOUNDBUFFER GetSTOMPsoundBuffer           ()const { return m_STOMPsoundBuffer;            }
	
private:
	SoundData() {};  //�R���X�g���N�^
	SoundData(const SoundData &soundData) {};  //�R�s�[�R���X�g���N�^
	~SoundData();    //�f�X�g���N�^

	HRESULT CreateSoundBuffer(LPDIRECTSOUNDBUFFER *dsb, const char *file);  //�T�E���h�o�b�t�@�̍쐬
	void CreateGameSound();

private:
	LPDIRECTSOUND8      m_LpDirectSound8       = nullptr;  //DirectSound8
	LPDIRECTSOUNDBUFFER m_LpPrimarySoundBuffer = nullptr;  //�v���C�}���[�T�E���h�o�b�t�@

	LPDIRECTSOUNDBUFFER m_KICKsoundBuffer             = nullptr;
	LPDIRECTSOUNDBUFFER m_MARIO_JUMP_SMALLsoundBuffer = nullptr;
	LPDIRECTSOUNDBUFFER m_STANDARD_BGMsoundBuffer     = nullptr;
	LPDIRECTSOUNDBUFFER m_STOMPsoundBuffer            = nullptr;

/*------Singleton------*/
protected:	
	bool m_InitializedFlag = false;  //���������Ă��邩�̃t���O�iTrue���������ς݁AFalse�����������j

protected:
	void Abstract() {};
};