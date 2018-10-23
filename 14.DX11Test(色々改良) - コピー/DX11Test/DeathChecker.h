#pragma once

#include"Vertex.h"
#include"RenderObj.h"

class DeathChecker : Square,RenderObj
{
public:
	DeathChecker(float xPos, float yPos, float zPos, float xSize, float ySize, ID3D11Device* pDevice);
	~DeathChecker();

	bool DeathCheck(Polygon* pSquare);

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

private:
	void Abstract() {};
};