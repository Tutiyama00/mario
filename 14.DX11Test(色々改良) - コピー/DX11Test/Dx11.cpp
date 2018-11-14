#include<d3dcompiler.h>
#include"Dx11.h"
#include"DirectXTex.h"
#include"Player.h"
#include"Enum.h"
#include"Camera.h"
#include"Block.h"
#include"WICTextureLoader.h"
#include"Characters.h"

using namespace DirectX;

/*######################    Dx11   ###################################*/

/*----------------------  public   -----------------------------------*/

void Dx11::Initialize(HWND hwnd)
{
	if (!m_InitializedFlag)
	{
		m_InitializedFlag = true;

		strides = sizeof(vertex);

		//-----パイプラインの準備---------
	    //スワップチェインの構成設定
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));                             //初期化する、設定してないのがあったらエラー吐くため？
		sd.BufferCount                        = 1;                                 //スワップ（交換）するバッファの枚数。複数枚でも可能。
		sd.BufferDesc.Width                   = M_WINDOW_WIDTH;                    //ディスプレイバッファの横幅。基本はウィンドウサイズでよい
		sd.BufferDesc.Height                  = M_WINDOW_HEIGHT;                   //ディスプレイバッファの縦幅。基本はウィンドウサイズでよい
		sd.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;        //ディスプレイバッファのフォーマット。たくさんあるので検索しないとだめ。正直あまり違いがわからない。
		sd.BufferDesc.RefreshRate.Numerator   = 60;                                //リフレッシュレートの分母。リフレッシュレートとは1秒間に何回画面をリフレッシュするかのこと。
		sd.BufferDesc.RefreshRate.Denominator = 1;                                 //リフレッシュレートの分子。リフレッシュレートとは1秒間に何回画面をリフレッシュするかのこと。
		sd.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;   //ディスプレイバッファの使われ方の方法
		sd.OutputWindow                       = hwnd;                              //出力ウィンドウの指定
		sd.SampleDesc.Count                   = 1;                                 //サンプルカウント数
		sd.Windowed                           = TRUE;                              //TRUE＝ウィンドウモード。FALSE＝フルスクリーンモード

		//機能レベルの設定
		D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
		D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;

		//デバイスとスワップチェインの作成
		HRESULT hr;
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,                   // どのビデオアダプタを使用するか？既定ならばnullptrで、IDXGIAdapterのアドレスを渡す.
			D3D_DRIVER_TYPE_HARDWARE,  // ドライバのタイプを渡す。これ以外は基本的にソフトウェア実装で、どうしてもという時やデバグ用に用いるべし.
			nullptr,                   // 上記をD3D_DRIVER_TYPE_SOFTWAREに設定した際に、その処理を行うDLLのハンドルを渡す。それ以外を指定している際には必ずnullptrを渡す.
			0,	                       // 何らかのフラグを指定する。詳しくはD3D11_CREATE_DEVICE列挙型で検索検索ぅ.
			&pFeatureLevels,           // 実はここでD3D_FEATURE_LEVEL列挙型の配列を与える。nullptrにすることで上記featureと同等の内容の配列が使用される.
			1,                         // 上記引数で、自分で定義した配列を与えていた場合、その配列の要素数をここに記述する.
			D3D11_SDK_VERSION,         // SDKのバージョン。必ずこの値.
			&sd,                       // DXGI_SWAP_CHAIN_DESC構造体のアドレスを設定する。ここで設定した構造愛に設定されているパラメータでSwapChainが作成される.
			&m_pSwapChain,             // 作成が成功した場合に、そのSwapChainのアドレスを格納するポインタ変数へのアドレス。ここで指定したポインタ変数経由でSwapChainを操作する.
			&m_pDevice,                // 上記とほぼ同様で、こちらにはDeviceのポインタ変数のアドレスを設定する.
			pFeatureLevel,             // 実際に作成に成功したD3D_FEATURE_LEVELを格納するためのD3D_FEATURE_LEVEL列挙型変数のアドレスを設定する.
			&m_pDeviceContext	       // SwapChainやDeviceと同様に、こちらにはContextのポインタ変数のアドレスを設定する.
		);

		if (FAILED(hr))
		{
			MessageBox(NULL, "Error : D3D11CreateDeviceAndSwapChain() Failed.", "ERRER", MB_OK);
		}

		//RenderTargetView作成のため、
		//スワップチェインに用意されたバッファ（2DTexture）を取得。
		ID3D11Texture2D* pBack;
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack);

		//RenderTargetViewの作成
		m_pDevice->CreateRenderTargetView(pBack, NULL, &m_pRenderTargetView);
		pBack->Release();

		//深度ステンシルバッファ用のテクスチャリソースの作成
		//DirectXの場合は、深度バッファとステンシルバッファを１つのテクスチャリソースに記録する仕組みになっているため。
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width              = M_WINDOW_WIDTH;             //テクスチャ―の幅。
		descDepth.Height             = M_WINDOW_HEIGHT;            //テクスチャ―の高さ。
		descDepth.MipLevels          = 1;                          //テクスチャ―内のミップマップレベルの最大数。
		descDepth.ArraySize          = 1;                          //テクスチャ―配列内のテクスチャ―の数
		descDepth.Format             = DXGI_FORMAT_D32_FLOAT;      //テクスチャ―フォーマット
		descDepth.SampleDesc.Count   = 1;                          //ピクセル単位のマルチサンプリングの数。
		descDepth.SampleDesc.Quality = 0;                          //イメージの品質レベル。品質が高いほどパフォーマンスは低下する。
		descDepth.Usage              = D3D11_USAGE_DEFAULT;        //テクスチャ―の読み込み及び書き込み方式の設定
		descDepth.BindFlags          = D3D11_BIND_DEPTH_STENCIL;   //パイプラインステージへのバインドに関するフラグ
		descDepth.CPUAccessFlags     = 0;                          //許可するCPUアクセスの種類を指定するフラグ。０の場合はCPUアクセスが不要ということ。
		descDepth.MiscFlags          = 0;                          //他の一般性の低いリソースオプションを識別するフラグ。０の場合はフラグを適用しないということ。
		m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencilTexture2D);

		//深度ステンシルビューの作成
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		ZeroMemory(&dsvDesc, sizeof(dsvDesc));
		dsvDesc.Format             = descDepth.Format;
		dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
		m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture2D, NULL, &m_pDepthStencilView);

		//サンプラーの作成
		D3D11_SAMPLER_DESC smpDesc;
		ZeroMemory(&smpDesc, sizeof(smpDesc));
		smpDesc.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		hr = m_pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Error : CreateSamplerState() Failed.", "ERRER", MB_OK);
		}

		//ビューポートの設定
		m_ViewPort.Width    = (FLOAT)M_WINDOW_WIDTH;
		m_ViewPort.Height   = (FLOAT)M_WINDOW_HEIGHT;
		m_ViewPort.MinDepth = 0.0f;
		m_ViewPort.MaxDepth = 1.0f;
		m_ViewPort.TopLeftX = 0;
		m_ViewPort.TopLeftY = 0;
	}
}

