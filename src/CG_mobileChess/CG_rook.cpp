#include "CG_rook.h"

//Default constructor
CG_rook::CG_rook(CG_Color color)
    : CG_piece(color, "Rook")
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
