#include"Camera.h"
#include<DirectXMath.h>

using namespace DirectX;

//変換行列
struct CameraConstantBuffer {
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

Camera::Camera(ID3D11Device* pDevice)
{
	HRESULT hr = TRUE;

	//定数バッファ作成
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth           = sizeof(CameraConstantBuffer);
	cbDesc.Usage               = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags      = 0;
	cbDesc.MiscFlags           = 0;
	cbDesc.StructureByteStride = 0;

	hr = pDevice->CreateBuffer(&cbDesc, NULL, &m_pCameraConstantBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error : CreateBuffer() m_pCameraConstantBuffer Failed.", "ERRER", MB_OK);
	}
}

Camera::~Camera()
{
	if (m_pCameraConstantBuffer != nullptr) { m_pCameraConstantBuffer->Release(); m_pCameraConstantBuffer = nullptr; }
}

//カメラ撮影
void Camera::Shoot(ID3D11DeviceContext* pDeviceContext, D3D11_VIEWPORT* pViewPort, float xPos)
{
	XMMATRIX worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	XMVECTOR eye        = XMVectorSet(xPos, 0.0f, -2.0f, 0.0f);  //カメラ位置
	XMVECTOR focus      = XMVectorSet(xPos, 0.0f, 0.0f, 0.0f);   //見るポジション
	XMVECTOR up         = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, focus, up);

	float    fov        = XMConvertToRadians(45.0f);
	float    aspect     = pViewPort->Width / pViewPort->Height;
	float    nearZ      = 0.1f;
	float    farZ       = 100.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

	CameraConstantBuffer cb;
	XMStoreFloat4x4(&cb.world, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&cb.view, XMMatrixTranspose(viewMatrix));
	XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(projMatrix));
	pDeviceContext->UpdateSubresource(m_pCameraConstantBuffer, 0, NULL, &cb, 0, 0);

	pDeviceContext->VSSetConstantBuffers(0, 1, &m_pCameraConstantBuffer);
}