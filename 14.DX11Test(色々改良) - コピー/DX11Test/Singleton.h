#pragma once

template<class T> class  Singleton
{
public:
	static T* Instance()
	{
		static T obj;
		return &obj;
	}

	virtual void Initialize(HWND hwnd) = 0; //初期化関数

protected:
	bool m_InitializedFlag;  //初期化しているかのフラグ（True＝初期化済み、False＝未初期化）

protected:
	virtual void Abstract() = 0;  //純粋仮想関数（これによってこのクラスはインスタンスできない)
};
