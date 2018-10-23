#pragma once

#include"Vertex.h"
#include"RenderObj.h"

class Title : public Square,public RenderObj
{
public:
	Title(float xPos, float yPos, float zPos, float xSize, float ySize, ID3D11Device* pDevice);
	~Title();

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

private:

	//---RenderObj---
	void Abstract();
};