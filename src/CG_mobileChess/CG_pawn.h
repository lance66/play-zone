#ifndef CG_PAWN_H
#define CG_PAWN_H

#include "CG_piece.h"

//Declare pawn class and inherit from piece class
class CG_pawn : public CG_piece
{
public:
    //Constructors
    CG_pawn(CG_Color color = WHITE);

    //Member Functions
    bool move(File f_to, Rank r_to, File f_from, Rank r_from);
    void UpdatePiece();
    bool canPromote();
    bool enPassant();

    void ToggleDirection() { direction *= -1; }
    //CG_piece promote(CG_piece promoteTo);

private:
    //Data Members
    int direction;
    bool m_hasMoved;
};

#endif // CG_PAWN_H

// TODO : Change variable name of direction to m_direction
