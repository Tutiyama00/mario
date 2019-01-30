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
		if (pSquare->m_pVertexArray[3].pos.y - m_Threshold <= m_pVertexArray[0].pos.y && pSquare->m_pVertexArray[3].pos.y - m_Threshold >= m_pVertexArray[2].pos.y
			||(pSquare->m_pVertexArray[1].pos.y + m_Threshold <= m_pVertexArray[0].pos.y && pSquare->m_pVertexArray[1].pos.y + m_Threshold >= m_pVertexArray[2].pos.y))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 左側にあるかチェック
/// </summary>
/// <param name="pSquare">調査対象</param>
/// <param name="threshold">調整値（正＝ゆるく、負＝厳しく）</param>
/// <returns>T：ある、F：ない</returns>
bool NotPlayer::LeftCheck(Square* pSquare, float threshold)
{
	//調査対象がこのブロックの左側にあるか
	if (pSquare->GetxPos() <= m_xPos)
	{
		//プレイヤーの右上か右下の頂点がこのブロックの左上、左下の間にあるか
		if (pSquare->m_pVertexArray[3].pos.y - threshold <= m_pVertexArray[0].pos.y && pSquare->m_pVertexArray[3].pos.y - threshold >= m_pVertexArray[2].pos.y
			|| (pSquare->m_pVertexArray[1].pos.y + threshold <= m_pVertexArray[0].pos.y && pSquare->m_pVertexArray[1].pos.y + threshold >= m_pVertexArray[2].pos.y))
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
		if ((pSquare->m_pVertexArray[0].pos.y - m_Threshold <= m_pVertexArray[3].pos.y && pSquare->m_pVertexArray[3].pos.y - m_Threshold >= m_pVertexArray[1].pos.y)
			||(pSquare->m_pVertexArray[2].pos.y + m_Threshold <= m_pVertexArray[3].pos.y && pSquare->m_pVertexArray[1].pos.y + m_Threshold >= m_pVertexArray[1].pos.y))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 右側にあるかチェック
/// </summary>
/// <param name="pSquare">調査対象</param>
/// <param name="threshold">調整値（正＝ゆるく、負＝厳しく）</param>
/// <returns>T：ある、F：ない</returns>
bool NotPlayer::RightCheck(Square* pSquare, float threshold)
{
	//プレイヤーがこのブロックの右側にあるか
	if (pSquare->GetxPos() >= m_xPos)
	{
		//プレイヤーの左上か左下の頂点がこのブロックの右上、右下の間にあるか
		if ((pSquare->m_pVertexArray[0].pos.y - threshold <= m_pVertexArray[3].pos.y && pSquare->m_pVertexArray[3].pos.y - threshold >= m_pVertexArray[1].pos.y)
			|| (pSquare->m_pVertexArray[2].pos.y + threshold <= m_pVertexArray[3].pos.y && pSquare->m_pVertexArray[1].pos.y + threshold >= m_pVertexArray[1].pos.y))
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
		if ((pSquare->m_pVertexArray[0].pos.x + m_Threshold >= m_pVertexArray[2].pos.x && pSquare->m_pVertexArray[0].pos.x + m_Threshold <= m_pVertexArray[1].pos.x)
			||(pSquare->m_pVertexArray[3].pos.x - m_Threshold >= m_pVertexArray[2].pos.x && pSquare->m_pVertexArray[3].pos.x - m_Threshold <= m_pVertexArray[1].pos.x))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 下側にあるかチェック
/// </summary>
/// <param name="pSquare">調査対象</param>
/// <param name="threshold">調整値（正＝ゆるく、負＝厳しく）</param>
/// <returns>T：ある、F：ない</returns>
bool NotPlayer::DownCheck(Square* pSquare, float threshold)
{
	//プレイヤーがこのブロックの下にあるか
	if (pSquare->GetyPos() <= m_yPos)
	{
		//プレイヤーの左上か右上の頂点がこのブロックの左下、右下の間にあるか
		if ((pSquare->m_pVertexArray[0].pos.x + threshold >= m_pVertexArray[2].pos.x && pSquare->m_pVertexArray[0].pos.x + threshold <= m_pVertexArray[1].pos.x)
			|| (pSquare->m_pVertexArray[3].pos.x - threshold >= m_pVertexArray[2].pos.x && pSquare->m_pVertexArray[3].pos.x - threshold <= m_pVertexArray[1].pos.x))
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
	//調査対象がこのブロックの上にあるか
	if (pSquare->GetyPos() >= ((m_pVertexArray[0].pos.y - m_yPos) / 4) + m_yPos)
	{
		//調査対象の左下か右下の頂点がこのブロックの左上、右上の間にあるか
		if ((pSquare->m_pVertexArray[2].pos.x + m_Threshold >= m_pVertexArray[0].pos.x && pSquare->m_pVertexArray[2].pos.x + m_Threshold <= m_pVertexArray[3].pos.x)
			||((pSquare->m_pVertexArray[1].pos.x - m_Threshold >= m_pVertexArray[0].pos.x && pSquare->m_pVertexArray[1].pos.x - m_Threshold <= m_pVertexArray[3].pos.x)))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 上側にあるかチェック
/// </summary>
/// <param name="pSquare">調査対象</param>
/// <param name="threshold">調整値（正＝ゆるく、負＝厳しく）</param>
/// <returns>T：ある、F：ない</returns>
bool NotPlayer::UpCheck(Square* pSquare, float threshold)
{
	//調査対象がこのブロックの上にあるか
	if (pSquare->GetyPos() >= ((m_pVertexArray[0].pos.y - m_yPos) / 4) + m_yPos)
	{
		//調査対象の左下か右下の頂点がこのブロックの左上、右上の間にあるか
		if ((pSquare->m_pVertexArray[2].pos.x + threshold >= m_pVertexArray[0].pos.x && pSquare->m_pVertexArray[2].pos.x + threshold <= m_pVertexArray[3].pos.x)
			|| ((pSquare->m_pVertexArray[1].pos.x - threshold >= m_pVertexArray[0].pos.x && pSquare->m_pVertexArray[1].pos.x - threshold <= m_pVertexArray[3].pos.x)))
		{
			return true;
		}
	}

	return false;
}