#include"NotPlayer.h"
#include"Vertex.h"


/*#####################################             #####################################*/
/*#####################################  PROTECTED  #####################################*/
/*#####################################             #####################################*/

/// <summary>
/// 左側にあるかのチェック
/// </summary>
/// <param name="pSquare">調査対象</param>
/// <returns>T：ある、F：ない</returns>
bool NotPlayer::LeftCheck(Square* pSquare)
{
	//調査対象がこのブロックの左側にあるか
	if (pSquare->GetxPos() <= m_xPos)
	{
		//プレイヤーの右上か右下の頂点がこのブロックの左上、左下の間にあるか
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
/// 右側にあるかのチェック
/// </summary>
/// <param name="pSquare">調査対象</param>
/// <returns>T：ある、F：ない</returns>
bool NotPlayer::RightCheck(Square* pSquare)
{
	//プレイヤーがこのブロックの右側にあるか
	if (pSquare->GetxPos() >= m_xPos)
	{
		//プレイヤーの左上か左下の頂点がこのブロックの右上、右下の間にあるか
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
/// 下側にあるかのチェック
/// </summary>
/// <param name="pSquare">調査対象</param>
/// <returns>T：ある、F：ない</returns>
bool NotPlayer::DownCheck(Square* pSquare)
{
	//プレイヤーがこのブロックの下にあるか
	if (pSquare->GetyPos() <= m_yPos)
	{
		//プレイヤーの左上か右上の頂点がこのブロックの左下、右下の間にあるか
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
/// 上側にあるかのチェック
/// </summary>
/// <param name="pSquare">調査対象</param>
/// <returns>T：ある、F：ない</returns>
bool NotPlayer::UpCheck(Square* pSquare)
{
	//プレイヤーがこのブロックの上にあるか
	if (pSquare->GetyPos() >= m_pVertexArray[0].pos[1])
	{
		//プレイヤーの左下か右下の頂点がこのブロックの左上、右上の間にあるか
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