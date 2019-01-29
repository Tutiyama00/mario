#include"NotPlayer.h"
#include"Vertex.h"


/*#####################################             #####################################*/
/*#####################################  PROTECTED  #####################################*/
/*#####################################             #####################################*/

/// <summary>
/// �����ɂ��邩�̃`�F�b�N
/// </summary>
/// <param name="pSquare">�����Ώ�</param>
/// <returns>T�F����AF�F�Ȃ�</returns>
bool NotPlayer::LeftCheck(Square* pSquare)
{
	//�����Ώۂ����̃u���b�N�̍����ɂ��邩
	if (pSquare->GetxPos() <= m_xPos)
	{
		//�v���C���[�̉E�ォ�E���̒��_�����̃u���b�N�̍���A�����̊Ԃɂ��邩
		if (pSquare->m_pVertexArray[3].pos[1] - m_Threshold <= m_pVertexArray[0].pos[1] && pSquare->m_pVertexArray[3].pos[1] - m_Threshold >= m_pVertexArray[2].pos[1])
		{
			return true;
		}
		else if (pSquare->m_pVertexArray[1].pos[1] + m_Threshold <= m_pVertexArray[0].pos[1] && pSquare->m_pVertexArray[1].pos[1] + m_Threshold >= m_pVertexArray[2].pos[1])
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �E���ɂ��邩�̃`�F�b�N
/// </summary>
/// <param name="pSquare">�����Ώ�</param>
/// <returns>T�F����AF�F�Ȃ�</returns>
bool NotPlayer::RightCheck(Square* pSquare)
{
	//�v���C���[�����̃u���b�N�̉E���ɂ��邩
	if (pSquare->GetxPos() >= m_xPos)
	{
		//�v���C���[�̍��ォ�����̒��_�����̃u���b�N�̉E��A�E���̊Ԃɂ��邩
		if (pSquare->m_pVertexArray[0].pos[1] - m_Threshold <= m_pVertexArray[3].pos[1] && pSquare->m_pVertexArray[3].pos[1] - m_Threshold >= m_pVertexArray[1].pos[1])
		{
			return true;
		}
		else if (pSquare->m_pVertexArray[2].pos[1] + m_Threshold <= m_pVertexArray[3].pos[1] && pSquare->m_pVertexArray[1].pos[1] + m_Threshold >= m_pVertexArray[1].pos[1])
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �����ɂ��邩�̃`�F�b�N
/// </summary>
/// <param name="pSquare">�����Ώ�</param>
/// <returns>T�F����AF�F�Ȃ�</returns>
bool NotPlayer::DownCheck(Square* pSquare)
{
	//�v���C���[�����̃u���b�N�̉��ɂ��邩
	if (pSquare->GetyPos() <= m_yPos)
	{
		//�v���C���[�̍��ォ�E��̒��_�����̃u���b�N�̍����A�E���̊Ԃɂ��邩
		if (pSquare->m_pVertexArray[0].pos[0] + m_Threshold >= m_pVertexArray[2].pos[0] && pSquare->m_pVertexArray[0].pos[0] + m_Threshold <= m_pVertexArray[1].pos[0])
		{
			return true;
		}
		else if (pSquare->m_pVertexArray[3].pos[0] - m_Threshold >= m_pVertexArray[2].pos[0] && pSquare->m_pVertexArray[3].pos[0] - m_Threshold <= m_pVertexArray[1].pos[0])
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �㑤�ɂ��邩�̃`�F�b�N
/// </summary>
/// <param name="pSquare">�����Ώ�</param>
/// <returns>T�F����AF�F�Ȃ�</returns>
bool NotPlayer::UpCheck(Square* pSquare)
{
	//�v���C���[�����̃u���b�N�̏�ɂ��邩
	if (pSquare->GetyPos() >= m_pVertexArray[0].pos[1])
	{
		//�v���C���[�̍������E���̒��_�����̃u���b�N�̍���A�E��̊Ԃɂ��邩
		if (pSquare->m_pVertexArray[2].pos[0] + m_Threshold >= m_pVertexArray[0].pos[0] && pSquare->m_pVertexArray[2].pos[0] + m_Threshold <= m_pVertexArray[3].pos[0])
		{
			return true;
		}
		else if (pSquare->m_pVertexArray[1].pos[0] - m_Threshold >= m_pVertexArray[0].pos[0] && pSquare->m_pVertexArray[1].pos[0] - m_Threshold <= m_pVertexArray[3].pos[0])
		{
			return true;
		}
	}

	return false;
}