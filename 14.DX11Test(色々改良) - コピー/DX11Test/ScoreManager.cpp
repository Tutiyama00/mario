#include"ScoreManager.h"

/// <summary>
/// スコア加算
/// </summary>
/// <param name="point">増やすポイント</param>
void ScoreManager::AddScore(int point)
{
	m_NowScoreAmount += point;
}

/// <summary>
/// スコアのリセット
/// </summary>
void ScoreManager::ScoreReSet()
{
	m_NowScoreAmount = 0;
}