#ifndef CG_PIECE_H
#define CG_PIECE_H

#include <QObject>

#include "CG_define.h"
//enum Color { White, Black};

class CG_piece : public QObject
{
public:
    void move(CG_board board, File f_to, Rank r_to,
              File f_from, Rank r_from) = 0;
    bool captured();
private:
    Color m_pieceColor;
    CG_square m_position;
};

#endif // CG_PIECE_H
