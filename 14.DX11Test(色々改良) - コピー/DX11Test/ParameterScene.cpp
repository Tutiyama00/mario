#include"ParameterScene.h"
#include"Flag.h"
#include"Timer.h"
#include"TextCharacters.h"
#include"Enum.h"
#include"Dx11.h"
#include"Image.h"
#include<string>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="nowGameState">現在のゲームステート</param>
ParameterScene::ParameterScene(GameState nowGameState)
{
	m_NextGameState = nowGameState;

	Vector3 pos  = { -0.8f,0.85f,0.0f };
	Vector2 size = { 0.07f,0.07f };
	m_pTextOfMARIO = new TextCharacters(pos, size, "MARIO", TPS_WHITE);

	pos.y = 0.775f;
	m_pTextOfScoreNamber = new TextCharacters(pos, size, "000000", TPS_WHITE);

	pos.x = 0.125f;
	pos.y = 0.85f;
	m_pTextOfWORLD = new TextCharacters(pos, size, "WORLD", TPS_WHITE);

	pos.x = 0.19f;
	pos.y = 0.775f;
	m_pTextOfWorldNamber = new TextCharacters(pos, size, "1-1", TPS_WHITE);

	pos.x = 0.6f;
	pos.y = 0.85f;
	m_pTextOfTIME  = new TextCharacters(pos, size, "TIME", TPS_WHITE);

	pos.x = 0.675f;
	pos.y = 0.775f;
	m_pTextOfTimeNamber = new TextCharacters(pos, size, "   ", TPS_WHITE);

	pos.x = -0.275f;
	m_pImageOfCoin = new Image(pos, size, L"Texture/COIN1.png");

	pos.x = -0.225f;
	m_pTextOfCoinNamber = new TextCharacters(pos, size, "*00", TPS_WHITE);

	m_pTimer = new Timer();
	m_pTimer->SetTimeRemaining(110);
	int time = m_pTimer->CountStart();

	m_pTextOfTimeNamber->ChangeText(std::to_string(time));
}

/// <summary>
/// デストラクタ
/// </summary>
ParameterScene::~ParameterScene()
{
	if (m_pTimer             != nullptr) { delete m_pTimer;             m_pTimer             = nullptr; }
	if (m_pTextOfMARIO       != nullptr) { delete m_pTextOfMARIO;       m_pTextOfMARIO       = nullptr; }
	if (m_pTextOfTIME        != nullptr) { delete m_pTextOfTIME;        m_pTextOfTIME        = nullptr; }
	if (m_pTextOfWORLD       != nullptr) { delete m_pTextOfWORLD;       m_pTextOfWORLD       = nullptr; }
	if (m_pTextOfTimeNamber  != nullptr) { delete m_pTextOfTimeNamber;  m_pTextOfTimeNamber  = nullptr; }
	if (m_pImageOfCoin       != nullptr) { delete m_pImageOfCoin;       m_pImageOfCoin       = nullptr; }
	if (m_pTextOfCoinNamber  != nullptr) { delete m_pTextOfCoinNamber;  m_pTextOfCoinNamber  = nullptr; }
	if (m_pTextOfScoreNamber != nullptr) { delete m_pTextOfScoreNamber; m_pTextOfScoreNamber = nullptr; }
	if (m_pTextOfWorldNamber != nullptr) { delete m_pTextOfWorldNamber; m_pTextOfWorldNamber = nullptr; }
}

/// <summary>
/// シーンの更新
/// </summary>
/// <param name="inputFlag"></param>
/// <returns>次のゲームステート</returns>
GameState ParameterScene::UpDateScene(InputFlag inputFlag)
{
	UINT time = m_pTimer->GetCount();
	if (time < 100)
	{
		m_pTextOfTimeNamber->ChangeText("0" + std::to_string(time));
	}
	else
	{
		m_pTextOfTimeNamber->ChangeText(std::to_string(time));
	}
	

	UpDateGame(inputFlag);
	Draw();

	return m_NextGameState;
}

/// <summary>
/// 描画
/// </summary>
void ParameterScene::Draw()
{
	m_pTextOfMARIO      ->Render       ();
	m_pTextOfTIME       ->Render       ();
	m_pTextOfWORLD      ->Render       ();
	m_pTextOfTimeNamber ->Render       ();
	m_pTextOfScoreNamber->Render       ();
	m_pTextOfCoinNamber ->Render       ();
	m_pImageOfCoin      ->ThisObjRender();
	m_pTextOfWorldNamber->Render       ();
}

/// <summary>
/// ステージ番号の表示を変える
/// </summary>
/// <param name="worldNamber">変化後のワールド番号</param>
/// <param name="stageNamber">変化後のステージ番号</param>
void ParameterScene::ChangeWorldNamber(int worldNamber, int stageNamber)
{
	std::string filePas = std::to_string(worldNamber) + "-" + std::to_string(stageNamber);  //ステージのファイルパス

	m_pTextOfWorldNamber->ChangeText(filePas);
}