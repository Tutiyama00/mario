#include"CharacterManager.h"
#include"Characters.h"
#include"Enum.h"
#include"Player.h"
#include"Block.h"
#include"Title.h"
#include<vector>

CharacterManager::CharacterManager(Object* stageArray, int stageHeight, int stageWidth, ID3D11Device* pDevice)
{
	m_pCharacters_Block = new Characters<Block>(pDevice, L"Block2.png", L"VertexShader.vsh", L"PixelShader.psh");

	CharacterMake(stageArray, stageHeight, stageWidth, pDevice);

	m_pCharacters_Block->ThisObjCreateBuffer(pDevice);
	m_pPlayer->ThisObjCreateBuffer(pDevice);
	m_pTitle->ThisObjCreateBuffer(pDevice);
}

CharacterManager::~CharacterManager()
{
	if (m_pCharacters_Block != nullptr) { delete m_pCharacters_Block; m_pCharacters_Block = nullptr; }
	if (m_pPlayer           != nullptr) { delete m_pPlayer;           m_pPlayer           = nullptr; }
	if (m_pTitle            != nullptr) { delete m_pTitle;            m_pTitle            = nullptr; }
}

void CharacterManager::CharacterMake(Object* stageArray, int stageHeight, int stageWidth, ID3D11Device* pDevice)
{
	//.5���؂�グ�ɂȂ�̂ŏc���i��O��j�̒��Ԓl���擾�ł���
	int halfHeight = stageHeight / 2;

	//�X�e�[�W��񂩂琶������I�u�W�F�N�g�𔻕�
	for (int height = 0; height < stageHeight; height++)
	{
		for (int width = 0; width < stageWidth; width++)
		{
			//�����ʒu�̃|�W�V�����̌v�Z
			float xPos = m_StandardSize * width;
			float yPos = m_StandardSize * -(height - halfHeight);

			//�X�C�b�`���Ŕ���
			switch (*(stageArray + (height*stageWidth + width)))
			{
			case Object::MARIO:
				m_pPlayer = new Player(xPos, yPos, m_StandardZpos, m_StandardSize, m_StandardSize, pDevice);
				break;
			case Object::NORMAL_BLOCK:
				m_pCharacters_Block->m_ObjectVector.push_back(new Block(xPos, yPos, m_StandardZpos, m_StandardSize, m_StandardSize));
				break;
			}
		}
	}

	//�^�C�g���p�I�u�W�F�N�g�̐���
	m_pTitle = new Title(0.0f, 0.0f, m_StandardZpos, 1.5, 1.3, pDevice);
}