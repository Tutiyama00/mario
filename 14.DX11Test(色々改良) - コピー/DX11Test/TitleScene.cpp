#include"TitleScene.h"
#include"Title.h"
#include"Enum.h"
#include"Flag.h"
#include"Dx11.h"
#include"Camera.h"
#include"TextChar.h"
#include"TextCharacters.h"
#include"Characters.h"
#include"Timer.h"

/*コンストラクタ*/
TitleScene::TitleScene(ID3D11Device* pDevice)
{
	Vector3 pos = { 0.0f, 0.15f, -0.5f };
	Vector2 size = { 1.2f, 0.7f };

	m_pCamera       = new Camera(pDevice);
	m_pTitle        = new Title(pos, size, pDevice);
	m_NextGameState = GameState::TITLE;

	pos.x  = -0.45f;
	pos.y  = -0.65f;
	pos.z  = 0.0f;
	size.x = size.y = 0.07f;

	m_pTextCharacters = new TextCharacters(pos, size,"1 PLAYER GAME", pDevice, TPS_WHITE);
}

/*デストラクタ*/
TitleScene::~TitleScene()
{
	if (m_pCamera         != nullptr) { delete m_pCamera;          m_pCamera         = nullptr; }
	if (m_pTitle          != nullptr) { delete m_pTitle;           m_pTitle          = nullptr; }
	if (m_pTextCharacters != nullptr) { delete m_pTextCharacters;  m_pTextCharacters = nullptr; }
}

/*シーンの更新*/
GameState TitleScene::UpDateScene(InputFlag inputFlag, Dx11* pDx11)
{
	UpDateGame(inputFlag,pDx11->m_pDevice);
	Draw(pDx11);

	return m_NextGameState;
}

/*ゲームの更新*/
void TitleScene::UpDateGame(InputFlag inputFlag, ID3D11Device* pDevice)
{
	if (inputFlag.Check(InputFlagCode::INPUT_SPACE))
	{
		m_NextGameState = GameState::RESULT;
	}
}

/*描画*/
void TitleScene::Draw(Dx11* pDx11)
{
	m_pCamera        ->Shoot(pDx11->m_pDeviceContext, &pDx11->m_ViewPort, 0.0f);
	m_pTextCharacters->Render(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	m_pTitle         ->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
}