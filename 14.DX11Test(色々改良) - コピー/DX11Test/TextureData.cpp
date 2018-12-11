#include"TextureData.h"
#include"WICTextureLoader.h"
#include"WICTextureLoader.cpp"
#include"Dx11.h"

/// <summary>
/// 初期化
/// </summary>
void TextureData::Initialize()
{
	m_InitializedFlag = true;

	//テクスチャの読み込み
	CoInitialize(NULL);   //COMライブラリの初期化が必要(絶対ここでしばらく詰んだ)
	
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/BLOCK.png"       , &m_pBLOCK_TR       , &m_pBLOCK_TSRV      );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/DOT_FONT.png"    , &m_pDOT_FONT_TR    , &m_pDOT_FONT_TSRV   );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/COIN1.png"       , &m_pCOIN1_TR       , &m_pCOIN1_TSRV      );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/KOURA1.png"      , &m_pKOURA1_TR      , &m_pKOURA1_TSRV     );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/KOURA2.png"      , &m_pKOURA2_TR      , &m_pKOURA2_TSRV     );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/KURIBO1.png"     , &m_pKURIBO1_TR     , &m_pKURIBO1_TSRV    );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/KURIBO2.png"     , &m_pKURIBO2_TR     , &m_pKURIBO2_TSRV    );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_DEAD.png"  , &m_pMARIO_DEAD_TR  , &m_pMARIO_DEAD_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_JUMP.png"  , &m_pMARIO_JUMP_TR  , &m_pMARIO_JUMP_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_RUN1.png"  , &m_pMARIO_RUN1_TR  , &m_pMARIO_RUN1_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_RUN2.png"  , &m_pMARIO_RUN2_TR  , &m_pMARIO_RUN2_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_RUN3.png"  , &m_pMARIO_RUN3_TR  , &m_pMARIO_RUN3_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_STAND.png" , &m_pMARIO_STAND_TR , &m_pMARIO_STAND_TSRV);
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/NOKONOKO1.png"   , &m_pNOKONOKO1_TR   , &m_pNOKONOKO1_TSRV  );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/NOKONOKO2.png"   , &m_pNOKONOKO2_TR   , &m_pNOKONOKO2_TSRV  );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/TITLE_LOGO.png"  , &m_pTITLE_LOGO_TR  , &m_pTITLE_LOGO_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/GOAL.png"        , &m_pGOAL_TR        , &m_pGOAL_TSRV       );

	//CoInitializeしたので呼ぶ
	CoUninitialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TextureData::~TextureData()
{
	if (m_pBLOCK_TR         != nullptr) { m_pBLOCK_TR         -> Release(); m_pBLOCK_TR         = nullptr; }
	if (m_pBLOCK_TSRV       != nullptr) { m_pBLOCK_TSRV       -> Release(); m_pBLOCK_TSRV       = nullptr; }
	if (m_pDOT_FONT_TR      != nullptr) { m_pDOT_FONT_TR      -> Release(); m_pDOT_FONT_TR      = nullptr; }
	if (m_pDOT_FONT_TSRV    != nullptr) { m_pDOT_FONT_TSRV    -> Release(); m_pDOT_FONT_TSRV    = nullptr; }
	if (m_pCOIN1_TR         != nullptr) { m_pCOIN1_TR         -> Release(); m_pCOIN1_TR         = nullptr; }
	if (m_pCOIN1_TSRV       != nullptr) { m_pCOIN1_TSRV       -> Release(); m_pCOIN1_TSRV       = nullptr; }
	if (m_pKOURA1_TR        != nullptr) { m_pKOURA1_TR        -> Release(); m_pKOURA1_TR        = nullptr; }
	if (m_pKOURA1_TSRV      != nullptr) { m_pKOURA1_TSRV      -> Release(); m_pKOURA1_TSRV      = nullptr; }
	if (m_pKOURA2_TR        != nullptr) { m_pKOURA2_TR        -> Release(); m_pKOURA2_TR        = nullptr; }
	if (m_pKOURA2_TSRV      != nullptr) { m_pKOURA2_TSRV      -> Release(); m_pKOURA2_TSRV      = nullptr; }
	if (m_pKURIBO1_TR       != nullptr) { m_pKURIBO1_TR       -> Release(); m_pKURIBO1_TR       = nullptr; }
	if (m_pKURIBO1_TSRV     != nullptr) { m_pKURIBO1_TSRV     -> Release(); m_pKURIBO1_TSRV     = nullptr; }
	if (m_pKURIBO2_TR       != nullptr) { m_pKURIBO2_TR       -> Release(); m_pKURIBO2_TR       = nullptr; }
	if (m_pKURIBO2_TSRV     != nullptr) { m_pKURIBO2_TSRV     -> Release(); m_pKURIBO2_TSRV     = nullptr; }
	if (m_pKURIBO_DEAD_TR   != nullptr) { m_pKURIBO_DEAD_TR   -> Release(); m_pKURIBO_DEAD_TR   = nullptr; }
	if (m_pKURIBO_DEAD_TSRV != nullptr) { m_pKURIBO_DEAD_TSRV -> Release(); m_pKURIBO_DEAD_TSRV = nullptr; }
	if (m_pMARIO_DEAD_TR    != nullptr) { m_pMARIO_DEAD_TR    -> Release(); m_pMARIO_DEAD_TR    = nullptr; }
	if (m_pMARIO_DEAD_TSRV  != nullptr) { m_pMARIO_DEAD_TSRV  -> Release(); m_pMARIO_DEAD_TSRV  = nullptr; }
	if (m_pMARIO_JUMP_TR    != nullptr) { m_pMARIO_JUMP_TR    -> Release(); m_pMARIO_JUMP_TR    = nullptr; }
	if (m_pMARIO_JUMP_TSRV  != nullptr) { m_pMARIO_JUMP_TSRV  -> Release(); m_pMARIO_JUMP_TSRV  = nullptr; }
	if (m_pMARIO_RUN1_TR    != nullptr) { m_pMARIO_RUN1_TR    -> Release(); m_pMARIO_RUN1_TR    = nullptr; }
	if (m_pMARIO_RUN1_TSRV  != nullptr) { m_pMARIO_RUN1_TSRV  -> Release(); m_pMARIO_RUN1_TSRV  = nullptr; }
	if (m_pMARIO_RUN2_TR    != nullptr) { m_pMARIO_RUN2_TR    -> Release(); m_pMARIO_RUN2_TR    = nullptr; }
	if (m_pMARIO_RUN2_TSRV  != nullptr) { m_pMARIO_RUN2_TSRV  -> Release(); m_pMARIO_RUN2_TSRV  = nullptr; }
	if (m_pMARIO_RUN3_TR    != nullptr) { m_pMARIO_RUN3_TR    -> Release(); m_pMARIO_RUN3_TR    = nullptr; }
	if (m_pMARIO_RUN3_TSRV  != nullptr) { m_pMARIO_RUN3_TSRV  -> Release(); m_pMARIO_RUN3_TSRV  = nullptr; }
	if (m_pMARIO_STAND_TR   != nullptr) { m_pMARIO_STAND_TR   -> Release(); m_pMARIO_STAND_TR   = nullptr; }
	if (m_pMARIO_STAND_TSRV != nullptr) { m_pMARIO_STAND_TSRV -> Release(); m_pMARIO_STAND_TSRV = nullptr; }
	if (m_pNOKONOKO1_TR     != nullptr) { m_pNOKONOKO1_TR     -> Release(); m_pNOKONOKO1_TR     = nullptr; }
	if (m_pNOKONOKO1_TSRV   != nullptr) { m_pNOKONOKO1_TSRV   -> Release(); m_pNOKONOKO1_TSRV   = nullptr; }
	if (m_pNOKONOKO2_TR     != nullptr) { m_pNOKONOKO2_TR     -> Release(); m_pNOKONOKO2_TR     = nullptr; }
	if (m_pNOKONOKO2_TSRV   != nullptr) { m_pNOKONOKO2_TSRV   -> Release(); m_pNOKONOKO2_TSRV   = nullptr; }
	if (m_pTITLE_LOGO_TR    != nullptr) { m_pTITLE_LOGO_TR    -> Release(); m_pTITLE_LOGO_TR    = nullptr; }
	if (m_pTITLE_LOGO_TSRV  != nullptr) { m_pTITLE_LOGO_TSRV  -> Release(); m_pTITLE_LOGO_TSRV  = nullptr; }
	if (m_pGOAL_TR          != nullptr) { m_pGOAL_TR          -> Release(); m_pGOAL_TR          = nullptr; }
	if (m_pGOAL_TSRV        != nullptr) { m_pGOAL_TSRV        -> Release(); m_pGOAL_TSRV        = nullptr; }
}