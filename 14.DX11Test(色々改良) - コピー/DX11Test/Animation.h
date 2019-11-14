#pragma once
#include<d3d11.h>
#include<vector>
#include<string>


using namespace std;

/* アニメーション用のリソース構造体 */
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
	vector<AnimResource> m_AnimRsrcVector;           //アニメーション用のリソース構造体の配列
	unsigned int m_AnimIntervalFlame       = 10;     //アニメーションとアニメ―ションの間のフレーム数
	unsigned int m_FlameCount              = 0;      //比較用のフレームカウンタ
	unsigned int m_NowAnimNamber           = 0;      //現在のアニメーションの番号（配列番号）
	bool         m_AnimPlayFlag            = false;  //アニメーション中かどうかのフラグ（true＝プレイ中、false＝プレイしていない）
};