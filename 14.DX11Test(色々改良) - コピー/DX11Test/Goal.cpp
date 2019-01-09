#include"Goal.h"
#include"TextureData.h"
#include"Image.h"
#include"TextureData.h"

/*#####################################          #####################################*/
/*#####################################  PUBLIC  #####################################*/
/*#####################################          #####################################*/


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�|�W�V����</param>
Goal::Goal(Vector3 pos)
{
	m_pPin    = new Image({ pos.x + m_PinLocalPos.x, pos.y + m_PinLocalPos.y, pos.z + m_PinLocalPos.z }, m_PinSize, TextureData::Instance()->GetGOAL_PIN_TR(), TextureData::Instance()->GetGOAL_PIN_TSRV());
	m_pPole   = new Image({ pos.x + m_PoleLocalPos.x, pos.y + m_PoleLocalPos.y, pos.z + m_PoleLocalPos.z }, m_PoleSize, TextureData::Instance()->GetGOAL_POLE_TR(), TextureData::Instance()->GetGOAL_POLE_TSRV());
	m_pFlag   = new Image({ pos.x + m_FlagLocalPos.x, pos.y + m_FlagLocalPos.y, pos.z + m_FlagLocalPos.z }, m_FlagSize, TextureData::Instance()->GetGOAL_FLAG_TR(), TextureData::Instance()->GetGOAL_FLAG_TSRV());
	m_pCastle = new Image({ pos.x + m_CastleLocalPos.x, pos.y + m_CastleLocalPos.y, pos.z + m_CastleLocalPos.z }, m_CastleSize, TextureData::Instance()->GetGOAL_CASTLE_TR(), TextureData::Instance()->GetGOAL_CASTLE_TSRV());
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Goal::~Goal() 
{
	if (m_pPin    != nullptr) { delete m_pPin;    m_pPin    = nullptr; }
	if (m_pPole   != nullptr) { delete m_pPole;   m_pPole   = nullptr; }
	if (m_pFlag   != nullptr) { delete m_pFlag;   m_pFlag   = nullptr; }
	if (m_pCastle != nullptr) { delete m_pCastle; m_pCastle = nullptr; }
};


/*-------------------------------------             ----------------------------------*/
/*-------------------------------------  RenderObj  ----------------------------------*/
/*-------------------------------------             ----------------------------------*/

/// <summary>
/// ���̃I�u�W�F�N�g�̕`��
/// </summary>
void Goal::ThisObjRender()
{
	m_pPin   ->ThisObjRender();
	m_pPole  ->ThisObjRender();
	m_pFlag  ->ThisObjRender();
	m_pCastle->ThisObjRender();
}

/// <summary>
/// ���̃I�u�W�F�N�g�̃o�b�t�@�̐���
/// </summary>
void Goal::ThisObjCreateBuffer()
{
	m_pPin   ->ThisObjCreateBuffer();
	m_pPole  ->ThisObjCreateBuffer();
	m_pFlag  ->ThisObjCreateBuffer();
	m_pCastle->ThisObjCreateBuffer();
}