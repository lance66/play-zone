#include "CG_bishop.h"

//Default constructor
CG_bishop::CG_bishop()
    : CG_piece(WHITE, "Bishop")
{

}

//Member functions
bool CG_bishop::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    //Assume bishop cannot move until proven otherwise
    bool canMakeMove = false;

    //Check to see if Bishop only moves diagonally.
    if ( abs(f_from - f_to) == abs(r_to - r_from) )
        canMakeMove = true;

    //Return whether bishop can move or not.
    return canMakeMove;
}
