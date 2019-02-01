#include<iostream>
#include<fstream>
#include<Windows.h>
#include"Stage.h"
#include"Enum.h"

using namespace std;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stageName">ステージ名</param>
Stage::Stage(const char* stageName)
{
	LoadStage(stageName);
}

/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
	Delete();
}

/// <summary>
/// メンバ変数のデリート
/// </summary>
void Stage::Delete()
{
	if (m_pStageDataArray != nullptr) { delete[] m_pStageDataArray; m_pStageDataArray = nullptr; }
}

/// <summary>
/// ステージの読み込み
/// </summary>
/// <param name="stageName">ステージのファイル名</param>
bool Stage::LoadStage(const char* stageName)
{
	//ファイルのデータを一時格納するローカル変数
	char* loadStageData = nullptr;

	//メンバ動的変数をNULLで初期化
	m_pStageDataArray = nullptr;

	//ifstreamのコンストラクタでファイルをオープンする
	ifstream ifs(stageName, ifstream::binary);

	if (ifs.fail())
	{
		return false;
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
		MessageBox(NULL, "loadStageDataのメモリを確保できませんでした。", "ERROR", MB_OK | MB_ICONERROR);
	}
	m_pStageDataArray = new Object[m_StageSize];
	if (m_pStageDataArray == nullptr)
	{
		MessageBox(NULL, "mStageDataのメモリを確保できませんでした。", "ERROR", MB_OK | MB_ICONERROR);
	}

	//ステージデータの読み込み
	ifs.read(loadStageData, m_StageSize);

	//ステージの時間
	char* time = new char;
	ifs.seekg(ifs.beg);
	ifs.read(time, 1);
	m_StageTime += atoi(time) * 100;
	ifs.seekg(ifs.beg + 1);
	ifs.read(time, 1);
	m_StageTime += atoi(time) * 10;
	ifs.seekg(ifs.beg + 2);
	ifs.read(time, 1);
	m_StageTime += atoi(time);
	delete time;
	time = nullptr;

	//ステージの幅の取得
	char* width = new char;  //ステージの幅
	char* digit = new char;  //ステージの幅の桁数
	ifs.seekg(ifs.beg + 5);
	ifs.read(digit, 1);
	switch (atoi(digit))
	{
	case 2:
		ifs.seekg(ifs.beg + 8);
		ifs.read(width, 1);
		m_StageWidth += atoi(width) * 10;
		ifs.seekg(ifs.beg + 9);
		ifs.read(width, 1);
		m_StageWidth += atoi(width);
		break;

	case 3:
		ifs.seekg(ifs.beg + 8);
		ifs.read(width, 1);
		m_StageWidth += atoi(width) * 100;
		ifs.seekg(ifs.beg + 9);
		ifs.read(width, 1);
		m_StageWidth += atoi(width) * 10;
		ifs.seekg(ifs.beg + 10);
		ifs.read(width, 1);
		m_StageWidth += atoi(width);
		break;
	}
	delete width;
	width = nullptr;
	delete digit;
	digit = nullptr;

	//ステージデータをObject型に変換
	int pt = 0;
	for (int i = 0; i < m_StageSize; i++)
	{
		switch (loadStageData[i])
		{
		case 'M':m_pStageDataArray[pt] = Object::MARIO;               pt++; break;
		case ' ':m_pStageDataArray[pt] = Object::SPACE;               pt++; break;
		case 'B':m_pStageDataArray[pt] = Object::NORMAL_BLOCK;        pt++; break;
		case 'b':m_pStageDataArray[pt] = Object::NORMAL_BLOCK_DUMMY;  pt++; break;
		case 'K':m_pStageDataArray[pt] = Object::KURIBOU;             pt++; break;
		case 'N':m_pStageDataArray[pt] = Object::NOKONOKO;            pt++; break;
		case 'G':m_pStageDataArray[pt] = Object::GROUND_BLOCK;        pt++; break;
		case 'g':m_pStageDataArray[pt] = Object::GROUND_BLOCK_DUMMY;  pt++; break;
		case 'C':m_pStageDataArray[pt] = Object::GOAL;                pt++; break;
		case 'p':m_pStageDataArray[pt] = Object::CLAY_PIPE_2;         pt++; break;
		case 'P':m_pStageDataArray[pt] = Object::CLAY_PIPE_3;         pt++; break;
		case 'i':m_pStageDataArray[pt] = Object::CLAY_PIPE_4;         pt++; break;
		}
	}

	//使い終わったloadStageDataのデリート（デリート後、すぐにNULLを入れて使用していないようにする）
	if (loadStageData != nullptr) { delete[] loadStageData; loadStageData = nullptr; }

	return true;
}

/// <summary>
/// ステージ情報を変更する（指定したステージを再読み込み）
/// </summary>
/// <param name="stageName">ステージ名</param>
bool Stage::ChangeStage(const char* stageName)
{
	Delete();
	m_StageSize  = 0;
	m_StageWidth = 0;
	m_StageTime  = 0;
	return LoadStage(stageName);
}