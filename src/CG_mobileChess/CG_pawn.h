#ifndef CG_PAWN_H
#define CG_PAWN_H

#include "CG_piece.h"

//Declare pawn class and inherit from piece class
class CG_pawn : public CG_piece
{
public:
    //Constructors
    CG_pawn();

    //Member Functions
    virtual bool move(File f_to, Rank r_to, File f_from, Rank r_from);
    bool canPromote();
    bool enPassant();
    //CG_piece promote(CG_piece promoteTo);

private:
    //Data Members
    int direction;
};

#endif // CG_PAWN_H
