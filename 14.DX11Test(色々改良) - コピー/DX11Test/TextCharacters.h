#pragma once

#include<string>
#include<d3d11.h>
#include"Math.h"
#include"TextChar.h"

using namespace OriginalMath;

template<class T> class Characters;

class TextCharacters
{
public:
	TextCharacters(Vector3 pos, Vector2 size, std::string text, ID3D11Device* pDevice,LPCWSTR TPS_COLOR);
	~TextCharacters();

	void Render(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ChangeText(std::string text,ID3D11Device* pDevice);

private:
	Characters<TextChar>* m_pCharacters = nullptr;
	const Vector3 M_POS;
	const Vector2 M_SIZE;
	const LPCWSTR M_TPS_COLOR;
};