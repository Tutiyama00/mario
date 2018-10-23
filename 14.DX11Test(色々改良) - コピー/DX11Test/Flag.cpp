#include"Flag.h"


using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
InputFlag::InputFlag():mFlags(0) {};

/// <summary>
/// デストラクタ
/// </summary>
InputFlag::~InputFlag() {};

/// <summary>
/// 指定のフラグの状態チェック
/// </summary>
/// <param name="flagCode">指定フラグ</param>
/// <returns></returns>
bool InputFlag::Check(InputFlagCode flagCode) 
{
	return (mFlags & static_cast<unsigned char>(flagCode)) != 0;
}

/// <summary>
/// 指定のフラグを立てる
/// </summary>
/// <param name="flagCode">指定フラグ</param>
void InputFlag::Set(InputFlagCode flagCode)
{
	mFlags |= static_cast<unsigned char>(flagCode);
}

/// <summary>
/// 指定のフラグを降ろす
/// </summary>
/// <param name="flagCode">指定フラグ</param>
void InputFlag::ReSet(InputFlagCode flagCode) 
{
	mFlags &= ~static_cast<unsigned char>(flagCode);
}

//フラグをすべて降ろす
void InputFlag::AllReSet()
{
	mFlags = 0;
}