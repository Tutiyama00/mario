#include"ResultScene.h"
#include"Image.h"
#include"Enum.h"
#include"Flag.h"
#include"Dx11.h"
#include"TextCharacters.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playerLife">初期プレイヤー残機</param>
ResultScene::ResultScene(UINT playerLife)
{
	m_NextGameState = GameState::RESULT;

	Vector3 pos  = { -0.14f,0.0f,0.0f };
	Vector2 size = { 0.1f,0.1f };

	m_pImageOfMario = new Image(pos, size, L"Texture/Mario.png");

	pos.x  = 0.0f;
	size.x = size.y = 0.07f;
	m_pTextOfMarioLife = new TextCharacters(pos, size, "*  " + std::to_string(playerLife), TPS_WHITE);

	pos.x  = -0.25f;
	pos.y  = 0.2f;
	size.x = size.y = 0.07f;
	m_pTextOfWORLD = new TextCharacters(pos, size, "WORLD", TPS_WHITE);

	pos.x = 0.15f;
	m_pTextOfWorldNamber = new TextCharacters(pos, size, "1-1", TPS_WHITE);
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
	if (m_pImageOfMario      != nullptr) { delete m_pImageOfMario;      m_pImageOfMario      = nullptr; }
	if (m_pTextOfWORLD       != nullptr) { delete m_pTextOfWORLD;       m_pTextOfWORLD       = nullptr; }
	if (m_pTextOfMarioLife   != nullptr) { delete m_pTextOfMarioLife;   m_pTextOfMarioLife   = nullptr; }
	if (m_pTextOfWorldNamber != nullptr) { delete m_pTextOfWorldNamber; m_pTextOfWorldNamber = nullptr; }
}

/// <summary>
/// シーンの更新
/// </summary>
/// <param name="inputFlag"></param>
/// <returns>次のシーン</returns>
GameState ResultScene::UpDateScene(InputFlag inputFlag)
{
	m_NextGameState = GameState::RESULT;

	UpDateGame(inputFlag);
	Draw();

	return m_NextGameState;
}

/// <summary>
/// ゲームの更新
/// </summary>
/// <param name="inputFlag"></param>
void ResultScene::UpDateGame(InputFlag inputFlag)
{
	/* 指定したフレーム数だけシーンを継続する */
	if (m_FlameCount >= M_CHANGE_FLAME_COUNT)
	{
		/* フレーム数カウントのリセット */
		m_FlameCount = 0;
		/* シーンの変更 */
		m_NextGameState = GameState::PLAY;
	}
	else
	{
		/* フレーム数カウント */
		m_FlameCount++;
	}
}

/// <summary>
/// 描画
/// </summary>
void ResultScene::Draw()
{
	m_pImageOfMario     ->ThisObjRender();
	m_pTextOfWORLD      ->Render       ();
	m_pTextOfMarioLife  ->Render       ();
	m_pTextOfWorldNamber->Render       ();
}

/// <summary>
/// ステージ番号表示の変更
/// </summary>
/// <param name="worldNamber">変更後ワールド番号</param>
/// <param name="stageNamber">変更後ステージ番号</param>
void ResultScene::ChangeWorldNamber(int worldNamber, int stageNamber)
{
	std::string filePas = std::to_string(worldNamber) + "-" + std::to_string(stageNamber);  //ステージのファイルパス

	/* ステージ番号表示の変更 */
	m_pTextOfWorldNamber->ChangeText(filePas);
}

/// <summary>
/// プレイヤーの残機の表示の変更
/// </summary>
/// <param name="playerLife">変更後のプレイヤーの残機</param>
void ResultScene::ChangeMarioLife(UINT playerLife)
{
	m_pTextOfMarioLife->ChangeText("*  " + std::to_string(playerLife));
}