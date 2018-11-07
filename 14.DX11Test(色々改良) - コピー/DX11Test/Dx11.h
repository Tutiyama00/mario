#pragma once

#include<d3d11.h>

class Dx11
{
public:
	Dx11();
	~Dx11();

	HRESULT Create(HWND hwnd);
	HRESULT AllDelete();

	void RenderStart();
	void RenderEnd();

public:
	/* getter */
	UINT           GetStrides()  { return strides; }
	UINT           GetOffsets()  { return offsets; }
	D3D11_VIEWPORT GetViewPort() { return m_ViewPort; }

public:
	ID3D11DeviceContext*     m_pDeviceContext = nullptr;        //�`�揈�����s���N���X�B�����I�ɂ́A�����_�����O�R�}���h�ƌĂ΂��o�C�i���f�[�^���쐬���AGPU�ɑ���B
	ID3D11Device*            m_pDevice        = nullptr;        //DirectX11�̒��S�ɂȂ�N���X�B�S�̂̊Ǘ��ƃo�b�t�@�A�V�F�[�_�A�e�N�X�`���Ȃǂ̃��\�[�X�쐬�Ȃǂ��s���B

private:
	const UINT M_WINDOW_WIDTH                         = 1000;
	const UINT M_WINDOW_HEIGHT                        = 750;

	IDXGISwapChain*          m_pSwapChain             = nullptr;        //�E�B���h�E�̂ւ̕\����_�u���o�b�t�@�����O�Ȃǂ��s���N���X�B
	                                                                    //GPU�������_�����O�R�}���h����͂��邱�ƂŎ��ۂ̕`�揈�����s����B
	ID3D11RenderTargetView*  m_pRenderTargetView      = nullptr;        //�����_�����O���ʂ̏o�͐���Ǘ�����N���X�B
	ID3D11Texture2D*         m_pDepthStencilTexture2D = nullptr;        //�[�x�X�e���V���o�b�t�@�p�̃e�N�X�`�����\�[�X
	ID3D11DepthStencilView*  m_pDepthStencilView      = nullptr;        //�[�x�o�b�t�@�B�s�N�Z�����̐[�x�����L�^���Ă������̂ŁA���̂̑O��֌W�𐳂����\�������邽�߂Ɏg���B
	                                                                    //�X�e���V���B�^�����̂悤�Ȃ��Ƃ����邽�߂Ɏg�����肷�邱�ƁB
	ID3D11SamplerState* m_pSampler = nullptr;
	bool m_RunningFlag = false;

	UINT strides = 0;
	UINT offsets = 0;
	D3D11_VIEWPORT m_ViewPort;
};