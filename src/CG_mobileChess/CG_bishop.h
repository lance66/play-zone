#ifndef CG_BISHOP_H
#define CG_BISHOP_H

#include <QObject>
#include "CG_piece.h"

class CG_bishop : public CG_piece
{
    Q_OBJECT

public:
    CG_bishop() : CG_piece(White, "Bishop")
    {

    }
    virtual bool move(File f_to, Rank r_to, File f_from, Rank r_from)
    {
        bool canMakeMove = false;

        //Check to see if Bishop only moves diagonally.
        if ( abs(f_from - f_to) == abs(r_to - r_from) )
        {
            canMakeMove = true;
        }

        return canMakeMove;
    }

private:

};

#endif // CG_BISHOP_H
