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
	int m_NowScoreAmount = 0;  //���݂̃X�R�A

private:
	ScoreManager() {};  //�R���X�g���N�^
	ScoreManager(const ScoreManager &scoreManager) {};  //�R�s�[�R���X�g���N�^
	~ScoreManager() {};    //�f�X�g���N�^

/*------Singleton------*/
protected:
	bool m_InitializedFlag = false;  //���������Ă��邩�̃t���O�iTrue���������ς݁AFalse�����������j

protected:
	void Abstract() {};
};