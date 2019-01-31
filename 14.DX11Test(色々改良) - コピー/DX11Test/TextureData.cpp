#include"TextureData.h"
#include"WICTextureLoader.h"
#include"WICTextureLoader.cpp"
#include"Dx11.h"

/// <summary>
/// ������
/// </summary>
void TextureData::Initialize()
{
	m_InitializedFlag = true;

	//�e�N�X�`���̓ǂݍ���
	CoInitialize(NULL);   //COM���C�u�����̏��������K�v(��΂����ł��΂炭�l��)
	
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/BLOCK.png"       , &m_pBLOCK_TR       , &m_pBLOCK_TSRV      );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/DOT_FONT.png"    , &m_pDOT_FONT_TR    , &m_pDOT_FONT_TSRV   );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/COIN1.png"       , &m_pCOIN1_TR       , &m_pCOIN1_TSRV      );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/KOURA1.png"      , &m_pKOURA1_TR      , &m_pKOURA1_TSRV     );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/KOURA2.png"      , &m_pKOURA2_TR      , &m_pKOURA2_TSRV     );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/KURIBO1.png"     , &m_pKURIBO1_TR     , &m_pKURIBO1_TSRV    );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/KURIBO2.png"     , &m_pKURIBO2_TR     , &m_pKURIBO2_TSRV    );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/KURIBO_DEAD.png" , &m_pKURIBO_DEAD_TR , &m_pKURIBO_DEAD_TSRV);
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_DEAD.png"  , &m_pMARIO_DEAD_TR  , &m_pMARIO_DEAD_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_JUMP.png"  , &m_pMARIO_JUMP_TR  , &m_pMARIO_JUMP_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_RUN1.png"  , &m_pMARIO_RUN1_TR  , &m_pMARIO_RUN1_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_RUN2.png"  , &m_pMARIO_RUN2_TR  , &m_pMARIO_RUN2_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_RUN3.png"  , &m_pMARIO_RUN3_TR  , &m_pMARIO_RUN3_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/MARIO_STAND.png" , &m_pMARIO_STAND_TR , &m_pMARIO_STAND_TSRV);
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/NOKONOKO1.png"   , &m_pNOKONOKO1_TR   , &m_pNOKONOKO1_TSRV  );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/NOKONOKO2.png"   , &m_pNOKONOKO2_TR   , &m_pNOKONOKO2_TSRV  );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/TITLE_LOGO.png"  , &m_pTITLE_LOGO_TR  , &m_pTITLE_LOGO_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/BLOCK_GROUND.png", &m_pBLOCK_GROUND_TR, &m_pBLOCK_GROUND_TSRV);
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/GOAL_PIN.png"    , &m_pGOAL_PIN_TR    , &m_pGOAL_PIN_TSRV    );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/GOAL_POLE.png"   , &m_pGOAL_POLE_TR   , &m_pGOAL_POLE_TSRV   );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/GOAL_FLAG.png"   , &m_pGOAL_FLAG_TR   , &m_pGOAL_FLAG_TSRV   );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/GOAL_CASTLE.png" , &m_pGOAL_CASTLE_TR , &m_pGOAL_CASTLE_TSRV );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/CLAY_PIPE.png"   , &m_pCLAY_PIPE_TR   , &m_pCLAY_PIPE_TSRV   );
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/BACK_GROUND_1.png", &m_pBACK_GROUND_1_TR, &m_pBACK_GROUND_1_TSRV);
	DirectX::CreateWICTextureFromFile(Dx11::Instance()->m_pDevice, L"Texture/BACK_GROUND_2.png", &m_pBACK_GROUND_2_TR, &m_pBACK_GROUND_2_TSRV);

	//CoInitialize�����̂ŌĂ�
	CoUninitialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TextureData::~TextureData()
{
	if (m_pBLOCK_TR          != nullptr) { m_pBLOCK_TR          -> Release(); m_pBLOCK_TR          = nullptr; }
	if (m_pBLOCK_TSRV        != nullptr) { m_pBLOCK_TSRV        -> Release(); m_pBLOCK_TSRV        = nullptr; }
	if (m_pDOT_FONT_TR       != nullptr) { m_pDOT_FONT_TR       -> Release(); m_pDOT_FONT_TR       = nullptr; }
	if (m_pDOT_FONT_TSRV     != nullptr) { m_pDOT_FONT_TSRV     -> Release(); m_pDOT_FONT_TSRV     = nullptr; }
	if (m_pCOIN1_TR          != nullptr) { m_pCOIN1_TR          -> Release(); m_pCOIN1_TR          = nullptr; }
	if (m_pCOIN1_TSRV        != nullptr) { m_pCOIN1_TSRV        -> Release(); m_pCOIN1_TSRV        = nullptr; }
	if (m_pKOURA1_TR         != nullptr) { m_pKOURA1_TR         -> Release(); m_pKOURA1_TR         = nullptr; }
	if (m_pKOURA1_TSRV       != nullptr) { m_pKOURA1_TSRV       -> Release(); m_pKOURA1_TSRV       = nullptr; }
	if (m_pKOURA2_TR         != nullptr) { m_pKOURA2_TR         -> Release(); m_pKOURA2_TR         = nullptr; }
	if (m_pKOURA2_TSRV       != nullptr) { m_pKOURA2_TSRV       -> Release(); m_pKOURA2_TSRV       = nullptr; }
	if (m_pKURIBO1_TR        != nullptr) { m_pKURIBO1_TR        -> Release(); m_pKURIBO1_TR        = nullptr; }
	if (m_pKURIBO1_TSRV      != nullptr) { m_pKURIBO1_TSRV      -> Release(); m_pKURIBO1_TSRV      = nullptr; }
	if (m_pKURIBO2_TR        != nullptr) { m_pKURIBO2_TR        -> Release(); m_pKURIBO2_TR        = nullptr; }
	if (m_pKURIBO2_TSRV      != nullptr) { m_pKURIBO2_TSRV      -> Release(); m_pKURIBO2_TSRV      = nullptr; }
	if (m_pKURIBO_DEAD_TR    != nullptr) { m_pKURIBO_DEAD_TR    -> Release(); m_pKURIBO_DEAD_TR    = nullptr; }
	if (m_pKURIBO_DEAD_TSRV  != nullptr) { m_pKURIBO_DEAD_TSRV  -> Release(); m_pKURIBO_DEAD_TSRV  = nullptr; }
	if (m_pMARIO_DEAD_TR     != nullptr) { m_pMARIO_DEAD_TR     -> Release(); m_pMARIO_DEAD_TR     = nullptr; }
	if (m_pMARIO_DEAD_TSRV   != nullptr) { m_pMARIO_DEAD_TSRV   -> Release(); m_pMARIO_DEAD_TSRV   = nullptr; }
	if (m_pMARIO_JUMP_TR     != nullptr) { m_pMARIO_JUMP_TR     -> Release(); m_pMARIO_JUMP_TR     = nullptr; }
	if (m_pMARIO_JUMP_TSRV   != nullptr) { m_pMARIO_JUMP_TSRV   -> Release(); m_pMARIO_JUMP_TSRV   = nullptr; }
	if (m_pMARIO_RUN1_TR     != nullptr) { m_pMARIO_RUN1_TR     -> Release(); m_pMARIO_RUN1_TR     = nullptr; }
	if (m_pMARIO_RUN1_TSRV   != nullptr) { m_pMARIO_RUN1_TSRV   -> Release(); m_pMARIO_RUN1_TSRV   = nullptr; }
	if (m_pMARIO_RUN2_TR     != nullptr) { m_pMARIO_RUN2_TR     -> Release(); m_pMARIO_RUN2_TR     = nullptr; }
	if (m_pMARIO_RUN2_TSRV   != nullptr) { m_pMARIO_RUN2_TSRV   -> Release(); m_pMARIO_RUN2_TSRV   = nullptr; }
	if (m_pMARIO_RUN3_TR     != nullptr) { m_pMARIO_RUN3_TR     -> Release(); m_pMARIO_RUN3_TR     = nullptr; }
	if (m_pMARIO_RUN3_TSRV   != nullptr) { m_pMARIO_RUN3_TSRV   -> Release(); m_pMARIO_RUN3_TSRV   = nullptr; }
	if (m_pMARIO_STAND_TR    != nullptr) { m_pMARIO_STAND_TR    -> Release(); m_pMARIO_STAND_TR    = nullptr; }
	if (m_pMARIO_STAND_TSRV  != nullptr) { m_pMARIO_STAND_TSRV  -> Release(); m_pMARIO_STAND_TSRV  = nullptr; }
	if (m_pNOKONOKO1_TR      != nullptr) { m_pNOKONOKO1_TR      -> Release(); m_pNOKONOKO1_TR      = nullptr; }
	if (m_pNOKONOKO1_TSRV    != nullptr) { m_pNOKONOKO1_TSRV    -> Release(); m_pNOKONOKO1_TSRV    = nullptr; }
	if (m_pNOKONOKO2_TR      != nullptr) { m_pNOKONOKO2_TR      -> Release(); m_pNOKONOKO2_TR      = nullptr; }
	if (m_pNOKONOKO2_TSRV    != nullptr) { m_pNOKONOKO2_TSRV    -> Release(); m_pNOKONOKO2_TSRV    = nullptr; }
	if (m_pTITLE_LOGO_TR     != nullptr) { m_pTITLE_LOGO_TR     -> Release(); m_pTITLE_LOGO_TR     = nullptr; }
	if (m_pTITLE_LOGO_TSRV   != nullptr) { m_pTITLE_LOGO_TSRV   -> Release(); m_pTITLE_LOGO_TSRV   = nullptr; }
	if (m_pBLOCK_GROUND_TR   != nullptr) { m_pBLOCK_GROUND_TR   -> Release(); m_pBLOCK_GROUND_TR   = nullptr; }
	if (m_pBLOCK_GROUND_TSRV != nullptr) { m_pBLOCK_GROUND_TSRV -> Release(); m_pBLOCK_GROUND_TSRV = nullptr; }
	if (m_pGOAL_PIN_TR       != nullptr) { m_pGOAL_PIN_TR       -> Release(); m_pGOAL_PIN_TR       = nullptr; }
	if (m_pGOAL_PIN_TSRV     != nullptr) { m_pGOAL_PIN_TSRV     -> Release(); m_pGOAL_PIN_TSRV     = nullptr; }
	if (m_pGOAL_POLE_TR      != nullptr) { m_pGOAL_POLE_TR      -> Release(); m_pGOAL_POLE_TR      = nullptr; }
	if (m_pGOAL_POLE_TSRV    != nullptr) { m_pGOAL_POLE_TSRV    -> Release(); m_pGOAL_POLE_TSRV    = nullptr; }
	if (m_pGOAL_FLAG_TR      != nullptr) { m_pGOAL_FLAG_TR      -> Release(); m_pGOAL_FLAG_TR      = nullptr; }
	if (m_pGOAL_FLAG_TSRV    != nullptr) { m_pGOAL_FLAG_TSRV    -> Release(); m_pGOAL_FLAG_TSRV    = nullptr; }
	if (m_pGOAL_CASTLE_TR    != nullptr) { m_pGOAL_CASTLE_TR    -> Release(); m_pGOAL_CASTLE_TR    = nullptr; }
	if (m_pGOAL_CASTLE_TSRV  != nullptr) { m_pGOAL_CASTLE_TSRV  -> Release(); m_pGOAL_CASTLE_TSRV  = nullptr; }
	if (m_pCLAY_PIPE_TR      != nullptr) { m_pCLAY_PIPE_TR      -> Release(); m_pCLAY_PIPE_TR      = nullptr; }
	if (m_pCLAY_PIPE_TSRV    != nullptr) { m_pCLAY_PIPE_TSRV    -> Release(); m_pCLAY_PIPE_TSRV    = nullptr; }
	if (m_pBACK_GROUND_1_TR != nullptr) { m_pBACK_GROUND_1_TR->Release(); m_pBACK_GROUND_1_TR = nullptr; }
	if (m_pBACK_GROUND_1_TSRV != nullptr) { m_pBACK_GROUND_1_TSRV->Release(); m_pBACK_GROUND_1_TSRV = nullptr; }
	if (m_pBACK_GROUND_2_TR != nullptr) { m_pBACK_GROUND_2_TR->Release(); m_pBACK_GROUND_2_TR = nullptr; }
	if (m_pBACK_GROUND_2_TSRV != nullptr) { m_pBACK_GROUND_2_TSRV->Release(); m_pBACK_GROUND_2_TSRV = nullptr; }
}