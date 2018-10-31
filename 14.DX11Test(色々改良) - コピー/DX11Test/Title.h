#pragma once

#include"Vertex.h"
#include"RenderObj.h"
#include"Math.h"

using namespace OriginalMath;

class Title : public Square,public RenderObj
{
public:
	Title(Vector3 pos, Vector2 size, ID3D11Device* pDevice);
	~Title();

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

private:

	//---RenderObj---
	void Abstract();
};