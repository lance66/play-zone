#ifndef CG_KNIGHT_H
#define CG_KNIGHT_H

#include "CG_piece.h"

//Declare knight class and inherit from piece class
class CG_knight : public CG_piece
{
public:
    //Constructors
    CG_knight();
    //Member functions
    bool move(File f_to, Rank r_to, File f_from, Rank r_from);

private:
    //Data members
};

#endif // CG_KNIGHT_H
