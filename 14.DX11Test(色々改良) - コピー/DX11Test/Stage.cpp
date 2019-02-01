#include<iostream>
#include<fstream>
#include<Windows.h>
#include"Stage.h"
#include"Enum.h"

using namespace std;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="stageName">�X�e�[�W��</param>
Stage::Stage(const char* stageName)
{
	LoadStage(stageName);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
	Delete();
}

/// <summary>
/// �����o�ϐ��̃f���[�g
/// </summary>
void Stage::Delete()
{
	if (m_pStageDataArray != nullptr) { delete[] m_pStageDataArray; m_pStageDataArray = nullptr; }
}

/// <summary>
/// �X�e�[�W�̓ǂݍ���
/// </summary>
/// <param name="stageName">�X�e�[�W�̃t�@�C����</param>
bool Stage::LoadStage(const char* stageName)
{
	//�t�@�C���̃f�[�^���ꎞ�i�[���郍�[�J���ϐ�
	char* loadStageData = nullptr;

	//�����o���I�ϐ���NULL�ŏ�����
	m_pStageDataArray = nullptr;

	//ifstream�̃R���X�g���N�^�Ńt�@�C�����I�[�v������
	ifstream ifs(stageName, ifstream::binary);

	if (ifs.fail())
	{
		return false;
	}

	//�t�@�C���̐擪�ʒu
	int begin = static_cast<int>(ifs.tellg());
	//�����ʒu���Ō���Ɉړ�
	ifs.seekg(0, ifs.end);
	//�t�@�C���̍Ō��
	int end = static_cast<int>(ifs.tellg());
	//�����߂��O�ɃN���A���Ȃ��ƃR�P��Ƃ��Ȃ�Ƃ�
	ifs.clear();
	//�����ʒu��擪�Ɉړ�
	ifs.seekg(0, ifs.beg);
	//�t�@�C���T�C�Y�̌���
	m_StageSize = end - begin;
	//�X�e�[�W�f�[�^���i�[����z��̃C���X�^���X
	loadStageData = new char[m_StageSize];
	if (loadStageData == nullptr)
	{
		MessageBox(NULL, "loadStageData�̃��������m�ۂł��܂���ł����B", "ERROR", MB_OK | MB_ICONERROR);
	}
	m_pStageDataArray = new Object[m_StageSize];
	if (m_pStageDataArray == nullptr)
	{
		MessageBox(NULL, "mStageData�̃��������m�ۂł��܂���ł����B", "ERROR", MB_OK | MB_ICONERROR);
	}

	//�X�e�[�W�f�[�^�̓ǂݍ���
	ifs.read(loadStageData, m_StageSize);

	//�X�e�[�W�̎���
	char* time = new char;
	ifs.seekg(ifs.beg);
	ifs.read(time, 1);
	m_StageTime += atoi(time) * 100;
	ifs.seekg(ifs.beg + 1);
	ifs.read(time, 1);
	m_StageTime += atoi(time) * 10;
	ifs.seekg(ifs.beg + 2);
	ifs.read(time, 1);
	m_StageTime += atoi(time);
	delete time;
	time = nullptr;

	//�X�e�[�W�̕��̎擾
	char* width = new char;  //�X�e�[�W�̕�
	char* digit = new char;  //�X�e�[�W�̕��̌���
	ifs.seekg(ifs.beg + 5);
	ifs.read(digit, 1);
	switch (atoi(digit))
	{
	case 2:
		ifs.seekg(ifs.beg + 8);
		ifs.read(width, 1);
		m_StageWidth += atoi(width) * 10;
		ifs.seekg(ifs.beg + 9);
		ifs.read(width, 1);
		m_StageWidth += atoi(width);
		break;

	case 3:
		ifs.seekg(ifs.beg + 8);
		ifs.read(width, 1);
		m_StageWidth += atoi(width) * 100;
		ifs.seekg(ifs.beg + 9);
		ifs.read(width, 1);
		m_StageWidth += atoi(width) * 10;
		ifs.seekg(ifs.beg + 10);
		ifs.read(width, 1);
		m_StageWidth += atoi(width);
		break;
	}
	delete width;
	width = nullptr;
	delete digit;
	digit = nullptr;

	//�X�e�[�W�f�[�^��Object�^�ɕϊ�
	int pt = 0;
	for (int i = 0; i < m_StageSize; i++)
	{
		switch (loadStageData[i])
		{
		case 'M':m_pStageDataArray[pt] = Object::MARIO;               pt++; break;
		case ' ':m_pStageDataArray[pt] = Object::SPACE;               pt++; break;
		case 'B':m_pStageDataArray[pt] = Object::NORMAL_BLOCK;        pt++; break;
		case 'b':m_pStageDataArray[pt] = Object::NORMAL_BLOCK_DUMMY;  pt++; break;
		case 'H':m_pStageDataArray[pt] = Object::HARD_BLOCK;          pt++; break;
		case 'h':m_pStageDataArray[pt] = Object::HARD_BLOCK_DUMMY;    pt++; break;
		case 'K':m_pStageDataArray[pt] = Object::KURIBOU;             pt++; break;
		case 'N':m_pStageDataArray[pt] = Object::NOKONOKO;            pt++; break;
		case 'G':m_pStageDataArray[pt] = Object::GROUND_BLOCK;        pt++; break;
		case 'g':m_pStageDataArray[pt] = Object::GROUND_BLOCK_DUMMY;  pt++; break;
		case 'C':m_pStageDataArray[pt] = Object::GOAL;                pt++; break;
		case 'p':m_pStageDataArray[pt] = Object::CLAY_PIPE_2;         pt++; break;
		case 'P':m_pStageDataArray[pt] = Object::CLAY_PIPE_3;         pt++; break;
		case 'i':m_pStageDataArray[pt] = Object::CLAY_PIPE_4;         pt++; break;
		}
	}

	//�g���I�����loadStageData�̃f���[�g�i�f���[�g��A������NULL�����Ďg�p���Ă��Ȃ��悤�ɂ���j
	if (loadStageData != nullptr) { delete[] loadStageData; loadStageData = nullptr; }

	return true;
}

/// <summary>
/// �X�e�[�W����ύX����i�w�肵���X�e�[�W���ēǂݍ��݁j
/// </summary>
/// <param name="stageName">�X�e�[�W��</param>
bool Stage::ChangeStage(const char* stageName)
{
	Delete();
	m_StageSize  = 0;
	m_StageWidth = 0;
	m_StageTime  = 0;
	return LoadStage(stageName);
}