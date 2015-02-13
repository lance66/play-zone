#ifndef CG_ROOK_H
#define CG_ROOK_H

#include <QObject>
#include "CG_piece.h"

class CG_rook : public CG_piece
{
    Q_OBJECT

public:
    CG_rook() : m_pieceColor(White), m_pieceName("Rook")
    {

    }

    virtual bool move(File f_to, Rank r_to, File f_from, Rank r_from)
    {
        bool canMakeMove = false;

        //Check to see if Rook is moving only by File or only by Rank.
        //aka, only vertically or horizontally.
        if ( f_from == f_to || r_from == r_to )
        {
            canMakeMove = true;
        }

        return canMakeMove;
    }

private:

};

#endif // CG_ROOK_H
