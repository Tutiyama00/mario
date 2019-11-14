#pragma once

//前方宣言
enum class Object : unsigned char;

class Stage
{
public:
	Stage(const char* stageName);
	~Stage();

	bool ChangeStage(const char* stageName);

public:
	/* getter */
	const int GetStageHeight() { return M_STAGE_HEIGHT; }
	int       GetStageWidth()  { return m_StageWidth;   }
	DWORD     GetStageTime()   { return m_StageTime;    }

public:
	Object* m_pStageDataArray; //ステージデータを保存する配列のポインタ

private:
	bool LoadStage(const char* stageName); //ステージの読み込み
	void Delete();  //メンバ変数のdelete
private:
	int         m_StageSize    = 0;  //ステージ配列の長さ
	const int   M_STAGE_HEIGHT = 17; //配列の長さ（縦）
	int         m_StageWidth   = 0;  //配列の長さ（幅）
	DWORD       m_StageTime    = 0;  //ステージのタイム  
};