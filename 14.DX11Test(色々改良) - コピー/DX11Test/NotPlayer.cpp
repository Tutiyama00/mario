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
		if (pSquare->m_pVertexArray[3].pos.y - m_Threshold <= m_pVertexArray[0].pos.y && pSquare->m_pVertexArray[3].pos.y - m_Threshold >= m_pVertexArray[2].pos.y
			||(pSquare->m_pVertexArray[1].pos.y + m_Threshold <= m_pVertexArray[0].pos.y && pSquare->m_pVertexArray[1].pos.y + m_Threshold >= m_pVertexArray[2].pos.y))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �����ɂ��邩�`�F�b�N
/// </summary>
/// <param name="pSquare">�����Ώ�</param>
/// <param name="threshold">�����l�i������邭�A�����������j</param>
/// <returns>T�F����AF�F�Ȃ�</returns>
bool NotPlayer::LeftCheck(Square* pSquare, float threshold)
{
	//�����Ώۂ����̃u���b�N�̍����ɂ��邩
	if (pSquare->GetxPos() <= m_xPos)
	{
		//�v���C���[�̉E�ォ�E���̒��_�����̃u���b�N�̍���A�����̊Ԃɂ��邩
		if (pSquare->m_pVertexArray[3].pos.y - threshold <= m_pVertexArray[0].pos.y && pSquare->m_pVertexArray[3].pos.y - threshold >= m_pVertexArray[2].pos.y
			|| (pSquare->m_pVertexArray[1].pos.y + threshold <= m_pVertexArray[0].pos.y && pSquare->m_pVertexArray[1].pos.y + threshold >= m_pVertexArray[2].pos.y))
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
		if ((pSquare->m_pVertexArray[0].pos.y - m_Threshold <= m_pVertexArray[3].pos.y && pSquare->m_pVertexArray[3].pos.y - m_Threshold >= m_pVertexArray[1].pos.y)
			||(pSquare->m_pVertexArray[2].pos.y + m_Threshold <= m_pVertexArray[3].pos.y && pSquare->m_pVertexArray[1].pos.y + m_Threshold >= m_pVertexArray[1].pos.y))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �E���ɂ��邩�`�F�b�N
/// </summary>
/// <param name="pSquare">�����Ώ�</param>
/// <param name="threshold">�����l�i������邭�A�����������j</param>
/// <returns>T�F����AF�F�Ȃ�</returns>
bool NotPlayer::RightCheck(Square* pSquare, float threshold)
{
	//�v���C���[�����̃u���b�N�̉E���ɂ��邩
	if (pSquare->GetxPos() >= m_xPos)
	{
		//�v���C���[�̍��ォ�����̒��_�����̃u���b�N�̉E��A�E���̊Ԃɂ��邩
		if ((pSquare->m_pVertexArray[0].pos.y - threshold <= m_pVertexArray[3].pos.y && pSquare->m_pVertexArray[3].pos.y - threshold >= m_pVertexArray[1].pos.y)
			|| (pSquare->m_pVertexArray[2].pos.y + threshold <= m_pVertexArray[3].pos.y && pSquare->m_pVertexArray[1].pos.y + threshold >= m_pVertexArray[1].pos.y))
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
		if ((pSquare->m_pVertexArray[0].pos.x + m_Threshold >= m_pVertexArray[2].pos.x && pSquare->m_pVertexArray[0].pos.x + m_Threshold <= m_pVertexArray[1].pos.x)
			||(pSquare->m_pVertexArray[3].pos.x - m_Threshold >= m_pVertexArray[2].pos.x && pSquare->m_pVertexArray[3].pos.x - m_Threshold <= m_pVertexArray[1].pos.x))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �����ɂ��邩�`�F�b�N
/// </summary>
/// <param name="pSquare">�����Ώ�</param>
/// <param name="threshold">�����l�i������邭�A�����������j</param>
/// <returns>T�F����AF�F�Ȃ�</returns>
bool NotPlayer::DownCheck(Square* pSquare, float threshold)
{
	//�v���C���[�����̃u���b�N�̉��ɂ��邩
	if (pSquare->GetyPos() <= m_yPos)
	{
		//�v���C���[�̍��ォ�E��̒��_�����̃u���b�N�̍����A�E���̊Ԃɂ��邩
		if ((pSquare->m_pVertexArray[0].pos.x + threshold >= m_pVertexArray[2].pos.x && pSquare->m_pVertexArray[0].pos.x + threshold <= m_pVertexArray[1].pos.x)
			|| (pSquare->m_pVertexArray[3].pos.x - threshold >= m_pVertexArray[2].pos.x && pSquare->m_pVertexArray[3].pos.x - threshold <= m_pVertexArray[1].pos.x))
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
	//�����Ώۂ����̃u���b�N�̏�ɂ��邩
	if (pSquare->GetyPos() >= ((m_pVertexArray[0].pos.y - m_yPos) / 4) + m_yPos)
	{
		//�����Ώۂ̍������E���̒��_�����̃u���b�N�̍���A�E��̊Ԃɂ��邩
		if ((pSquare->m_pVertexArray[2].pos.x + m_Threshold >= m_pVertexArray[0].pos.x && pSquare->m_pVertexArray[2].pos.x + m_Threshold <= m_pVertexArray[3].pos.x)
			||((pSquare->m_pVertexArray[1].pos.x - m_Threshold >= m_pVertexArray[0].pos.x && pSquare->m_pVertexArray[1].pos.x - m_Threshold <= m_pVertexArray[3].pos.x)))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �㑤�ɂ��邩�`�F�b�N
/// </summary>
/// <param name="pSquare">�����Ώ�</param>
/// <param name="threshold">�����l�i������邭�A�����������j</param>
/// <returns>T�F����AF�F�Ȃ�</returns>
bool NotPlayer::UpCheck(Square* pSquare, float threshold)
{
	//�����Ώۂ����̃u���b�N�̏�ɂ��邩
	if (pSquare->GetyPos() >= ((m_pVertexArray[0].pos.y - m_yPos) / 4) + m_yPos)
	{
		//�����Ώۂ̍������E���̒��_�����̃u���b�N�̍���A�E��̊Ԃɂ��邩
		if ((pSquare->m_pVertexArray[2].pos.x + threshold >= m_pVertexArray[0].pos.x && pSquare->m_pVertexArray[2].pos.x + threshold <= m_pVertexArray[3].pos.x)
			|| ((pSquare->m_pVertexArray[1].pos.x - threshold >= m_pVertexArray[0].pos.x && pSquare->m_pVertexArray[1].pos.x - threshold <= m_pVertexArray[3].pos.x)))
		{
			return true;
		}
	}

	return false;
}