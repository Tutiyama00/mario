#pragma once
#include<d3d11.h>
#include"Math.h"

using namespace OriginalMath;

//頂点構造体
struct vertex
{
	Vector3 pos;
	Vector2 tex;
	float col[4];
};

//###################    Polygon   ##############################

//抽象クラス
class Polygon
{
public:
	virtual void Abstract() = 0;  //純粋仮想関数（これによってこのクラスはインスタンスできない)
	virtual ~Polygon() {};        //デストラクタ←ここでカラ定義

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
	vertex* m_pVertexArray = nullptr;  //頂点配列
	WORD*   m_pIndexArray  = nullptr;  //インデックス配列

protected:
	UINT    m_VertexArraySize;         //頂点配列の要素数
	UINT    m_IndexArraySize;          //インデックス配列の要素数

	float m_xPos;  //X座標
	float m_yPos;  //Y座標
	float m_zPos;  //Z座標
	float m_xSize; //Xサイズ
	float m_ySize; //Yサイズ
};


//###################    Square   ##############################

class Square : public Polygon
{
public:
	void Abstract();  //抽象クラス化のための純粋仮想関数をここで定義する←このクラスが抽象クラスだと判断されないために

	//コンストラクタ
	Square(Vector3 pos,Vector2 size);

	//デストラクタ
	~Square();

	virtual bool CollisionCheck(Polygon* checkPolygon); //衝突判定
	virtual bool CollisionCheck(Polygon* checkPolygon, float threshold); //衝突判定

protected:
	void ParallelInverted();  //平行に反転させる
	bool AABBCheck(Vector3 leftUpVertex, Vector3 rightDownVertex, Vector3 targetVertex, float threshold);  //AABB方式、衝突判定で使う

protected:
	float m_ColAdjustedValue     = 0.0f;   //衝突の調整値(正＝判定が広くなる、負＝判定が狭くなる)
	bool  m_ParallelInvertedFlag = false;  //平行反転させているのかのフラグ
	float m_DiagonalLength       = 0.0f;   //この四角形の対角線の長さ
};