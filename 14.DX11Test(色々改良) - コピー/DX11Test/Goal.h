#pragma once

#include"Vertex.h"
#include"RenderObj.h"

class Goal : public Square,public RenderObj
{
public:
	Goal(Vector3 pos, Vector2 size);
	~Goal();

	//---RenderObj---
	void ThisObjRender();
	void ThisObjCreateBuffer();

protected:

	//---RenderObj---
	void Abstract();
};