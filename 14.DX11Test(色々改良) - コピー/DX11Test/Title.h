#pragma once

#include"Vertex.h"
#include"RenderObj.h"
#include"Math.h"

using namespace OriginalMath;

class Title : public Square,public RenderObj
{
public:
	Title(Vector3 pos, Vector2 size);
	~Title();

	//---RenderObj---
	void ThisObjRender();
	void ThisObjCreateBuffer();

private:

	//---RenderObj---
	void Abstract();
};