#pragma once
#include<d3d11.h>
#include"Interface.h"

//���_�\����
struct vertex
{
	float pos[3];
	float tex[2];
};

//###################    Polygon   ##############################

//���ۃN���X
class Polygon
{
public:
	virtual void Abstract() = 0;  //�������z�֐��i����ɂ���Ă��̃N���X�̓C���X�^���X�ł��Ȃ�)
	virtual ~Polygon();           //�f�X�g���N�^�������ŃJ����`

public:
	UINT    m_VertexArraySize;  //���_�z��̗v�f��
	UINT    m_IndexArraySize;   //�C���f�b�N�X�z��̗v�f��
	vertex* m_pVertexArray = nullptr;     //���_�z��
    WORD*   m_pIndexArray  = nullptr;      //�C���f�b�N�X�z��

	float m_xPos;  //X���W
	float m_yPos;  //Y���W
	float m_zPos;  //Z���W
	float m_xSize; //X�T�C�Y
	float m_ySize; //Y�T�C�Y
};


//###################    Square   ##############################

class Square : public Polygon
{
public:
	void Abstract();  //���ۃN���X���̂��߂̏������z�֐��������Œ�`���適���̃N���X�����ۃN���X���Ɣ��f����Ȃ����߂�

	//�R���X�g���N�^
	Square(float xPos, float yPos, float zPos,float xSize, float ySize);

	//�f�X�g���N�^
	~Square();

	virtual bool CollisionCheck(Polygon* checkPolygon); //�Փ˔���

private:

	float m_DiagonalLength = 0; //���̎l�p�`�̑Ίp���̒���
};


//###################    Triangle   ##############################

class Triangle : public Polygon
{
public:
	void Abstract();  //���ۃN���X���̂��߂̏������z�֐��������Œ�`���適���̃N���X�����ۃN���X���Ɣ��f����Ȃ����߂�

	//�R���X�g���N�^
	Triangle(float xPos, float yPos, float zPos, float xSize, float ySize);

	//�f�X�g���N�^
	~Triangle();
};