#include "CG_history.h"

CG_history::CG_history(CG_square from, CG_square to, CG_board * board, CG_history * previous)
{
    from = m_from;
    to = m_to;
    board = m_board;
    previous = m_previous;
    m_capturedPiece = board->getSquare(to.getFile(), to.getRank());
}

CG_history::setNext(CG_history next)
{
    m_next = next;
}

CG_history::moveBack()
{

}

CG_history::moveForward()
{

}
