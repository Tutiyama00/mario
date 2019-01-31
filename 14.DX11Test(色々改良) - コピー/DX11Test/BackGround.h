#pragma once
#include<vector>
#include<d3d11.h>
#include"Math.h"
#include"RenderObj.h"

using namespace std;
using namespace OriginalMath;

/*�O���錾*/
class Image;

class BackGround : public RenderObj
{
public:
	BackGround(Vector3 pos, Vector2 size, ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV);
	~BackGround();

public:
	void NextCheck(float lookMinXPos);  //�w�i�̃|�W�V�����ς����s���Ă悢���̃`�F�b�N
	void AddBackGround(ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV);  //�w�i��ǉ�����

private:
	vector<Image*> m_BackGroundVector;        //�w�i�C���[�W���i�[����x�N�^�[�z��
	unsigned int m_HeadBackGroundNamber = 0;  //���ݐ擪�ʒu�ɂ���w�i�̔z��ԍ�

private:
	void LoopBackGround();  //�w�i�����[�v������

/*---RenderObj---*/
public:
	void ThisObjCreateBuffer()override;
	void ThisObjRender()override;

protected:
	void Abstract()override {};
};
