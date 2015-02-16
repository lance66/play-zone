#include "CG_king.h"

//Default constructor
CG_king::CG_king(CG_Color color)
    :CG_piece(color, "King")
{

}

//Member functions
bool CG_king::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    bool canMakeMove = false;

    //King logic here

    return canMakeMove;
}
