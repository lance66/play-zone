#include "CG_board.h"
#include <QDebug>

//Default constructor
CG_board::CG_board()
{
    //Create pointer to temporary piece
    CG_piece *tempPiece;

    //First turn of the game is always white
    turn = WHITE;

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
}

//CG_board::CG_board() : m_board()
//{
//    for ( int rank = 1; rank <= 8; rank++)
//    {
//        for ( int file = 1; file <= 8; file++)
//        {
//            //m_board[file][rank].SetFile(file);
//            //m_board[file][rank].SetRow(row);

//            if((rank % 2 == 1 && file % 2 == 1) ||
//               (rank % 2 == 0 && file % 2 == 0))
//            {
//               // m_board[file][rank].SetColor(Black);
//            }
//            else
//            {
//                //m_board[file][rank].SetColor(White);
//            }

//            //m_board[file][rank].SetClicked(false);
//        }
//    }
//}
