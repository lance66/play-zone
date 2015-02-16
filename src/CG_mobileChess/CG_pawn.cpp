#include "CG_pawn.h"

//Default constructor
CG_pawn::CG_pawn(CG_Color color)
    : CG_piece(color, "Pawn")
{

}

//Member functions
bool CG_pawn::move(File f_to, Rank r_to, File f_from, Rank r_from)
{
    bool canMakeMove = false;

    return canMakeMove;
}
