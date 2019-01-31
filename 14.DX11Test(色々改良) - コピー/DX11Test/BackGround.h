#pragma once
#include<vector>
#include<d3d11.h>
#include"Math.h"
#include"RenderObj.h"

using namespace std;
using namespace OriginalMath;

/*前方宣言*/
class Image;

class BackGround : public RenderObj
{
public:
	BackGround(Vector3 pos, Vector2 size, ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV);
	~BackGround();

public:
	void NextCheck(float lookMinXPos);  //背景のポジション変えを行ってよいかのチェック
	void AddBackGround(ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV);  //背景を追加する

private:
	vector<Image*> m_BackGroundVector;        //背景イメージを格納するベクター配列
	unsigned int m_HeadBackGroundNamber = 0;  //現在先頭位置にある背景の配列番号

private:
	void LoopBackGround();  //背景をループさせる

/*---RenderObj---*/
public:
	void ThisObjCreateBuffer()override;
	void ThisObjRender()override;

protected:
	void Abstract()override {};
};
