#include"TextCharacters.h"
#include"Characters.h"
#include"TextChar.h"

TextCharacters::TextCharacters(Vector3 pos, Vector2 size,std::string text, ID3D11Device* pDevice,  LPCWSTR TPS_COLOR) : M_POS(pos), M_SIZE(size), M_TPS_COLOR(TPS_COLOR)
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

//�\�����镶���̕ύX
void TextCharacters::ChangeText(std::string text,ID3D11Device* pDevice)
{
	//�e�X�̃T�C�Y�̕ۑ�
	int objSize  = m_pCharacters->m_ObjectVector.size();
	int newTextSize = text.size();

	Vector3 setPos = M_POS;

	//���̕����ƐV���������͂ǂ��炪������������
	if (newTextSize <= objSize)
	{
		//�V���������̕����Z�������ꍇ

		//���������for������
		for (int i = 0; i < objSize; i++)
		{
			//�\���������������܂����邩�ǂ���
			if (i >= newTextSize)
			{
				//�Ȃ�������]���ȃI�u�W�F�N�g��delete����
				if (m_pCharacters->m_ObjectVector[i] != nullptr) 
				{
					delete m_pCharacters->m_ObjectVector[i];
					m_pCharacters->m_ObjectVector[i] = nullptr; 
				}
			}
			else
			{
				//�������當����ς���
				m_pCharacters->m_ObjectVector[i]->CherTexSet(text[i]);
			}
		}

		//�������̗]���ȕ���z�񂩂��������
		while (m_pCharacters->m_ObjectVector.back() == nullptr)
		{
			m_pCharacters->m_ObjectVector.pop_back();
		}
	}
	else
	{
		//�V���������̕������������ꍇ

		//���������for������
		for (int i = 0; i < newTextSize ; i++)
		{
			//objSize�̑傫���𒴂��Ă��邩�ǂ���
			if (i >= objSize)
			{
				//�����Ă���ꍇ
				//�I�u�W�F�N�g��ǉ�
				setPos.x = M_POS.x + M_SIZE.x * i;
				m_pCharacters->m_ObjectVector.push_back(new TextChar(setPos, M_SIZE, pDevice, M_TPS_COLOR, text[i]));
			}
			else
			{
				//�����Ă��Ȃ��ꍇ
				//�����炠��I�u�W�F�N�g�̕�����ς���
				m_pCharacters->m_ObjectVector[i]->CherTexSet(text[i]);
			}
		}
	}

	m_pCharacters->UpdateVIBuffer(pDevice);
}