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

class Dx11
{
public:
	Dx11();
	~Dx11();

	HRESULT Create(HWND hwnd);
	HRESULT Render(Camera* pCamera, GameState gameState, CharacterManager* pCharacterManager);
	HRESULT AllDelete();

public:
	ID3D11DeviceContext*     m_pDeviceContext = nullptr;        //描画処理を行うクラス。内部的には、レンダリングコマンドと呼ばれるバイナリデータを作成し、GPUに送る。
	ID3D11Device*            m_pDevice        = nullptr;        //DirectX11の中心になるクラス。全体の管理とバッファ、シェーダ、テクスチャなどのリソース作成などを行う。

private:
	const UINT M_WINDOW_WIDTH                         = 1440;
	const UINT M_WINDOW_HEIGHT                        = 810;

	IDXGISwapChain*          m_pSwapChain             = nullptr;        //ウィンドウのへの表示やダブルバッファリングなどを行うクラス。
	                                                                    //GPUがレンダリングコマンドを解析することで実際の描画処理が行われる。
	ID3D11RenderTargetView*  m_pRenderTargetView      = nullptr;        //レンダリング結果の出力先を管理するクラス。
	ID3D11Texture2D*         m_pDepthStencilTexture2D = nullptr;        //深度ステンシルバッファ用のテクスチャリソース
	ID3D11DepthStencilView*  m_pDepthStencilView      = nullptr;        //深度バッファ。ピクセル毎の深度情報を記録しておくもので、物体の前後関係を正しく表示させるために使う。
	                                                                    //ステンシル。型抜きのようなことをするために使ったりすること。
	D3D11_VIEWPORT         m_ViewPort;

	ID3D11SamplerState* m_pSampler           = nullptr;

private:
	float m_StandardSize = 0.1f;
	float m_StandardZpos = -0.5f;

public:
	void ObjectMakes(Object* stageArray, int stageHeight, int stageWidth);

public:
	Player* m_pPlayer = nullptr;
	std::vector<Block*> m_BlockVector;
	Title* m_pTitle = nullptr;
};