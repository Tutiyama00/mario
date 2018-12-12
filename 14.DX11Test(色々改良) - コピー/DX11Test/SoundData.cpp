#include"SoundData.h"


/// <summary>
/// 初期化関数
/// </summary>
/// <param name="hwnd">ウィンドウハンドル</param>
void SoundData::Initialize(HWND hwnd)
{
	m_InitializedFlag = true;

	HRESULT hr = S_OK;
	WAVEFORMATEX wf;

	/* COMライブラリの初期化 */
	CoInitialize(NULL);

	/* DirectSound8 を作成 */
	hr = DirectSoundCreate8(NULL, &m_LpDirectSound8, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : DirectSoundCreate8() Failed.", "ERRER", MB_OK);
	}

	/* 協調レベル設定 */
	hr = m_LpDirectSound8->SetCooperativeLevel(hwnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : SetCooperativeLevel() Failed.", "ERRER", MB_OK);
	}

	/* プライマリサウンドバッファの作成 */
	DSBUFFERDESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.dwSize = sizeof(dsDesc);
	dsDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsDesc.dwBufferBytes = 0;
	dsDesc.lpwfxFormat = NULL;
	hr = m_LpDirectSound8->CreateSoundBuffer(&dsDesc, &m_LpPrimarySoundBuffer, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateSoundBuffer() Failed.", "ERRER", MB_OK);
	}

	/* プライマリバッファのステータスを決定 */
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

	CreateGameSound();
}


/// <summary>
/// デストラクタ
/// </summary>
SoundData::~SoundData()
{
	if (m_KICKsoundBuffer             != nullptr) { m_KICKsoundBuffer            ->Release(); m_KICKsoundBuffer             = nullptr; }
	if (m_MARIO_JUMP_SMALLsoundBuffer != nullptr) { m_MARIO_JUMP_SMALLsoundBuffer->Release(); m_MARIO_JUMP_SMALLsoundBuffer = nullptr; }
	if (m_STANDARD_BGMsoundBuffer     != nullptr) { m_STANDARD_BGMsoundBuffer    ->Release(); m_STANDARD_BGMsoundBuffer     = nullptr; }
	if (m_STOMPsoundBuffer            != nullptr) { m_STOMPsoundBuffer           ->Release(); m_STOMPsoundBuffer            = nullptr; }

	if (m_LpPrimarySoundBuffer != nullptr) { m_LpPrimarySoundBuffer->Release(); m_LpPrimarySoundBuffer = nullptr; }

	/* DirectSound8を最後にリリースしないといけない */
	if (m_LpDirectSound8 != nullptr) { m_LpDirectSound8->Release(); m_LpDirectSound8 = nullptr; }

	CoUninitialize();
}


/// <summary>
/// サウンドバッファの作成
/// </summary>
/// <param name="pDirectSoundBuffer">データを格納するバッファ</param>
/// <param name="file">音楽ファイルのパス</param>
/// <returns></returns>
HRESULT SoundData::CreateSoundBuffer(LPDIRECTSOUNDBUFFER *pDirectSoundBuffer, const char *file)
{
	HRESULT hr = S_OK;
	MMCKINFO srcWaveFile;
	MMCKINFO srcWaveFmt;
	MMCKINFO srcWaveData;
	LPWAVEFORMATEX wf;

	//WAVファイルをロード
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc)
	{
		MessageBox(NULL, "Error : CreateSoundBuffer() mmioOpenA() Failed.", "ERRER", MB_OK);
		return false;
	}

	//'WAVE'チャンクチェック
	ZeroMemory(&srcWaveFile, sizeof(srcWaveFile));
	srcWaveFile.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	hr = mmioDescend(hSrc, &srcWaveFile, NULL, MMIO_FINDRIFF);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : mmioDescend() srcWaveFile Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		return false;
	}

	//'fmt'チャンクチェック
	ZeroMemory(&srcWaveFmt, sizeof(srcWaveFile));
	srcWaveFmt.ckid = mmioFOURCC('f', 'm', 't', ' ');
	hr = mmioDescend(hSrc, &srcWaveFmt, &srcWaveFile, MMIO_FINDCHUNK);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : mmioDescend() srcWaveFmt Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		return false;
	}

	////ヘッダサイズをWAVEFORMATEX型サイズ以下にならないようにしている？
	int srcHeaderSize = srcWaveFmt.cksize;
	if (srcHeaderSize < sizeof(WAVEFORMATEX))
	{
		srcHeaderSize = sizeof(WAVEFORMATEX);
	}


    //ヘッダメモリ確保
    wf = (LPWAVEFORMATEX) malloc(srcHeaderSize);
    if (!wf) 
    {
	    MessageBox(NULL, "Error : new int() Failed.", "ERRER", MB_OK);
	    mmioClose(hSrc, 0);
	    delete wf;
	    return false;
    }
    ZeroMemory(wf, sizeof(LPWAVEFORMATEX));

	////WAVEフォーマットのロード
	hr = mmioRead(hSrc, (HPSTR)wf, srcWaveFmt.cksize);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : mmioRead() Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		delete wf;
		return false;
	}

	//fmtチャンクに戻る
	mmioAscend(hSrc, &srcWaveFmt, 0);

	//Dataチャンクを探す
	srcWaveData.ckid = mmioFOURCC('d', 'a', 't', 'a');
	hr = mmioDescend(hSrc, &srcWaveData, &srcWaveFile, MMIO_FINDCHUNK);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : mmioDescend() srcWaveData Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		delete wf;
		return false;
	}

	// サウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	dsdesc.dwBufferBytes = srcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	hr = m_LpDirectSound8->CreateSoundBuffer(&dsdesc, pDirectSoundBuffer, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "Error : CreateSoundBuffer() Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		delete wf;
		return false;
	}

	//ロック開始
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	hr = (*pDirectSoundBuffer)->Lock(0, srcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	if (FAILED(hr)) {
		MessageBox(NULL, "Error : Lock() Failed.", "ERRER", MB_OK);
		mmioClose(hSrc, 0);
		delete wf;
		return false;
	}

	//データ書き込み
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	//ロック解除
	(*pDirectSoundBuffer)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	//解放処理
	mmioClose(hSrc, 0);
	delete wf;
}

/// <summary>
/// 使用するサウンドバッファをすべて作成する
/// </summary>
void SoundData::CreateGameSound()
{
	CreateSoundBuffer(&m_KICKsoundBuffer            , "Sound/KICK.wav"            );
	CreateSoundBuffer(&m_MARIO_JUMP_SMALLsoundBuffer, "Sound/MARIO_JUMP_SMALL.wav");
	CreateSoundBuffer(&m_STANDARD_BGMsoundBuffer    , "Sound/STANDARD_BGM.wav"    );
	CreateSoundBuffer(&m_STOMPsoundBuffer           , "Sound/STOMP.wav"           );
}