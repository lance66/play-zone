#include "CG_board.h"
#include <QDebug>

//Default constructor
CG_board::CG_board() : m_board()
{
    //Set up the CG_squares to be the correct file and rank.
    for ( int rank = 1; rank <= 8; rank++)
    {
        for ( int file = 1; file <= 8; file++)
        {
            m_board[file-1][rank-1].setSquare((File)file, rank);
        }
    }

    //Set up all of the white pieces on the board.
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

    //Set up all of the black pieces on the board.
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

void CG_board::move(int f_source, int r_source, int f_dest, int r_dest)
{

    //This code will eventually be implemented for validation of piece movement.
    //As of current, pieces can move wherever to test that pieces can move on the board.
    /*if(m_board[f_source][r_source].getPiece() != nullptr)
    {
        if(m_board[f_dest][r_dest].getPiece() == nullptr)
        {
            if(m_board[f_source][r_source].getPiece()->move((File) f_source, (Rank) r_source, (File) f_dest, (Rank) r_dest))
            {
                m_board[f_dest][r_dest].setPiece(m_board[f_source][r_source].getPiece());
                m_board[f_source][r_source].setPiece(0);

                temp = m_board[f_source][r_source].getPieceName();
            }
        }
    }*/

    //Make the destination CG_square hold the CG_piece from the source CG_square,
    //and make the source CG_square hold a null pointer to a CG_piece.
    //Thus, this empties the source CG_square of its CG_piece.
    m_board[f_dest][r_dest].setPiece(m_board[f_source][r_source].getPiece());
    m_board[f_source][r_source].setPiece(0);
}

QString CG_board::getSquare(int source_file, int source_rank)
{
    //Makes a temporary QString of the CG_square's CG_piece name.
    QString ret_str = m_board[source_file][source_rank].getPieceName();
    char temp = '\0';

    //If the CG_piece pointer in CG_square isn't a null pointer,
    //Add an integer to the end representing the color of the piece.
    if (m_board[source_file][source_rank].getPiece() != nullptr)
    {
        temp = m_board[source_file][source_rank].getPiece()->getPieceColor() + 48;
        ret_str += QString(temp);
    }

    //Return the QString representing the CG_piece in the CG_square.
    return ret_str;
}
