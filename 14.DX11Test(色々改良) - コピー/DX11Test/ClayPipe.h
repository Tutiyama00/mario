#pragma once

#include"Block.h"

class ClayPipe : public Block
{
public:
	ClayPipe(Vector3 pos, Vector2 size, unsigned int height);
	~ClayPipe() {};
};