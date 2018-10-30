#include"TitleScene.h"
#include"Title.h"
#include"Enum.h"
#include"Flag.h"
#include"Dx11.h"
#include"Camera.h"
#include"TextChar.h"

TitleScene::TitleScene(ID3D11Device* pDevice)
{
	m_pCamera = new Camera(pDevice);
	m_pTitle = new Title(0.0f, 0.0f, -0.5f, 1.5, 1.3, pDevice);
	m_NextGameState = GameState::TITLE;

	float texLeftUp[2]    = { 0.0f,0.0f };
	float texRightDown[2] = { 1.0f,1.0f };
	float color[4]        = { 1.0f,1.0f ,1.0f ,0.0f };
	m_pTextChar           = new TextChar(0.0f, 0.0f, -0.5f, 1.0f, 1.0f, pDevice, texLeftUp, texRightDown,TC_BLACK,'!');
}

TitleScene::~TitleScene()
{
	if (m_pCamera != nullptr)   { delete m_pCamera;    m_pCamera   = nullptr; }
	if (m_pTitle  != nullptr)   { delete m_pTitle;     m_pTitle    = nullptr; }
	if (m_pTextChar != nullptr) { delete m_pTextChar;  m_pTextChar = nullptr; }
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
		m_pTextChar->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
		m_pTitle->ThisObjRender(pDx11->m_pDeviceContext, pDx11->strides, pDx11->offsets);
	};

	pDx11->Render(titleRender);
}