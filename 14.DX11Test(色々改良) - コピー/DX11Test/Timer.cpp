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

//�O��̃t���[���ƌ��݂̃t���[���ŃJ�E���g�_�E������
DWORD Timer::GetCount()
{
	if (m_CountFlag)
	{
		//���݂̎��Ԃ�ۑ�
		m_TimeEnd = timeGetTime() / 1000;

		//�������擾
		DWORD dif = m_TimeEnd - m_TimeStart;

		//�O��������ƈ������Ēl���傫���Ȃ邽�ߌv�Z�O�̂�ۑ�
		DWORD oldTimeRemaining = m_TimeRemaining;

		//�c�莞�Ԃ������
		m_TimeRemaining -= dif;

		//�v�Z�O���傫����������������Ƃ������ƂŌv���I���A�c�莞�Ԃ��O�ŌŒ�
		if (m_TimeRemaining > oldTimeRemaining)
		{
			CountStop();
			m_TimeRemaining = 0;
			return m_TimeRemaining;
		}

		//���݂̎��Ԃ����̌v���J�n���Ԃɐݒ�
		m_TimeStart = m_TimeEnd;

		//�c�莞�Ԃ��o��
		//std::stringstream stream;
		//stream << m_TimeRemaining << std::endl;
		//OutputDebugString(stream.str().c_str());

		return m_TimeRemaining;
	}

	return m_TimeRemaining;
}

//�v�����~
void Timer::CountStop()
{
	m_CountFlag = false;

	m_TimeStart = 0;
	m_TimeEnd   = 0;
}

//�v�����n�߂�
DWORD Timer::CountStart()
{
	//���̎��Ԃ�ۑ����Ď��̃t���[���Ŕ�r����
	m_TimeStart = timeGetTime() / 1000;
	m_CountFlag = true;
	return m_TimeRemaining;
}