#ifndef CG_BOARD_H
#define CG_BOARD_H

#include <QObject>
#include "CG_square.h"

class CG_board : public QObject
{
public:
    CG_board();
private:
    CG_square m_board[8][8];
};

#endif // CG_BOARD_H
