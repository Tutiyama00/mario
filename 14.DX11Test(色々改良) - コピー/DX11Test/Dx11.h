#pragma once

#include<d3d11.h>
#include"Singleton.h"

class Dx11 : public Singleton<Dx11>
{
public:
	friend class Singleton<Dx11>;

public:
	void Initialize(HWND hwnd); //初期化関数

	void RenderStart();
	void RenderEnd();

public:
	/* getter */
	UINT           GetStrides()  { return strides; }
	UINT           GetOffsets()  { return offsets; }
	D3D11_VIEWPORT GetViewPort() { return m_ViewPort; }

public:
	ID3D11DeviceContext*     m_pDeviceContext = nullptr;        //描画処理を行うクラス。内部的には、レンダリングコマンドと呼ばれるバイナリデータを作成し、GPUに送る。
	ID3D11Device*            m_pDevice        = nullptr;        //DirectX11の中心になるクラス。全体の管理とバッファ、シェーダ、テクスチャなどのリソース作成などを行う。

private:
	const UINT M_WINDOW_WIDTH                         = 1000;
	const UINT M_WINDOW_HEIGHT                        = 750;

	IDXGISwapChain*          m_pSwapChain             = nullptr;        //ウィンドウのへの表示やダブルバッファリングなどを行うクラス。
	                                                                    //GPUがレンダリングコマンドを解析することで実際の描画処理が行われる。
	ID3D11RenderTargetView*  m_pRenderTargetView      = nullptr;        //レンダリング結果の出力先を管理するクラス。
	ID3D11Texture2D*         m_pDepthStencilTexture2D = nullptr;        //深度ステンシルバッファ用のテクスチャリソース
	ID3D11DepthStencilView*  m_pDepthStencilView      = nullptr;        //深度バッファ。ピクセル毎の深度情報を記録しておくもので、物体の前後関係を正しく表示させるために使う。
	                                                                    //ステンシル。型抜きのようなことをするために使ったりすること。
	ID3D11SamplerState* m_pSampler = nullptr;
	bool m_RunningFlag = false;

	UINT strides = 0;
	UINT offsets = 0;
	D3D11_VIEWPORT m_ViewPort;

private:
	Dx11() {};
	Dx11(const Dx11 &gameManager) {};
	~Dx11();

	HRESULT AllDelete();

protected:
	bool m_InitializedFlag = false;  //初期化しているかのフラグ（True＝初期化済み、False＝未初期化）

protected:
	void Abstract() {};  //純粋仮想関数（これによってこのクラスはインスタンスできない)
};