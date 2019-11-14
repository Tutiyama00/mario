#pragma once

//�O���錾
enum class Object : unsigned char;

class Stage
{
public:
	Stage(const char* stageName);
	~Stage();

	bool ChangeStage(const char* stageName);

public:
	/* getter */
	const int GetStageHeight() { return M_STAGE_HEIGHT; }
	int       GetStageWidth()  { return m_StageWidth;   }
	DWORD     GetStageTime()   { return m_StageTime;    }

public:
	Object* m_pStageDataArray; //�X�e�[�W�f�[�^��ۑ�����z��̃|�C���^

private:
	bool LoadStage(const char* stageName); //�X�e�[�W�̓ǂݍ���
	void Delete();  //�����o�ϐ���delete
private:
	int         m_StageSize    = 0;  //�X�e�[�W�z��̒���
	const int   M_STAGE_HEIGHT = 17; //�z��̒����i�c�j
	int         m_StageWidth   = 0;  //�z��̒����i���j
	DWORD       m_StageTime    = 0;  //�X�e�[�W�̃^�C��  
};