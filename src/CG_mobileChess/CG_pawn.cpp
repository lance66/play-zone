#include "CG_pawn.h"

//Default constructor
CG_pawn::CG_pawn(CG_Color color)
    : CG_piece(color, "Pawn"), m_hasMoved(false)
{
    if(color == WHITE)
    {
        direction = 1;
    }
    else
    {
        direction = -1;
    }
}

//Member functions
bool CG_pawn::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    bool canMakeMove = false;

    //The Pawn's movements are by far the most complex of the
    //chess piece collection.  For now, this only cares if the
    //Pawn moves within its File, but eventually movements for
    //capturing, en passant, and the 2 space first move will be
    //accounted for.
    if( !m_hasMoved && abs(f_to - f_from) == 2 &&
        abs(r_to - r_from) == 0 )//&&
        //direction == f_to - f_from )
    {
        canMakeMove = true;
        m_hasMoved = true;
    }
    else if ( abs(f_to - f_from) == 1 &&
              abs(r_to - r_from) == 0 &&
              direction == f_to - f_from )
    {
        canMakeMove = true;
        m_hasMoved = true;
    }
    else if ( abs(f_to - f_from) == 1 &&
              abs(r_to - r_from) == 1 &&
              direction == f_to - f_from )
    {
        canMakeMove = true;
        m_hasMoved = true;
    }

    return canMakeMove;
}
