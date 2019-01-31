#include<crtdbg.h>
#include <Windows.h>
#include"Vertex.h"
#include"GameManager.h"
#include<sstream>

HWND  g_hwnd               = nullptr;
const UINT G_WINDOW_WIDTH  = 1000;
const UINT G_WINDOW_HEIGHT = 750;
MSG   g_msg = {0};
char* g_baseClassName = (char*)"Base_Window";

const float G_MIN_FREAM_TIME = 1.0f / 60;
float g_frameTime = 0;
LARGE_INTEGER g_timeStart;
LARGE_INTEGER g_timeEnd;
LARGE_INTEGER g_timeFrequency;
float g_fps = 0;
DWORD g_sleepTime = 0;

//ウィンドウプロシージャ
LRESULT CALLBACK BaseWindProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT MainLoop();
void FrameControl();

/*
hInstance　　 = 現在のインスタンスのハンドル
hInstancePrev = 以前のインスタンスのハンドル
pCmdLine      = コマンドライン(実行ファイルのパスとかデータファイルのパスが入る)
nCmdShow      = ウィンドウの表示状態
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow)
{
	//メモリリーク検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//ウィンドウクラス構造体の設定
	WNDCLASSEX wc = { 0 };
	wc.cbSize               = sizeof(wc);                          //WNDCLASSEX構造体のサイズ
	wc.style                = CS_HREDRAW | CS_VREDRAW;             //ウィンドウスタイル
	wc.lpfnWndProc          = BaseWindProc;                        //ウィンドウプロシージャのアドレス
	wc.cbClsExtra           = 0;                                   //クラス構造体、ウィンドウ構造体の追加領域をバイト単位で予約するもの↓
	wc.cbWndExtra           = 0;                                   //↑通常は０を指定する
	wc.hInstance            = hInstance;                           //WinMain()のインスタンスハンドル
	wc.hIcon                = LoadIcon(nullptr, IDI_APPLICATION);  //使用するアイコンのハンドル
	wc.hCursor              = LoadCursor(nullptr, IDC_ARROW);      //使用するマウスカーソルのハンドル
	wc.hbrBackground        = (HBRUSH)(COLOR_BACKGROUND);          //ウィンドウのクライアント領域の背景色
	wc.lpszMenuName         = nullptr;                             //メニュー
	wc.lpszClassName        = g_baseClassName;                     //このウィンドウクラスの名前
	wc.hIconSm              = nullptr;                             //使用する小さいアイコン

	//ウィンドウクラス構造体の登録
	if (!RegisterClassEx(&wc)) { return -1; }

	//ウィンドウの作成
	g_hwnd = CreateWindowEx(
		WS_EX_LEFT,             //拡張ウィンドウスタイル
		g_baseClassName,        //登録されているウィンドウクラス名
		"テスト",               //作成するウィンドウの名前
		WS_OVERLAPPEDWINDOW,    //ウィンドウスタイル
		0,                      //ウィンドウの横方向の位置
		0,                      //ウィンドウの縦方向の位置
		G_WINDOW_WIDTH,         //ウィンドウの幅
		G_WINDOW_HEIGHT,        //ウィンドウの高さ
		0,                      //親ウィンドウまたはオーナーウィンドウのハンドル
		0,                      //メニューハンドルまたは子識別子
		hInstance,              //アプリケーションインスタンスのハンドル
		0                       //ウィンドウ作成データ
	);

	//ウィンドウが正しく作成されたかチェック
	if (g_hwnd == NULL) { return -1; }

	//ウィンドウの表示
	ShowWindow(g_hwnd, SW_SHOW);

	//ゲームマネージャーの初期化
	GameManager::Instance()->Initialize(g_hwnd);

	//フレーム制御処理
	QueryPerformanceFrequency(&g_timeFrequency);  //更新頻度の取得
	QueryPerformanceCounter(&g_timeStart);  //初回計算用に1度現在時間を取得

	//メッセージループの開始
	while (true)
	{
		if (!MainLoop())
		{
			break;
		}
	}

	return g_msg.wParam;
}

HRESULT MainLoop()
{
	FrameControl();

	//メッセージがあるかないかチェック
	if (PeekMessage(&g_msg, NULL, 0, 0, PM_NOREMOVE))
	{
		//メッセージの取得
		if (GetMessage(&g_msg, NULL, 0, 0))
		{
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);
		}
		else
		{
			return FALSE;
		}
	}
	GameManager::Instance()->InputGet();
	GameManager::Instance()->UpDateGame();
	return TRUE;
}

//ベースウィンドウプロシージャ
LRESULT CALLBACK BaseWindProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//フレーム制御
void FrameControl()
{
	//比較用に現在時刻の取得
	QueryPerformanceCounter(&g_timeEnd);

	//秒単位でフレーム間の秒数取得
	g_frameTime = (float)(g_timeEnd.QuadPart - g_timeStart.QuadPart) / (float)(g_timeFrequency.QuadPart);

	//設定した最低フレーム間秒より短いかどうかの比較
	if (g_frameTime < G_MIN_FREAM_TIME)
	{
		//OutputDebugString("sleep\n");

		//ミリ秒に変換する←Sleep()はミリ秒設定なので
		g_sleepTime = (DWORD)((G_MIN_FREAM_TIME - g_frameTime) * 1000);

		timeBeginPeriod(1);  //分解能を上げる（こうしないとSleep()の精度はガタガタ？）
		Sleep(g_sleepTime);
		timeEndPeriod(1);    //分解能戻す

		return;
	}

	if (g_frameTime > 0.0) { // 経過時間が0より大きい(こうしないと下の計算でゼロ除算になると思われ)
		g_fps = (g_fps*0.99f) + (0.01f / g_frameTime); // 平均fpsを計算
#ifdef _DEBUG
// デバッグ用(デバッガにFSP出す)
#ifdef UNICODE
		std::wstringstream stream;
#else
		std::stringstream stream;
#endif
		stream << g_fps << " FPS" << std::endl;
		//カウンタ付けて10回に1回出力、とかにしないと見づらいかもね
		//OutputDebugString(stream.str().c_str());
#endif  //_DEBUG
	}

	g_timeStart = g_timeEnd;
}