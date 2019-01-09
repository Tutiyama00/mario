#include<d3dcompiler.h>
#include"Dx11.h"
#include"DirectXTex.h"
#include"Player.h"
#include"Enum.h"
#include"Camera.h"
#include"Block.h"
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

		//-----�p�C�v���C���̏���---------
	    //�X���b�v�`�F�C���̍\���ݒ�
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));                             //����������A�ݒ肵�ĂȂ��̂���������G���[�f�����߁H
		sd.BufferCount                        = 1;                                 //�X���b�v�i�����j����o�b�t�@�̖����B�������ł��\�B
		sd.BufferDesc.Width                   = M_WINDOW_WIDTH;                    //�f�B�X�v���C�o�b�t�@�̉����B��{�̓E�B���h�E�T�C�Y�ł悢
		sd.BufferDesc.Height                  = M_WINDOW_HEIGHT;                   //�f�B�X�v���C�o�b�t�@�̏c���B��{�̓E�B���h�E�T�C�Y�ł悢
		sd.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;        //�f�B�X�v���C�o�b�t�@�̃t�H�[�}�b�g�B�������񂠂�̂Ō������Ȃ��Ƃ��߁B�������܂�Ⴂ���킩��Ȃ��B
		sd.BufferDesc.RefreshRate.Numerator   = 60;                                //���t���b�V�����[�g�̕���B���t���b�V�����[�g�Ƃ�1�b�Ԃɉ����ʂ����t���b�V�����邩�̂��ƁB
		sd.BufferDesc.RefreshRate.Denominator = 1;                                 //���t���b�V�����[�g�̕��q�B���t���b�V�����[�g�Ƃ�1�b�Ԃɉ����ʂ����t���b�V�����邩�̂��ƁB
		sd.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;   //�f�B�X�v���C�o�b�t�@�̎g�����̕��@
		sd.OutputWindow                       = hwnd;                              //�o�̓E�B���h�E�̎w��
		sd.SampleDesc.Count                   = 1;                                 //�T���v���J�E���g��
		sd.Windowed                           = TRUE;                              //TRUE���E�B���h�E���[�h�BFALSE���t���X�N���[�����[�h

		//�@�\���x���̐ݒ�
		D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
		D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;

		//�f�o�C�X�ƃX���b�v�`�F�C���̍쐬
		HRESULT hr;
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,                   // �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr�ŁAIDXGIAdapter�̃A�h���X��n��.
			D3D_DRIVER_TYPE_HARDWARE,  // �h���C�o�̃^�C�v��n���B����ȊO�͊�{�I�Ƀ\�t�g�E�F�A�����ŁA�ǂ����Ă��Ƃ�������f�o�O�p�ɗp����ׂ�.
			nullptr,                   // ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵���ۂɁA���̏������s��DLL�̃n���h����n���B����ȊO���w�肵�Ă���ۂɂ͕K��nullptr��n��.
			0,	                       // ���炩�̃t���O���w�肷��B�ڂ�����D3D11_CREATE_DEVICE�񋓌^�Ō���������.
			&pFeatureLevels,           // ���͂�����D3D_FEATURE_LEVEL�񋓌^�̔z���^����Bnullptr�ɂ��邱�Ƃŏ�Lfeature�Ɠ����̓��e�̔z�񂪎g�p�����.
			1,                         // ��L�����ŁA�����Œ�`�����z���^���Ă����ꍇ�A���̔z��̗v�f���������ɋL�q����.
			D3D11_SDK_VERSION,         // SDK�̃o�[�W�����B�K�����̒l.
			&sd,                       // DXGI_SWAP_CHAIN_DESC�\���̂̃A�h���X��ݒ肷��B�����Őݒ肵���\�����ɐݒ肳��Ă���p�����[�^��SwapChain���쐬�����.
			&m_pSwapChain,             // �쐬�����������ꍇ�ɁA����SwapChain�̃A�h���X���i�[����|�C���^�ϐ��ւ̃A�h���X�B�����Ŏw�肵���|�C���^�ϐ��o�R��SwapChain�𑀍삷��.
			&m_pDevice,                // ��L�Ƃقړ��l�ŁA������ɂ�Device�̃|�C���^�ϐ��̃A�h���X��ݒ肷��.
			pFeatureLevel,             // ���ۂɍ쐬�ɐ�������D3D_FEATURE_LEVEL���i�[���邽�߂�D3D_FEATURE_LEVEL�񋓌^�ϐ��̃A�h���X��ݒ肷��.
			&m_pDeviceContext	       // SwapChain��Device�Ɠ��l�ɁA������ɂ�Context�̃|�C���^�ϐ��̃A�h���X��ݒ肷��.
		);

		if (FAILED(hr))
		{
			MessageBox(NULL, "Error : D3D11CreateDeviceAndSwapChain() Failed.", "ERRER", MB_OK);
		}

		//RenderTargetView�쐬�̂��߁A
		//�X���b�v�`�F�C���ɗp�ӂ��ꂽ�o�b�t�@�i2DTexture�j���擾�B
		ID3D11Texture2D* pBack;
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack);

		//RenderTargetView�̍쐬
		m_pDevice->CreateRenderTargetView(pBack, NULL, &m_pRenderTargetView);
		pBack->Release();

		//�[�x�X�e���V���o�b�t�@�p�̃e�N�X�`�����\�[�X�̍쐬
		//DirectX�̏ꍇ�́A�[�x�o�b�t�@�ƃX�e���V���o�b�t�@���P�̃e�N�X�`�����\�[�X�ɋL�^����d�g�݂ɂȂ��Ă��邽�߁B
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width              = M_WINDOW_WIDTH;             //�e�N�X�`���\�̕��B
		descDepth.Height             = M_WINDOW_HEIGHT;            //�e�N�X�`���\�̍����B
		descDepth.MipLevels          = 1;                          //�e�N�X�`���\���̃~�b�v�}�b�v���x���̍ő吔�B
		descDepth.ArraySize          = 1;                          //�e�N�X�`���\�z����̃e�N�X�`���\�̐�
		descDepth.Format             = DXGI_FORMAT_D32_FLOAT;      //�e�N�X�`���\�t�H�[�}�b�g
		descDepth.SampleDesc.Count   = 1;                          //�s�N�Z���P�ʂ̃}���`�T���v�����O�̐��B
		descDepth.SampleDesc.Quality = 0;                          //�C���[�W�̕i�����x���B�i���������قǃp�t�H�[�}���X�͒ቺ����B
		descDepth.Usage              = D3D11_USAGE_DEFAULT;        //�e�N�X�`���\�̓ǂݍ��݋y�я������ݕ����̐ݒ�
		descDepth.BindFlags          = D3D11_BIND_DEPTH_STENCIL;   //�p�C�v���C���X�e�[�W�ւ̃o�C���h�Ɋւ���t���O
		descDepth.CPUAccessFlags     = 0;                          //������CPU�A�N�Z�X�̎�ނ��w�肷��t���O�B�O�̏ꍇ��CPU�A�N�Z�X���s�v�Ƃ������ƁB
		descDepth.MiscFlags          = 0;                          //���̈�ʐ��̒Ⴂ���\�[�X�I�v�V���������ʂ���t���O�B�O�̏ꍇ�̓t���O��K�p���Ȃ��Ƃ������ƁB
		m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencilTexture2D);

		//�[�x�X�e���V���r���[�̍쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		ZeroMemory(&dsvDesc, sizeof(dsvDesc));
		dsvDesc.Format             = descDepth.Format;
		dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
		m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture2D, NULL, &m_pDepthStencilView);

		//�T���v���[�̍쐬
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

		//�r���[�|�[�g�̐ݒ�
		m_ViewPort.Width    = (FLOAT)M_WINDOW_WIDTH;
		m_ViewPort.Height   = (FLOAT)M_WINDOW_HEIGHT;
		m_ViewPort.MinDepth = 0.0f;
		m_ViewPort.MaxDepth = 1.0f;
		m_ViewPort.TopLeftX = 0;
		m_ViewPort.TopLeftY = 0;
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Dx11::~Dx11() 
{
	if (!m_InitializedFlag) { MessageBox(NULL, "NotInitialize Dx11", "ERROR", MB_OK); return; }

	Dx11::AllDelete();
	CoUninitialize();
}

