#include<iostream>
#include<fstream>
#include<Windows.h>
#include"Stage.h"
#include"Enum.h"

using namespace std;


/// <summary>
/// Stageコンストラクタ
/// </summary>
/// <param name="stageName">ステージ名</param>
/// <param name="stageH">ステージの高さ</param>
/// <param name="stageW">ステージの幅</param>
Stage::Stage(const char* stageName, HWND hwnd)
{
	//ファイルのデータを一時格納するローカル変数
	char* loadStageData = nullptr;

	//メンバ動的変数をNULLで初期化
	m_pStageDataArray = nullptr;

	//ifstreamのコンストラクタでファイルをオープンする
	ifstream ifs(stageName, ifstream::binary);

	if (ifs.fail())
	{
		MessageBox(hwnd, "ファイルのオープンに失敗しました。", "ERROR", MB_OK | MB_ICONERROR);
	}

	//ファイルの先頭位置
	int begin = static_cast<int>(ifs.tellg());
	//調査位置を最後尾に移動
	ifs.seekg(0, ifs.end);
	//ファイルの最後尾
	int end = static_cast<int>(ifs.tellg());
	//巻き戻し前にクリアしないとコケるとかなんとか
	ifs.clear();
	//調査位置を先頭に移動
	ifs.seekg(0, ifs.beg);
	//ファイルサイズの決定
	m_StageSize = end - begin;
	//ステージデータを格納する配列のインスタンス
	loadStageData = new char[m_StageSize];
	if (loadStageData == nullptr)
	{
		MessageBox(hwnd, "loadStageDataのメモリを確保できませんでした。", "ERROR", MB_OK | MB_ICONERROR);
	}
	m_pStageDataArray = new Object[m_StageSize];
	if (m_pStageDataArray == nullptr)
	{
		MessageBox(hwnd, "mStageDataのメモリを確保できませんでした。", "ERROR", MB_OK | MB_ICONERROR);
	}

	//ステージデータの読み込み
	ifs.read(loadStageData, m_StageSize);

	//ステージの幅の取得
	char* width = new char;
	ifs.seekg(ifs.beg);
	ifs.read(width, 1);
	m_StageWidth += atoi(width) * 10;
	ifs.seekg(ifs.beg + 1);
	ifs.read(width, 1);
	m_StageWidth += atoi(width);
	delete width;
	width = nullptr;

	//ステージデータをObject型に変換
	int pt = 0;
	for (int i = 0; i < m_StageSize; i++)
	{
		switch (loadStageData[i])
		{
		case 'M':m_pStageDataArray[pt] = Object::MARIO;           pt++; break;
		case ' ':m_pStageDataArray[pt] = Object::SPACE;           pt++; break;
		case 'B':m_pStageDataArray[pt] = Object::NORMAL_BLOCK;    pt++; break;
		case 'K':m_pStageDataArray[pt] = Object::KURIBOU;         pt++; break;
		}
	}

	//使い終わったloadStageDataのデリート（デリート後、すぐにNULLを入れて使用していないようにする）
	if (loadStageData != nullptr) { delete[] loadStageData; loadStageData = nullptr; }
}

/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
	if (m_pStageDataArray != nullptr) { delete[] m_pStageDataArray; m_pStageDataArray = nullptr; }
}