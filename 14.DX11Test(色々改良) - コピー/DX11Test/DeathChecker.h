#pragma once

#include"Vertex.h"
#include"RenderObj.h"
#include"Math.h"

using namespace OriginalMath;

class DeathChecker : Square,RenderObj
{
public:
	DeathChecker(Vector3 pos, Vector2 size, ID3D11Device* pDevice);
	~DeathChecker();

	bool DeathCheck(Polygon* pSquare);

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

private:
	void Abstract() {};
};