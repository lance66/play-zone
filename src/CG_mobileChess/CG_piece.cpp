#include "CG_piece.h"

//Default constructor
CG_piece::CG_piece(CG_Color pieceColor, QString pieceName)
    : m_pieceColor(pieceColor), m_pieceName(pieceName)
{

}

//Member functions
QString CG_piece::getPieceName()
{
    return m_pieceName;
}

CG_Color CG_piece::getPieceColor()
{
    return m_pieceColor;
}
