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
	LPDIRECTSOUNDBUFFER GetSTAGE_CLEARPsoundBuffer    ()const { return m_STAGE_CLEARsoundBuffer; }
	LPDIRECTSOUNDBUFFER GetMARIO_DIEsoundBuffer()const { return m_MARIO_DIEsoundBuffer; }
	LPDIRECTSOUNDBUFFER GetGAME_OVERsoundBuffer()const { return m_GAME_OVERsoundBuffer; }
	
private:
	SoundData() {};  //コンストラクタ
	SoundData(const SoundData &soundData) {};  //コピーコンストラクタ
	~SoundData();    //デストラクタ

	HRESULT CreateSoundBuffer(LPDIRECTSOUNDBUFFER *dsb, const char *file);  //サウンドバッファの作成
	void CreateGameSound();

private:
	LPDIRECTSOUND8      m_LpDirectSound8       = nullptr;  //DirectSound8
	LPDIRECTSOUNDBUFFER m_LpPrimarySoundBuffer = nullptr;  //プライマリーサウンドバッファ

	LPDIRECTSOUNDBUFFER m_KICKsoundBuffer             = nullptr;
	LPDIRECTSOUNDBUFFER m_MARIO_JUMP_SMALLsoundBuffer = nullptr;
	LPDIRECTSOUNDBUFFER m_STANDARD_BGMsoundBuffer     = nullptr;
	LPDIRECTSOUNDBUFFER m_STOMPsoundBuffer            = nullptr;
	LPDIRECTSOUNDBUFFER m_STAGE_CLEARsoundBuffer      = nullptr;
	LPDIRECTSOUNDBUFFER m_MARIO_DIEsoundBuffer = nullptr;
	LPDIRECTSOUNDBUFFER m_GAME_OVERsoundBuffer = nullptr;

/*------Singleton------*/
protected:	
	bool m_InitializedFlag = false;  //初期化しているかのフラグ（True＝初期化済み、False＝未初期化）

protected:
	void Abstract() {};
};