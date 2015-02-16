#include "CG_knight.h"

//Default constructor
CG_knight::CG_knight(CG_Color color)
    : CG_piece(color, "Knight")
{

}

//Member functions
bool CG_knight::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    //Assume knight cannot move until proven otherwise
    bool canMakeMove = false;

    //A Knight moves in an 'L' pattern, which is essentially either
    //moving 1 File away and 2 Ranks away from its original position,
    //or moving 2 Files away and 1 Rank away from its original position.
    if ( (abs(f_to - f_from) == 2 && abs(r_to - r_from) == 1) ||
         (abs(f_to - f_from) == 1 && abs(r_to - r_from) == 2) )
    {
        canMakeMove = true;
    }

    //Return whether knight can move or not.
    return canMakeMove;
}
