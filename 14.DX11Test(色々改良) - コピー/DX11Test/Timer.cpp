#include"Timer.h"
#include<Windows.h>
#include<sstream>
#include<mmsystem.h>

Timer::Timer()
{
	m_TimeStart = 0;
	m_TimeEnd = 0;
}

Timer::~Timer() {}

//前回のフレームと現在のフレームでカウントダウンする
DWORD Timer::GetCount()
{
	if (m_CountFlag)
	{
		//現在の時間を保存
		m_TimeEnd = timeGetTime() / 1000;

		//差分を取得
		DWORD dif = m_TimeEnd - m_TimeStart;

		//０から引くと一周回って値が大きくなるため計算前のを保存
		DWORD oldTimeRemaining = m_TimeRemaining;

		//残り時間から引く
		m_TimeRemaining -= dif;

		//計算前より大きかったら一周回ったということで計測終了、残り時間を０で固定
		if (m_TimeRemaining > oldTimeRemaining)
		{
			CountStop();
			m_TimeRemaining = 0;
			return m_TimeRemaining;
		}

		//現在の時間を次の計測開始時間に設定
		m_TimeStart = m_TimeEnd;

		//残り時間を出力
		std::stringstream stream;
		stream << m_TimeRemaining << std::endl;
		//OutputDebugString(stream.str().c_str());

		return m_TimeRemaining;
	}

	return m_TimeRemaining;
}

//計測を停止
void Timer::CountStop()
{
	m_CountFlag = false;

	m_TimeStart = 0;
	m_TimeEnd   = 0;
}

//計測を始める
DWORD Timer::CountStart()
{
	//今の時間を保存して次のフレームで比較する
	m_TimeStart = timeGetTime() / 1000;
	m_CountFlag = true;
	return m_TimeRemaining;
}