#ifndef CG_QUEEN_H
#define CG_QUEEN_H

#include <QObject>
#include "CG_piece.h"

class CG_queen : public CG_piece
{
    Q_OBJECT

public:
    //Constructors
    CG_queen();

    //Member functions
    bool move(File f_to, Rank r_to, File f_from, Rank r_from);

private:

};

#endif // CG_QUEEN_H
