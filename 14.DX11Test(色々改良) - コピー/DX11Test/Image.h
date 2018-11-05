#pragma once

#include"Vertex.h"
#include"RenderObj.h"

class Image : public Square,public RenderObj
{
public:
	Image(Vector3 pos, Vector2 size, ID3D11Device* pDevice, const wchar_t* pTextureFileName);
	~Image();

	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

protected:
	virtual void Abstract();
};