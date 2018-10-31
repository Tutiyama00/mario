#include"TitleScene.h"
#include"Title.h"
#include"Enum.h"
#include"Flag.h"
#include"Dx11.h"
#include"Camera.h"
#include"TextChar.h"
#include"TextCharacters.h"
#include"Characters.h"

TitleScene::TitleScene(ID3D11Device* pDevice)
{
	Vector3 pos = { 0.0f, 0.1f, -0.5f };
	Vector2 size = { 1.3f, 1.0f };

	m_pCamera       = new Camera(pDevice);
	m_pTitle        = new Title(pos, size, pDevice);
	m_NextGameState = GameState::TITLE;

	pos.x = -0.45f;
	pos.y = -0.4f;
	pos.z = -0.5f;
	size.x = size.y = 0.07f;

	m_pTextCharacters = new TextCharacters(pos, size,"1 PLAYER GAME", pDevice, TPS_WHITE);
}

TitleScene::~TitleScene()
{
	if (m_pCamera   != nullptr)   { delete m_pCamera;    m_pCamera   = nullptr; }
	if (m_pTitle    != nullptr)   { delete m_pTitle;     m_pTitle    = nullptr; }
	if (m_pTextCharacters != nullptr) { delete m_pTextCharacters;  m_pTextCharacters = nullptr; }
}

GameState TitleScene::UpDateScene(InputFlag inputFlag, Dx11* pDx11)
{
	UpDateGame(inputFlag);
	Draw(pDx11);

	return m_NextGameState;
}

void TitleScene::UpDateGame(InputFlag inputFlag)
{
	if (inputFlag.Check(InputFlagCode::INPUT_SPACE))
	{
		m_NextGameState = GameState::PLAY;
	}
}

void TitleScene::Draw(Dx11* pDx11)
{
	auto titleRender = [this,pDx11]
	{
		m_pCamera->Shoot(pDx11->m_pDeviceContext, &pDx11->m_ViewPort, 0.0f);
		m_pTextCharacters->Render(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
		m_pTitle->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	};

	pDx11->Render(titleRender);
}