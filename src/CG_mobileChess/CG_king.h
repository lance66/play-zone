#ifndef CG_KING_H
#define CG_KING_H

#include "CG_piece.h"

//Declare king class and inherit from piece
class CG_king : public CG_piece
{
public:
    //Constructors
    CG_king();

    //Member functions
    bool move(File f_to, Rank r_to, File f_from, Rank r_from);
private:
    //Data members
};

#endif // CG_KING_H
