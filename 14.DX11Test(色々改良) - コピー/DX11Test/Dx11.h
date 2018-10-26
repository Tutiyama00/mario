#pragma once

#include<d3d11.h>
#include<vector>

class Camera;
enum class GameState : unsigned char;

class Player;
class Block;
class Title;
enum class Object : unsigned char;
class CharacterManager;
struct vertex;

class Dx11
{
public:
	Dx11();
	~Dx11();

	HRESULT Create(HWND hwnd);
	HRESULT AllDelete();

public:
	ID3D11DeviceContext*     m_pDeviceContext = nullptr;        //�`�揈�����s���N���X�B�����I�ɂ́A�����_�����O�R�}���h�ƌĂ΂��o�C�i���f�[�^���쐬���AGPU�ɑ���B
	ID3D11Device*            m_pDevice        = nullptr;        //DirectX11�̒��S�ɂȂ�N���X�B�S�̂̊Ǘ��ƃo�b�t�@�A�V�F�[�_�A�e�N�X�`���Ȃǂ̃��\�[�X�쐬�Ȃǂ��s���B
	UINT strides = 0;
	UINT offsets = 0;
	D3D11_VIEWPORT         m_ViewPort;

private:
	const UINT M_WINDOW_WIDTH                         = 1440;
	const UINT M_WINDOW_HEIGHT                        = 810;

	IDXGISwapChain*          m_pSwapChain             = nullptr;        //�E�B���h�E�̂ւ̕\����_�u���o�b�t�@�����O�Ȃǂ��s���N���X�B
	                                                                    //GPU�������_�����O�R�}���h����͂��邱�ƂŎ��ۂ̕`�揈�����s����B
	ID3D11RenderTargetView*  m_pRenderTargetView      = nullptr;        //�����_�����O���ʂ̏o�͐���Ǘ�����N���X�B
	ID3D11Texture2D*         m_pDepthStencilTexture2D = nullptr;        //�[�x�X�e���V���o�b�t�@�p�̃e�N�X�`�����\�[�X
	ID3D11DepthStencilView*  m_pDepthStencilView      = nullptr;        //�[�x�o�b�t�@�B�s�N�Z�����̐[�x�����L�^���Ă������̂ŁA���̂̑O��֌W�𐳂����\�������邽�߂Ɏg���B
	                                                                    //�X�e���V���B�^�����̂悤�Ȃ��Ƃ����邽�߂Ɏg�����肷�邱�ƁB
	ID3D11SamplerState* m_pSampler           = nullptr;

public:
	template<class tfunction> HRESULT Render(tfunction ifunction)
	{
		float ClearColor[4] = { 0.0f,1.0f,1.0f,1.0f };
		//UINT strides = sizeof(vertex);
		//UINT offsets = 0;

		//pCamera->Shoot(m_pDeviceContext, &m_ViewPort, pCharacterManager->m_pPlayer->m_xPos);

		//�N���A
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		//��b�ݒ�
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_pDeviceContext->RSSetViewports(1, &m_ViewPort);
		m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

		ifunction();

		//Present�͂P���OK�������u���Ɠ_�łȂǂ̌��ۂ������適Present�͗��ŕ`�悵�����̔����J���ĕ\������悤�Ȃ��̂�����
		m_pSwapChain->Present(0, 0);

		return TRUE;
	}
};