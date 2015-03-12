#include "CG_history.h"

CG_history::CG_history(CG_square board[8][8])
{
    CG_square ** temp = new CG_square * [NUMBER_OF_RANKS];

    //Set each individual square in board to temp
    for(int rank = 0; rank < NUMBER_OF_RANKS; rank++)
    {
        temp[rank] = new CG_square[NUMBER_OF_RANKS];

        for (int file = 0; file < NUMBER_OF_RANKS; file++)
        {
            temp[rank][file].setRank(board[rank][file].getRank());
            temp[rank][file].setFile(board[rank][file].getFile());
            temp[rank][file].setPiece(board[rank][file].getPiece());
        }
    }

    for(int i = 0; i < NUMBER_OF_RANKS; i++)
        delete temp[i];

    delete [] temp;

    m_boardList.push_back(temp);
    m_currentBoardIndex = 0;
}

CG_history::CG_history()
{
    m_currentBoardIndex = 0;
}

void CG_history::setNext(CG_square board[8][8], CG_square from, CG_square to)
{
    m_currentBoardIndex++;

    CG_square ** temp = new CG_square * [NUMBER_OF_RANKS];

    for(int rank = 0; rank < NUMBER_OF_RANKS; rank++)
    {
        temp[rank] = new CG_square[NUMBER_OF_RANKS];

        for (int file = 0; file < NUMBER_OF_RANKS; file++)
        {
            temp[rank][file].setRank(board[rank][file].getRank());
            temp[rank][file].setFile(board[rank][file].getFile());
            temp[rank][file].setPiece(board[rank][file].getPiece());
        }
    }

    m_boardList.push_back(temp);

//    for(int i = 0; i < NUMBER_OF_RANKS; i++)
//        delete [] temp[i];

//    delete [] temp;

//    m_from = from;
//    m_to = to;
}

void CG_history::moveBack()
{
    m_currentBoardIndex--;
}

void CG_history::moveForward()
{
    m_currentBoardIndex++;
}

CG_square ** CG_history::getCurrentBoard()
{
    return m_boardList[m_currentBoardIndex];
}
