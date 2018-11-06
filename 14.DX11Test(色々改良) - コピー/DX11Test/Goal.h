#pragma once

#include"Vertex.h"
#include"RenderObj.h"

class Goal : public Square,public RenderObj
{
public:
	Goal(Vector3 pos, Vector2 size, ID3D11Device* pDevice);
	~Goal();

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

protected:

	//---RenderObj---
	void Abstract();
};