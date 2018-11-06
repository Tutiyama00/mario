#pragma once

//前方宣言
enum class Object : unsigned char;

class Stage
{
public:
	Stage(const char* stageName);
	~Stage();

public:
	/*アクセサー*/
	int GetStageHeight() { return m_StageHeight; }
	int GetStageWidth()  { return m_StageWidth; }

	Object* m_pStageDataArray; //ステージデータを保存する配列のポインタ

private:
	int   m_StageSize;        //ステージ配列の長さ
	int   m_StageHeight = 17; //配列の長さ（縦）
	int   m_StageWidth = 0;   //配列の長さ（幅）
};