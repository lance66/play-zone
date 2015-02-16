#ifndef CG_BISHOP_H
#define CG_BISHOP_H

#include <QObject>
#include "CG_piece.h"

class CG_bishop : public CG_piece
{
    //Macro for all QObjects
    Q_OBJECT

public:
    //Constructors
    CG_bishop(CG_Color color = WHITE);

    //Member functions
    bool move(File f_to, Rank r_to, File f_from, Rank r_from);

private:

};

#endif // CG_BISHOP_H
