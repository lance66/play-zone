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
    m_board[0][0].setPiece(BLACK, "Rook");
    m_board[0][1].setPiece(BLACK, "Knight");
    m_board[0][2].setPiece(BLACK, "Bishop");
    m_board[0][3].setPiece(BLACK, "Queen");
    m_board[0][4].setPiece(BLACK, "King");
    m_board[0][5].setPiece(BLACK, "Bishop");
    m_board[0][6].setPiece(BLACK, "Knight");
    m_board[0][7].setPiece(BLACK, "Rook");
    m_board[1][0].setPiece(BLACK, "Pawn");
    m_board[1][1].setPiece(BLACK, "Pawn");
    m_board[1][2].setPiece(BLACK, "Pawn");
    m_board[1][3].setPiece(BLACK, "Pawn");
    m_board[1][4].setPiece(BLACK, "Pawn");
    m_board[1][5].setPiece(BLACK, "Pawn");
    m_board[1][6].setPiece(BLACK, "Pawn");
    m_board[1][7].setPiece(BLACK, "Pawn");

    //Set up all of the black pieces on the board.
    m_board[7][0].setPiece(WHITE, "Rook");
    m_board[7][1].setPiece(WHITE, "Knight");
    m_board[7][2].setPiece(WHITE, "Bishop");
    m_board[7][3].setPiece(WHITE, "Queen");
    m_board[7][4].setPiece(WHITE, "King");
    m_board[7][5].setPiece(WHITE, "Bishop");
    m_board[7][6].setPiece(WHITE, "Knight");
    m_board[7][7].setPiece(WHITE, "Rook");
    m_board[6][0].setPiece(WHITE, "Pawn");
    m_board[6][1].setPiece(WHITE, "Pawn");
    m_board[6][2].setPiece(WHITE, "Pawn");
    m_board[6][3].setPiece(WHITE, "Pawn");
    m_board[6][4].setPiece(WHITE, "Pawn");
    m_board[6][5].setPiece(WHITE, "Pawn");
    m_board[6][6].setPiece(WHITE, "Pawn");
    m_board[6][7].setPiece(WHITE, "Pawn");
}

bool CG_board::move(int f_source, int r_source, int f_dest, int r_dest)
{
    bool move_made = false;

    //If the square selected has a piece in it.
    if(m_board[f_source][r_source].getPiece() != nullptr)
    {
        //If the destination doesn't have a piece
        //or the destination has a piece of a different color
        if(m_board[f_dest][r_dest].getPiece() == nullptr ||
           m_board[f_source][r_source].getPiece()->getPieceColor() !=
           m_board[f_dest][r_dest].getPiece()->getPieceColor())
        {
            //If the piece can actually make that movement pattern
            if(m_board[f_source][r_source].getPiece()->move((File) f_source, (Rank) r_source, (File) f_dest, (Rank) r_dest))
            {
                if(CheckForClearPath( f_source, r_source, f_dest, r_dest))
                {
                    //Move the piece from its source to the destination.
                    m_board[f_dest][r_dest].setPiece(m_board[f_source][r_source].getPiece());
                    m_board[f_source][r_source].setPiece();
                    move_made = true;
                }
            }
        }
    }

    return move_made;

    //Make the destination CG_square hold the CG_piece from the source CG_square,
    //and make the source CG_square hold a null pointer to a CG_piece.
    //Thus, this empties the source CG_square of its CG_piece.
    //m_board[f_dest][r_dest].setPiece(m_board[f_source][r_source].getPiece());
    //m_board[f_source][r_source].setPiece(0);
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

bool CG_board::CheckForClearPath(int f_to, int r_to, int f_from, int r_from)
{
    bool path_clear = true;

    //If the movement matches that of a rook's movement patterns,
    //meaning it is moving vertically or horizontally.
    if ( f_to == f_from || r_to == r_from )
    {
        CheckRookMovement(f_to, r_to, f_from, r_from, path_clear);
    }
    //If the movement matches that of a bishop's movement patterns,
    //meaning it is moving diagonally.
    else if ( abs(f_from - f_to) == abs(r_to - r_from) )
    {
        CheckBishopMovement(f_to, r_to, f_from, r_from, path_clear);
    }

    return path_clear;
}

void CG_board::CheckRookMovement(int f_source, int r_source, int f_dest, int r_dest, bool & valid)
{

    //This checks a vertical movement on the board for any pieces
    //inbetween the source and destination squares.
    if ( f_source == f_dest )
    {
        //This loop should check every square inbetween the source and
        //destination squares to see if a piece exists in that square.
        for(int i = r_dest < r_source ? r_dest + 1 : r_source + 1;
            (i < (r_dest < r_source ? r_source : r_dest)) && valid;
            i++)
        {
            //If a square in the path contains a piece, then the
            //movement cannot be a valid movement.
            if(m_board[f_dest][i].getPiece() != nullptr)
            {
                valid = false;
            }
        }
    }
    else //Same thing as vertical, except for horizontal movement.
    {
        //This loop should check every square inbetween the source and
        //destination squares to see if a piece exists in that square.
        for(int i = f_dest < f_source ? f_dest + 1 : f_source + 1;
            (i < (f_dest < f_source ? f_source : f_dest)) && valid;
            i++)
        {
            //If a square in the path contains a piece, then the
            //movement cannot be a valid movement.
            if(m_board[i][r_dest].getPiece() != nullptr)
            {
                valid = false;
            }
        }
    }
}

void CG_board::CheckBishopMovement(int f_source, int r_source, int f_dest, int r_dest, bool &valid)
{
    //These variables help decide how to adjust the file and rank
    //when checking the squares diagonally.  If the file source
    //is larger than the file destination, it will set the movement
    //pattern to move down by 1 (-1) each time, or vice versa.
    int f_movement = f_source > f_dest ? -1 : 1;
    int r_movement = r_source > r_dest ? -1 : 1;

    //This is going to check each square inbetween the source and destination
    //diagonally to see if a piece exists in any of those squares.
    //If a piece is found, then the movement isn't valid.
    for( int i = f_source + f_movement,
         j = r_source + r_movement;
         i != f_dest && j != r_dest;
         i += f_movement, j += r_movement)
    {
        //If a square in the path has a piece in it, then the
        //movement cannot be a valid movement.
        if(m_board[i][j].getPiece() != nullptr)
        {
            valid = false;
        }
    }

}
