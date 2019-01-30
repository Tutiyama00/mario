#pragma once
#include<d3d11.h>
#include"Math.h"

using namespace OriginalMath;

//���_�\����
struct vertex
{
	Vector3 pos;
	Vector2 tex;
	float col[4];
};

//###################    Polygon   ##############################

//���ۃN���X
class Polygon
{
public:
	virtual void Abstract() = 0;  //�������z�֐��i����ɂ���Ă��̃N���X�̓C���X�^���X�ł��Ȃ�)
	virtual ~Polygon() {};        //�f�X�g���N�^�������ŃJ����`

	void VertexMove(float xAmount, float yAmount);

public:
	/*getter*/
	float GetxPos() { return m_xPos; }
	float GetyPos() { return m_yPos; }
	float GetxSize() { return m_xSize; }
	float GetySize() { return m_ySize; }
	UINT GetVertexArraySize() { return m_VertexArraySize; }
	UINT GetIndexArraySize () { return m_IndexArraySize;  }

public:
	vertex* m_pVertexArray = nullptr;  //���_�z��
	WORD*   m_pIndexArray  = nullptr;  //�C���f�b�N�X�z��

protected:
	UINT    m_VertexArraySize;         //���_�z��̗v�f��
	UINT    m_IndexArraySize;          //�C���f�b�N�X�z��̗v�f��

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
	Square(Vector3 pos,Vector2 size);

	//�f�X�g���N�^
	~Square();

	virtual bool CollisionCheck(Polygon* checkPolygon); //�Փ˔���
	virtual bool CollisionCheck(Polygon* checkPolygon, float threshold); //�Փ˔���

protected:
	void ParallelInverted();  //���s�ɔ��]������
	bool AABBCheck(Vector3 leftUpVertex, Vector3 rightDownVertex, Vector3 targetVertex, float threshold);  //AABB�����A�Փ˔���Ŏg��

protected:
	float m_ColAdjustedValue     = 0.0f;   //�Փ˂̒����l(�������肪�L���Ȃ�A�������肪�����Ȃ�)
	bool  m_ParallelInvertedFlag = false;  //���s���]�����Ă���̂��̃t���O
	float m_DiagonalLength       = 0.0f;   //���̎l�p�`�̑Ίp���̒���
};