#include"Animation.h"
#include"Dx11.h"
#include"Timer.h"

/// <summary>
/// アニメーションをプレイする
/// </summary>
/// <returns>このフレームのリソース</returns>
void Animation::AnimPlay()
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
}

/// <summary>
/// アニメーションを初期状態に戻す
/// </summary>
void Animation::AnimReset()
{
	m_FlameCount    = 0;
	m_NowAnimNamber = 0;
}

/// <summary>
/// アニメーション１カットを追加する
/// </summary>
/// <param name="pFileNames">追加したいカットのテクスチャファイルのパス</param>
void Animation::AddAnimResource(ID3D11Resource*  pTR, ID3D11ShaderResourceView* pTSVR)
{
	AnimResource animResource;

	animResource.m_pAnimTextureResource = pTR;
	animResource.m_pAnimTextureSRV      = pTSVR;

	/* 配列に追加 */
	m_AnimRsrcVector.push_back(animResource);
}