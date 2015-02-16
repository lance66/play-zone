#ifndef CG_ROOK_H
#define CG_ROOK_H

#include <QObject>
#include "CG_piece.h"

class CG_rook : public CG_piece
{
    Q_OBJECT

public:
    CG_rook(CG_Color color = WHITE);
    bool move(File f_to, Rank r_to, File f_from, Rank r_from);

private:

};

#endif // CG_ROOK_H
