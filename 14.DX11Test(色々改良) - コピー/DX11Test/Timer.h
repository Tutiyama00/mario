#pragma once
#include<Windows.h>

class Timer
{
public:
	Timer();
	~Timer();

	DWORD GetCount();
	void  CountStop();
	DWORD CountStart();

public:
	void  SetTimeRemaining(DWORD time) { m_TimeRemaining = time; }

private:
	DWORD m_TimeRemaining = 0;   //残り時間
	DWORD m_TimeStart = 0;     //比較用の前のフレームの時間
	DWORD m_TimeEnd = 0;       //比較用の現在のフレームの時間

	bool m_CountFlag = false;
};