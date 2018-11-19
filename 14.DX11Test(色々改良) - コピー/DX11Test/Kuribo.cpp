#include"Kuribo.h"
#include"Flag.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="size">サイズ</param>
Kuribo::Kuribo(Vector3 pos, Vector2 size) : Enemy(pos,size)
{
	LoadTexture(L"Texture/KURIBO.png");
	CreateShader(L"Shader/VertexShader.vsh", L"Shader/PixelShader.psh");
	CreateBuffer(m_pVertexArray, m_VertexArraySize, m_pIndexArray, m_IndexArraySize);
}

/// <summary>
/// 
/// </summary>
/// <param name="inputFlag"></param>
void Kuribo::Move(InputFlag* inputFlag)
{

}