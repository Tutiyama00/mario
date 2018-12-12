#include"Sound.h"


//�R���X�g���N�^
Dsound::Dsound(HWND hwnd)
{
	m_LpDirectSound        = nullptr;
	m_LpPrimarySoundBuffer = nullptr;

	HRESULT hr = S_OK;
	WAVEFORMATEX wf;

	//COM���C�u�����̏�����
	CoInitialize(NULL);

	//DirectSound8 ���쐬
	hr = DirectSoundCreate8(NULL, &m_LpDirectSound, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : DirectSoundCreate8() Failed.", "ERRER", MB_OK);
	}

	//�������x���ݒ�
	hr = m_LpDirectSound->SetCooperativeLevel(hwnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : SetCooperativeLevel() Failed.", "ERRER", MB_OK);
	}

	//�v���C�}���T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.dwSize = sizeof(dsDesc);
	dsDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsDesc.dwBufferBytes = 0;
	dsDesc.lpwfxFormat = NULL;
	hr = m_LpDirectSound->CreateSoundBuffer(&dsDesc, &m_LpPrimarySoundBuffer, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateSoundBuffer() Failed.", "ERRER", MB_OK);
	}

	//�v���C�}���o�b�t�@�̃X�e�[�^�X������
	wf.cbSize = sizeof(wf);
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
	hr = m_LpPrimarySoundBuffer->SetFormat(&wf);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : m_LpPrimarySoundBuffer->SetFormat() Failed.", "ERRER", MB_OK);
	}
}


//�f�X�g���N�^
Dsound::~Dsound()
{
	if (m_LpDirectSound != nullptr) { m_LpDirectSound->Release(); m_LpDirectSound = nullptr; }
	if (m_LpPrimarySoundBuffer != nullptr) 
	{
		m_LpPrimarySoundBuffer->Release(); 
		m_LpPrimarySoundBuffer = nullptr; 
	}

	CoUninitialize();
}


//�T�E���h�o�b�t�@�̍쐬
HRESULT Dsound::CreateSoundBuffer(LPDIRECTSOUNDBUFFER *pDirectSoundBuffer, const char *file)
{
	HRESULT hr = S_OK;
	MMCKINFO srcWaveFile;
	MMCKINFO srcWaveFmt;
	MMCKINFO srcWaveData;
	LPWAVEFORMATEX wf;

	//WAV�t�@�C�������[�h
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc)
	{
		MessageBox(NULL, "Error : CreateSoundBuffer() mmioOpenA() Failed.", "ERRER", MB_OK);
		return false;
	}

	//'WAVE'�`�����N�`�F�b�N
	ZeroMemory(&srcWaveFile, sizeof(srcWaveFile));
	srcWaveFile.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	hr = mmioDescend(hSrc, &srcWaveFile, NULL, MMIO_FINDRIFF);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : mmioDescend() srcWaveFile Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		return false;
	}

	//'fmt'�`�����N�`�F�b�N
	ZeroMemory(&srcWaveFmt, sizeof(srcWaveFile));
	srcWaveFmt.ckid = mmioFOURCC('f', 'm', 't', ' ');
	hr = mmioDescend(hSrc, &srcWaveFmt, &srcWaveFile, MMIO_FINDCHUNK);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : mmioDescend() srcWaveFmt Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		return false;
	}

	////�w�b�_�T�C�Y��WAVEFORMATEX�^�T�C�Y�ȉ��ɂȂ�Ȃ��悤�ɂ��Ă���H
	int srcHeaderSize = srcWaveFmt.cksize;
	if (srcHeaderSize < sizeof(WAVEFORMATEX))
	{
		srcHeaderSize = sizeof(WAVEFORMATEX);
	}


    //�w�b�_�������m��
    wf = (LPWAVEFORMATEX) malloc(srcHeaderSize);
    if (!wf) 
    {
	    MessageBox(NULL, "Error : new int() Failed.", "ERRER", MB_OK);
	    mmioClose(hSrc, 0);
	    delete wf;
	    return false;
    }
    ZeroMemory(wf, sizeof(LPWAVEFORMATEX));

	////WAVE�t�H�[�}�b�g�̃��[�h
	hr = mmioRead(hSrc, (HPSTR)wf, srcWaveFmt.cksize);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : mmioRead() Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		delete wf;
		return false;
	}

	//fmt�`�����N�ɖ߂�
	mmioAscend(hSrc, &srcWaveFmt, 0);

	//Data�`�����N��T��
	srcWaveData.ckid = mmioFOURCC('d', 'a', 't', 'a');
	hr = mmioDescend(hSrc, &srcWaveData, &srcWaveFile, MMIO_FINDCHUNK);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : mmioDescend() srcWaveData Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		delete wf;
		return false;
	}

	// �T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	dsdesc.dwBufferBytes = srcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	hr = m_LpDirectSound->CreateSoundBuffer(&dsdesc, pDirectSoundBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "Error : CreateSoundBuffer() Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		delete wf;
		return false;
	}

	//���b�N�J�n
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	hr = (*pDirectSoundBuffer)->Lock(0, srcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	if (FAILED(hr)) {
		MessageBox(NULL, "Error : Lock() Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		delete wf;
		return false;
	}

	//�f�[�^��������
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	//���b�N����
	(*pDirectSoundBuffer)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	//�������
	mmioClose(hSrc, 0);
	delete wf;
}