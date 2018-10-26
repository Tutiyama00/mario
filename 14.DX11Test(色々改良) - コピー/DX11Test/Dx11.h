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
	ID3D11DeviceContext*     m_pDeviceContext = nullptr;        //描画処理を行うクラス。内部的には、レンダリングコマンドと呼ばれるバイナリデータを作成し、GPUに送る。
	ID3D11Device*            m_pDevice        = nullptr;        //DirectX11の中心になるクラス。全体の管理とバッファ、シェーダ、テクスチャなどのリソース作成などを行う。
	UINT strides = 0;
	UINT offsets = 0;
	D3D11_VIEWPORT         m_ViewPort;

private:
	const UINT M_WINDOW_WIDTH                         = 1440;
	const UINT M_WINDOW_HEIGHT                        = 810;

	IDXGISwapChain*          m_pSwapChain             = nullptr;        //ウィンドウのへの表示やダブルバッファリングなどを行うクラス。
	                                                                    //GPUがレンダリングコマンドを解析することで実際の描画処理が行われる。
	ID3D11RenderTargetView*  m_pRenderTargetView      = nullptr;        //レンダリング結果の出力先を管理するクラス。
	ID3D11Texture2D*         m_pDepthStencilTexture2D = nullptr;        //深度ステンシルバッファ用のテクスチャリソース
	ID3D11DepthStencilView*  m_pDepthStencilView      = nullptr;        //深度バッファ。ピクセル毎の深度情報を記録しておくもので、物体の前後関係を正しく表示させるために使う。
	                                                                    //ステンシル。型抜きのようなことをするために使ったりすること。
	ID3D11SamplerState* m_pSampler           = nullptr;

public:
	template<class tfunction> HRESULT Render(tfunction ifunction)
	{
		float ClearColor[4] = { 0.0f,1.0f,1.0f,1.0f };
		//UINT strides = sizeof(vertex);
		//UINT offsets = 0;

		//pCamera->Shoot(m_pDeviceContext, &m_ViewPort, pCharacterManager->m_pPlayer->m_xPos);

		//クリア
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		//基礎設定
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_pDeviceContext->RSSetViewports(1, &m_ViewPort);
		m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

		ifunction();

		//Presentは１回でOK←複数置くと点滅などの現象がおこる←Presentは裏で描画したもの箱を開けて表示するようなものだから
		m_pSwapChain->Present(0, 0);

		return TRUE;
	}
};