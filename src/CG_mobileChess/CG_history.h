#ifndef CG_HISTORY_H
#define CG_HISTORY_H

#include <QDebug>
#include <vector>
#include <iterator>
#include "CG_square.h"

const int NUMBER_OF_RANKS = 8;

class CG_history
{
public:
    CG_history();
    CG_history(CG_square board[8][8]);
    void setNext(CG_square board[8][8], CG_square from, CG_square to);
    void moveBack();
    void moveForward();
    CG_square ** getCurrentBoard();

private:
    std::vector<CG_square **> m_boardList;
    CG_square m_from;
    CG_square m_to;
    int m_currentBoardIndex;
};

#endif // CG_HISTORY_H
