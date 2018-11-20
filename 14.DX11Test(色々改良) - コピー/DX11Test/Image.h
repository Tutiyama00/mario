#pragma once

#include"Vertex.h"
#include"RenderObj.h"

class Image : public Square,public RenderObj
{
public:
	Image(Vector3 pos, Vector2 size, const wchar_t* pTextureFileName);
	~Image() {};

	/*---RenderObj---*/
	void ThisObjRender();
	void ThisObjCreateBuffer();

protected:
	virtual void Abstract() {};
};