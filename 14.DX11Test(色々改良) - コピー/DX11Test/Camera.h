#pragma once

#include<d3d11.h>

class Camera
{
public:
	Camera(ID3D11Device* device);
	~Camera();

	void Shoot(ID3D11DeviceContext* pDeviceContext, D3D11_VIEWPORT* pViewPort, float xPos);

public:
	ID3D11Buffer*   m_pCameraConstantBuffer = nullptr;
};