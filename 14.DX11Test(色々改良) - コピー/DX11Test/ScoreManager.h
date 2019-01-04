#pragma once

#include"Singleton.h"

#define NOKONOKO_SCORE 200
#define KURIBO_SCORE 100

class ScoreManager : public Singleton<ScoreManager>
{
public:
	friend class Singleton<ScoreManager>;

public:
	void AddScore(int point);
	void ScoreReSet();

public:
	/* getter */
	int GetNowScoreAmount() { return m_NowScoreAmount; }

private:
	int m_NowScoreAmount = 0;  //現在のスコア

private:
	ScoreManager() {};  //コンストラクタ
	ScoreManager(const ScoreManager &scoreManager) {};  //コピーコンストラクタ
	~ScoreManager() {};    //デストラクタ

/*------Singleton------*/
protected:
	bool m_InitializedFlag = false;  //初期化しているかのフラグ（True＝初期化済み、False＝未初期化）

protected:
	void Abstract() {};
};