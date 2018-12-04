#include"Animation.h"
#include"Dx11.h"
#include"WICTextureLoader.h"
#include"Timer.h"

/// <summary>
/// アニメーションをプレイする
/// </summary>
/// <returns>このフレームのリソース</returns>
AnimResource Animation::AnimPlay()
{
	unsigned int animAmount = 0;

	/* フレームのカウントアップ */
	m_FlameCount++;

	/* 総アニメーション数　＝　フレームカウンタ　／　アニメーション間フレーム数 */
	animAmount = m_FlameCount / m_AnimIntervalFlame;

	/* ０の場合割り算ができないため */
	animAmount++;

	/* 現在のアニメーション番号　＝　総アニメーション数　％　１アニメーション数 */
	m_NowAnimNamber = animAmount % m_AnimRsrcVector.size();

	return m_AnimRsrcVector[m_NowAnimNamber];
}

void Animation::AnimReset()
{
	m_FlameCount = 0;
	m_NowAnimNamber = 0;
}

void Animation::AddAnimResource(const wchar_t* pFileNames)
{
	//テクスチャの読み込み
	CoInitialize(NULL);   //COMライブラリの初期化が必要(絶対ここでしばらく詰んだ)
	AnimResource animResource;

	HRESULT hr = S_OK;

	//テクスチャの読み込み
	hr = DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, pFileNames, &animResource.m_pAnimTextureResource, &animResource.m_pAnimTextureSRV);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateWICTextureFromFile() Anime Failed.", "ERRER", MB_OK);
	}

	m_AnimRsrcVector.push_back(animResource);


	//CoInitializeしたので呼ぶ
	CoUninitialize();
}