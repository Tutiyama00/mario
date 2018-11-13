#pragma once

#include<d3d11.h>

class Camera
{
public:
	Camera();
	~Camera();

	void Shoot(float xPos);

private:
	ID3D11Buffer*   m_pCameraConstantBuffer = nullptr;
};