#pragma once

//�O���錾
enum class Object : unsigned char;

class Stage
{
public:
	Stage(const char* stageName);
	~Stage();

public:
	/*�A�N�Z�T�[*/
	int GetStageHeight() { return m_StageHeight; }
	int GetStageWidth()  { return m_StageWidth; }

	Object* m_pStageDataArray; //�X�e�[�W�f�[�^��ۑ�����z��̃|�C���^

private:
	int   m_StageSize;        //�X�e�[�W�z��̒���
	int   m_StageHeight = 13; //�z��̒����i�c�j
	int   m_StageWidth = 0;   //�z��̒����i���j
};