#include "CG_rook.h"

//Default constructor
CG_rook::CG_rook(CG_Color color)
    : CG_piece(color, "Rook"), m_hasMoved(false)
{

}

//Member functions
bool CG_rook::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    bool canMakeMove = false;

    //Check to see if Rook is moving only by File or only by Rank.
    //aka, only vertically or horizontally.
    if ( f_from == f_to || r_from == r_to )
    {
        canMakeMove = true;
    }

    return canMakeMove;
}

void CG_rook::UpdatePiece()
{
    //If a rook has moved, it needs to update the rook accordingly.
    m_hasMoved = true;
}

bool CG_rook::getHasMoved()
{
    return m_hasMoved;
}
