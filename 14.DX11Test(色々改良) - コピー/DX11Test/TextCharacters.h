#pragma once

#include<string>
#include<d3d11.h>
#include"Math.h"
#include"TextChar.h"

using namespace OriginalMath;

/* 前方宣言 */
template<class T> class Characters;

class TextCharacters
{
public:
	TextCharacters(Vector3 pos, Vector2 size, std::string text, LPCWSTR TPS_COLOR);
	~TextCharacters();

	void Render();
	void ChangeText(std::string text);

private:
	Characters<TextChar>* m_pCharacters = nullptr;  //文字列用の配列
	const Vector3 M_POS;        //文字のポジション（先頭文字基準）
	const Vector2 M_SIZE;       //文字のサイズ
	const LPCWSTR M_TPS_COLOR;  //文字の色（ピクセルシェーダのパス）
};