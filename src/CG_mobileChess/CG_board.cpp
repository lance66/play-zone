#include "CG_board.h"
#include <QDebug>

//Default constructor
//CG_board::CG_board()
//{
    //Create pointer to temporary piece

    //First turn of the game is always white
    //turn = WHITE;

    //Enpassant is null until enpassant actually happens
    //enPassant = nullptr;

    //Print board

    //Make into member function later
//    for(int rank = 1; rank <=8; rank++)
//    {
//        for(int file = 1; file <=8; file++)
//        {
//            if(rank == 1 && file == 1)
//                tempPiece = CG_Piece(WHITE, "rook");
//            else
//            {
//                //Empty square
//                tempPiece = nullptr;
//            }

//            //Assign board to correct piece
//            m_board[file][rank] = tempPiece;

//            //Make sure we placed the correct piece on the correct square
//            QDebug() << m_board[file][rank];
//        }
//    }
//}

CG_board::CG_board() : m_board()
{
    for ( int rank = 1; rank <= 8; rank++)
    {
        for ( int file = 1; file <= 8; file++)
        {
            m_board[file-1][rank-1].setSquare((File)file, rank);
            //m_board[file][rank].SetFile(file);
            //m_board[file][rank].SetRow(row);
        }
    }

    m_board[0][0].setPiece(WHITE, "Rook");
    m_board[0][1].setPiece(WHITE, "Knight");
    m_board[0][2].setPiece(WHITE, "Bishop");
    m_board[0][3].setPiece(WHITE, "Queen");
    m_board[0][4].setPiece(WHITE, "King");
    m_board[0][5].setPiece(WHITE, "Bishop");
    m_board[0][6].setPiece(WHITE, "Knight");
    m_board[0][7].setPiece(WHITE, "Rook");
    m_board[1][0].setPiece(WHITE, "Pawn");
    m_board[1][1].setPiece(WHITE, "Pawn");
    m_board[1][2].setPiece(WHITE, "Pawn");
    m_board[1][3].setPiece(WHITE, "Pawn");
    m_board[1][4].setPiece(WHITE, "Pawn");
    m_board[1][5].setPiece(WHITE, "Pawn");
    m_board[1][6].setPiece(WHITE, "Pawn");
    m_board[1][7].setPiece(WHITE, "Pawn");

    m_board[7][0].setPiece(BLACK, "Rook");
    m_board[7][1].setPiece(BLACK, "Knight");
    m_board[7][2].setPiece(BLACK, "Bishop");
    m_board[7][3].setPiece(BLACK, "Queen");
    m_board[7][4].setPiece(BLACK, "King");
    m_board[7][5].setPiece(BLACK, "Bishop");
    m_board[7][6].setPiece(BLACK, "Knight");
    m_board[7][7].setPiece(BLACK, "Rook");
    m_board[6][0].setPiece(BLACK, "Pawn");
    m_board[6][1].setPiece(BLACK, "Pawn");
    m_board[6][2].setPiece(BLACK, "Pawn");
    m_board[6][3].setPiece(BLACK, "Pawn");
    m_board[6][4].setPiece(BLACK, "Pawn");
    m_board[6][5].setPiece(BLACK, "Pawn");
    m_board[6][6].setPiece(BLACK, "Pawn");
    m_board[6][7].setPiece(BLACK, "Pawn");
}
