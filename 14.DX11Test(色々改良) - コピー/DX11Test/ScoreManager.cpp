#include"ScoreManager.h"

/// <summary>
/// �X�R�A���Z
/// </summary>
/// <param name="point">���₷�|�C���g</param>
void ScoreManager::AddScore(int point)
{
	m_NowScoreAmount += point;
}

/// <summary>
/// �X�R�A�̃��Z�b�g
/// </summary>
void ScoreManager::ScoreReSet()
{
	m_NowScoreAmount = 0;
}