Dx11::~Dx11() 
{
	if (!m_InitializedFlag) { MessageBox(NULL, "NotInitialize Dx11", "ERROR", MB_OK); return; }

	Dx11::AllDelete();
	CoUninitialize();
}

//解放
HRESULT Dx11::AllDelete()
{
	if (m_pSwapChain             != nullptr) { m_pSwapChain            -> Release();  m_pSwapChain             = nullptr; }
	if (m_pDevice                != nullptr) { m_pDevice               -> Release();  m_pDevice                = nullptr; }
	if (m_pDeviceContext         != nullptr) { m_pDeviceContext        -> Release();  m_pDeviceContext         = nullptr; }
	if (m_pRenderTargetView      != nullptr) { m_pRenderTargetView     -> Release();  m_pRenderTargetView      = nullptr; }
	if (m_pDepthStencilTexture2D != nullptr) { m_pDepthStencilTexture2D-> Release();  m_pDepthStencilTexture2D = nullptr; }
	if (m_pDepthStencilView      != nullptr) { m_pDepthStencilView     -> Release();  m_pDepthStencilView      = nullptr; }
	if (m_pSampler               != nullptr) { m_pSampler              -> Release();  m_pSampler               = nullptr; }

	return TRUE;
}

//Render開始
void Dx11::RenderStart()
{
	if (!m_InitializedFlag) { MessageBox(NULL, "NotInitialize Dx11", "ERROR", MB_OK); return; }

	if (!m_RunningFlag)
	{
		m_RunningFlag = true;

		float ClearColor[4] = { 0.0f,0.0f,0.0f,1.0f };

		//クリア
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		//基礎設定
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_pDeviceContext->RSSetViewports(1, &m_ViewPort);
		m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	}
	else
	{
		MessageBox(NULL, "RenderNow!", "ERRER", MB_OK);
	}
}

//Render終了
void Dx11::RenderEnd()
{
	if (!m_InitializedFlag) { MessageBox(NULL, "NotInitialize Dx11", "ERROR", MB_OK); return; }

	if (m_RunningFlag)
	{
		//Presentは１回でOK←複数置くと点滅などの現象がおこる←Presentは裏で描画したもの箱を開けて表示するようなものだから
		m_pSwapChain->Present(0, 0);

		m_RunningFlag = false;
	}
	else
	{
		MessageBox(NULL, "NotPlayRender", "ERRER", MB_OK);
	}
}