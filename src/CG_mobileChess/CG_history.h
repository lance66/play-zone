#ifndef CG_HISTORY_H
#define CG_HISTORY_H

#include "CG_board.h"
//#include "CG_piece.h"

class CG_history
{
public:
    CG_history(CG_square from, CG_square to, CG_board * board, CG_history * previous);
    setNext(CG_history next);
    void moveBack();
    void moveForward();
private:
    CG_board * m_board;
    CG_history * m_previous;
    CG_history * m_next;
    CG_square m_from;
    CG_square m_to;
    CG_piece m_capturedPiece;
};

#endif // CG_HISTORY_H
