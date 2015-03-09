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

    //This checks to see if the King moved 1 space in any
    //direction.  Eventually, logic will need to be applied for
    //castling purposes.
    if ( (abs(f_to - f_from) == 1 && abs(r_to - r_from) == 0) ||
         (abs(f_to - f_from) == 0 && abs(r_to - r_from) == 1) ||
         (abs(f_to - f_from) == 1 && abs(r_to - r_from) == 1))
    {
        canMakeMove = true;
    }

    return canMakeMove;
}
