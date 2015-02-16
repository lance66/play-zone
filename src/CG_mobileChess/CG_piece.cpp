#include "CG_piece.h"

//Default constructor
CG_piece::CG_piece(CG_Color pieceColor, QString pieceName)
    : m_pieceColor(pieceColor), m_pieceName(pieceName)
{

}

bool CG_piece::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    bool canMakeMove = false;

    return canMakeMove;
}

//Member functions
QString CG_piece::getPieceName() const
{
    return m_pieceName;
}

int CG_piece::getPieceColor() const
{
    return (int) m_pieceColor;
}
