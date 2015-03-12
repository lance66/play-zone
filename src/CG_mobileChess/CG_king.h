#ifndef CG_KING_H
#define CG_KING_H

#include "CG_piece.h"

//Declare king class and inherit from piece
class CG_king : public CG_piece
{
public:
    //Constructors
    CG_king(CG_Color color = WHITE);

    //Member functions
    bool move(File f_to, Rank r_to, File f_from, Rank r_from);
    void UpdatePiece();
    bool getHasMoved();
private:
    bool m_hasMoved;
    //Data members
};

#endif // CG_KING_H
