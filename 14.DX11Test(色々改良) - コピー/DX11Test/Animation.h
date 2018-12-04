#pragma once
#include<d3d11.h>
#include<vector>

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
	Animation();
	~Animation();

private:
	void CreateAnimResource(const wchar_t* pFileName, AnimResource* pAnimResource);

private:
	vector<AnimResource> m_AnimRsrcVector;  //アニメーション用のリソース構造体の配列
};