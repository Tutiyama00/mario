#pragma once

template<class T> class  Singleton
{
public:
	static T* Instance()
	{
		static T obj;
		return &obj;
	}

protected:
	bool m_InitializedFlag;  //���������Ă��邩�̃t���O�iTrue���������ς݁AFalse�����������j

protected:
	virtual void Abstract() = 0;  //�������z�֐��i����ɂ���Ă��̃N���X�̓C���X�^���X�ł��Ȃ�)
};