/// <summary>
/// ���
/// </summary>
/// <returns></returns>
void Dx11::AllDelete()
{
	if (m_pSwapChain             != nullptr) { m_pSwapChain            -> Release();  m_pSwapChain             = nullptr; }
	if (m_pDevice                != nullptr) { m_pDevice               -> Release();  m_pDevice                = nullptr; }
	if (m_pDeviceContext         != nullptr) { m_pDeviceContext        -> Release();  m_pDeviceContext         = nullptr; }
	if (m_pRenderTargetView      != nullptr) { m_pRenderTargetView     -> Release();  m_pRenderTargetView      = nullptr; }
	if (m_pDepthStencilTexture2D != nullptr) { m_pDepthStencilTexture2D-> Release();  m_pDepthStencilTexture2D = nullptr; }
	if (m_pDepthStencilView      != nullptr) { m_pDepthStencilView     -> Release();  m_pDepthStencilView      = nullptr; }
	if (m_pSampler               != nullptr) { m_pSampler              -> Release();  m_pSampler               = nullptr; }
}

//Render�J�n
void Dx11::RenderStart()
{
	if (!m_InitializedFlag) { MessageBox(NULL, "NotInitialize Dx11", "ERROR", MB_OK); return; }

	if (!m_RunningFlag)
	{
		m_RunningFlag = true;

		float ClearColor[4] = { 0.0f,0.3f,0.0f,0.0f };

		//�N���A
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		//��b�ݒ�
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

//Render�I��
void Dx11::RenderEnd()
{
	if (!m_InitializedFlag) { MessageBox(NULL, "NotInitialize Dx11", "ERROR", MB_OK); return; }

	if (m_RunningFlag)
	{
		//Present�͂P���OK�������u���Ɠ_�łȂǂ̌��ۂ������適Present�͗��ŕ`�悵�����̔����J���ĕ\������悤�Ȃ��̂�����
		m_pSwapChain->Present(0, 0);

		m_RunningFlag = false;
	}
	else
	{
		MessageBox(NULL, "NotPlayRender", "ERRER", MB_OK);
	}
}