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
	/* getter */
	bool GetCountFlag() { return m_CountFlag; }
	/* setter */
	void SetTimeRemaining(DWORD time) { m_TimeRemaining = time; }

private:
	DWORD m_TimeRemaining = 0;  //�c�莞��
	DWORD m_TimeStart = 0;      //��r�p�̑O�̃t���[���̎���
	DWORD m_TimeEnd = 0;        //��r�p�̌��݂̃t���[���̎���

	bool m_CountFlag = false;
};