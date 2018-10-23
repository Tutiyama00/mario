#pragma once

#include<dsound.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")

class Dsound
{
public:
	Dsound(HWND hwnd);
	~Dsound();

	HRESULT CreateSoundBuffer(LPDIRECTSOUNDBUFFER *dsb, const char *file);

private:
	LPDIRECTSOUND8 m_LpDirectSound;
	LPDIRECTSOUNDBUFFER m_LpPrimarySoundBuffer;
};