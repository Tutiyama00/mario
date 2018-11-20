#pragma once

#include<string>
#include<d3d11.h>
#include"Math.h"
#include"TextChar.h"

using namespace OriginalMath;

/* �O���錾 */
template<class T> class Characters;

class TextCharacters
{
public:
	TextCharacters(Vector3 pos, Vector2 size, std::string text, LPCWSTR TPS_COLOR);
	~TextCharacters();

	void Render();
	void ChangeText(std::string text);

private:
	Characters<TextChar>* m_pCharacters = nullptr;  //������p�̔z��
	const Vector3 M_POS;        //�����̃|�W�V�����i�擪������j
	const Vector2 M_SIZE;       //�����̃T�C�Y
	const LPCWSTR M_TPS_COLOR;  //�����̐F�i�s�N�Z���V�F�[�_�̃p�X�j
};