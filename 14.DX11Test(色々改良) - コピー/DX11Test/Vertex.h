#pragma once
#include<d3d11.h>

//頂点構造体
struct vertex
{
	float pos[3];
	float tex[2];
};

//###################    Polygon   ##############################

//抽象クラス
class Polygon
{
public:
	virtual void Abstract() = 0;  //純粋仮想関数（これによってこのクラスはインスタンスできない)
	virtual ~Polygon();           //デストラクタ←ここでカラ定義

public:
	UINT    m_VertexArraySize;  //頂点配列の要素数
	UINT    m_IndexArraySize;   //インデックス配列の要素数
	vertex* m_pVertexArray = nullptr;     //頂点配列
    WORD*   m_pIndexArray  = nullptr;     //インデックス配列

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
	Square(float xPos, float yPos, float zPos,float xSize, float ySize);

	//デストラクタ
	~Square();

	virtual bool CollisionCheck(Polygon* checkPolygon); //衝突判定

private:

	float m_DiagonalLength = 0; //この四角形の対角線の長さ
};


//###################    Triangle   ##############################

class Triangle : public Polygon
{
public:
	void Abstract();  //抽象クラス化のための純粋仮想関数をここで定義する←このクラスが抽象クラスだと判断されないために

	//コンストラクタ
	Triangle(float xPos, float yPos, float zPos, float xSize, float ySize);

	//デストラクタ
	~Triangle();
};