#include "CG_king.h"

//Default constructor
CG_king::CG_king(CG_Color color)
    :CG_piece(color, "King"), m_hasMoved(false)
{

}

//Member functions
bool CG_king::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    bool canMakeMove = false;

    //This checks to see if the King is attempting to castle.
    //This requires that a square 2 ranks away is selected without changing
    //the file, and that the king has not moved yet.
    if ( (abs(r_to - r_from) == 2 && abs(f_to - f_from) == 0 ) && !m_hasMoved)
    {
        canMakeMove = true;
    }
    //This checks to see if the king is moving 1 square in any direction.
    else if ( (abs(f_to - f_from) == 1 && abs(r_to - r_from) == 0) ||
         (abs(f_to - f_from) == 0 && abs(r_to - r_from) == 1) ||
         (abs(f_to - f_from) == 1 && abs(r_to - r_from) == 1))
    {
        canMakeMove = true;
    }

    return canMakeMove;
}

void CG_king::UpdatePiece()
{
    //If a king has moved, it needs to update the piece accordingly.
    m_hasMoved = true;
}

bool CG_king::getHasMoved()
{
    return m_hasMoved;
}
