#include "CG_bishop.h"

//Default constructor
CG_bishop::CG_bishop(CG_Color color)
    : CG_piece(color, "Bishop")
{

}

//Member functions
bool CG_bishop::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    //Assume bishop cannot move until proven otherwise
    bool canMakeMove = false;

    //Check to see if Bishop only moves diagonally.
    //The way it does this is through the absolute difference in its
    //Rank and File.  If both differences are equal, then the piece
    //moved diagonally.
    if ( abs(f_from - f_to) == abs(r_to - r_from) )
        canMakeMove = true;

    //Return whether bishop can move or not.
    return canMakeMove;
}
