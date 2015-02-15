#include "CG_queen.h"

//Default constructor
CG_queen::CG_queen()
    : CG_piece(WHITE, "Queen")
{

}

//Member functions
bool CG_queen::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    bool canMakeMove = false;

    //Check to see if Queen is moving only by File or only by Rank.
    //aka, only vertically or horizontally.
    if ( f_from == f_to || r_from == r_to )
    {
        canMakeMove = true;
    }

    //Check to see if Queen only moves diagonally.
    if ( abs(f_from - f_to) == abs(r_to - r_from) )
    {
        canMakeMove = true;
    }

    return canMakeMove;
}
