#pragma once

#include"Vertex.h"
#include"RenderObj.h"

class Image : public Square,public RenderObj
{
public:
	Image(Vector3 pos, Vector2 size, ID3D11Resource* pTR, ID3D11ShaderResourceView* pTSRV);
	~Image() {};

protected:
	virtual void Abstract() {};


/*-------RenderObj------*/
public:
	void ThisObjRender();
	void ThisObjCreateBuffer();
};