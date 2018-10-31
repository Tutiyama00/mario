#include"TextCharacters.h"
#include"Characters.h"
#include"TextChar.h"

TextCharacters::TextCharacters(Vector3 pos, Vector2 size,std::string text, ID3D11Device* pDevice,  LPCWSTR TPS_COLOR)
{
	m_pCharacters = new Characters<TextChar>(pDevice, L"Texture/DOT_FONT.png", L"Shader/TextVertexShader.vsh", TPS_COLOR);

	int textSize = text.size();

	for (int i = 0; i < textSize; i++)
	{
		m_pCharacters->m_ObjectVector.push_back(new TextChar(pos, size, pDevice, TPS_COLOR, text[i]));
		pos.x += size.x;
	}

	m_pCharacters->ThisObjCreateBuffer(pDevice);
}

TextCharacters::~TextCharacters()
{
	if (m_pCharacters != nullptr) { delete m_pCharacters; m_pCharacters = nullptr; }
}

void TextCharacters::Render(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets)
{
	m_pCharacters->ThisObjRender(pDeviceContext, strides, offsets);
}