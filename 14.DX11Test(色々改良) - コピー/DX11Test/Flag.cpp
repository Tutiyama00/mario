#include"Flag.h"


using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
InputFlag::InputFlag():mFlags(0) {};

/// <summary>
/// �f�X�g���N�^
/// </summary>
InputFlag::~InputFlag() {};

/// <summary>
/// �w��̃t���O�̏�ԃ`�F�b�N
/// </summary>
/// <param name="flagCode">�w��t���O</param>
/// <returns></returns>
bool InputFlag::Check(InputFlagCode flagCode) 
{
	return (mFlags & static_cast<unsigned char>(flagCode)) != 0;
}

/// <summary>
/// �w��̃t���O�𗧂Ă�
/// </summary>
/// <param name="flagCode">�w��t���O</param>
void InputFlag::Set(InputFlagCode flagCode)
{
	mFlags |= static_cast<unsigned char>(flagCode);
}

/// <summary>
/// �w��̃t���O���~�낷
/// </summary>
/// <param name="flagCode">�w��t���O</param>
void InputFlag::ReSet(InputFlagCode flagCode) 
{
	mFlags &= ~static_cast<unsigned char>(flagCode);
}

//�t���O�����ׂč~�낷
void InputFlag::AllReSet()
{
	mFlags = 0;
}