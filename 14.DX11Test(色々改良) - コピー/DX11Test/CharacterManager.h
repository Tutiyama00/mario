#pragma once

#include<d3d11.h>

template<class T> class Characters;
class Player;
class Block;
class Title;
enum class Object : unsigned char;
class DeathChecker;

class CharacterManager
{
public:
	CharacterManager(Object* stageArray, int stageHeight, int stageWidth, ID3D11Device* pDevice);
	~CharacterManager();

public:
	Characters<Block>* m_pCharacters_Block = nullptr;
	Player*            m_pPlayer           = nullptr;
	Title*             m_pTitle            = nullptr;
	DeathChecker*      m_pDeathChecker     = nullptr;

private:
	void CharacterMake(Object* stageArray, int stageHeight, int stageWidth, ID3D11Device* pDevice);

private:
	float m_StandardSize = 0.1f;
	float m_StandardZpos = -0.5f;
};