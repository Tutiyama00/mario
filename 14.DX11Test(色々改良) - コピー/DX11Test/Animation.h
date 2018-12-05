#pragma once
#include<d3d11.h>
#include<vector>
#include<string>


using namespace std;

/* アニメーション用のリソース構造体 */
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
	vector<AnimResource> m_AnimRsrcVector;           //アニメーション用のリソース構造体の配列
	unsigned int m_AnimIntervalFlame       = 10;      //アニメーションとアニメ―ションの間のフレーム数
	unsigned int m_FlameCount              = 0;      //比較用のフレームカウンタ
	unsigned int m_NowAnimNamber           = 0;      //現在のアニメーションの番号（配列番号）
	bool         m_AnimPlayFlag            = false;  //アニメーション中かどうかのフラグ（true＝プレイ中、false＝プレイしていない）
};