#include "CG_board.h"
#include <QDebug>
#include <math.h>

//Default constructor
CG_board::CG_board() : m_board(), m_whiteToMove(true)
{
    //Set up all of the black pieces on the board.
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

    for (int row = 2; row < 7; row++)
        for (int col = 0; col < 8; col++)
            m_board[row][col].setPiece(nullptr);

    //Set up all of the white pieces on the board.
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

    //initBlackView();

    //startOfGameFlipBoard();

    CG_square tempFrom;
    CG_square tempTo;

    m_history.setNext(m_board, tempFrom, tempTo);
}

void CG_board::initBlackView()
{

    //Set up the squares

    //Set up all of the black pieces on the board.
    m_board[0][0].setPiece(WHITE, "Rook");
    m_board[0][1].setPiece(WHITE, "Knight");
    m_board[0][2].setPiece(WHITE, "Bishop");
    m_board[0][3].setPiece(WHITE, "King");
    m_board[0][4].setPiece(WHITE, "Queen");
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

    for (int row = 2; row < 7; row++)
        for (int col = 0; col < 8; col++)
            m_board[row][col].setPiece(nullptr);

    //Set up all of the white pieces on the board.
    m_board[7][0].setPiece(BLACK, "Rook");
    m_board[7][1].setPiece(BLACK, "Knight");
    m_board[7][2].setPiece(BLACK, "Bishop");
    m_board[7][3].setPiece(BLACK, "King");
    m_board[7][4].setPiece(BLACK, "Queen");
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

    for(int file = 0; file < 8; file++)
    {
        m_board[1][file].getPiece()->ToggleDirection();
    }

    for(int file = 0; file < 8; file++)
        m_board[6][file].getPiece()->ToggleDirection();

    CG_square tempFrom;
    CG_square tempTo;

    m_history.setNext(m_board, tempFrom, tempTo);
}

CG_board::CG_board(const CG_board & copy ) : m_board(), m_whiteToMove(copy.m_whiteToMove), m_history(m_board)
{
    for ( int rank = 1; rank <= 8; rank++)
    {
        for ( int file = 1; file <= 8; file++)
        {
            m_board[file-1][rank-1].setSquare((File)file, rank);
            if ( copy.m_board[file-1][rank-1].getPiece() != nullptr )
            {
                m_board[file-1][rank-1].setPiece(CG_Color(copy.m_board[file-1][rank-1].getPiece()->getPieceColor()),
                                                 copy.m_board[file-1][rank-1].getPiece()->getPieceName());
            }
            else
            {
                m_board[file-1][rank-1].setPiece();
            }
        }
    }
}

bool CG_board::move(int f_source, int r_source, int f_dest, int r_dest, int translation)
{
    bool move_made = false;

    CG_Color currentPlayer = m_whiteToMove ? WHITE : BLACK;

    m_whiteToMove ? qDebug() << "White moves" : qDebug() << "Black moves";
    qDebug() << "From file " << f_source;
    qDebug() << "From rank " << r_source;
    qDebug() << "To file " << f_dest;
    qDebug() << "To rank " << r_dest;

    qDebug() << "---------------";
    qDebug() << "White To Move: " << m_whiteToMove;
    qDebug() << "Current Player: " << currentPlayer;
    qDebug() << "Current Piece: " << m_board[f_source][r_source].getPiece()->getPieceColor();


    // If the square selected has a piece in it.
    if(m_board[f_source][r_source].getPiece() != nullptr)
    {
        // If the piece selected is of the color of the player moving,
        // continue onward.  Otherwise, this is an invalid move.
        // White pieces cannot be moved unless it is the white player moving them,
        // and vice versa for black.

        //if((m_board[f_source][r_source].getPiece()->getPieceColor() == currentPlayer))
        //{

            // If the piece being moved is a King and the destination doesn't have
            // a piece in it, and the king is actually moving only by rank.
            if (m_board[f_source][r_source].getPiece()->getPieceName() == "King"
                && m_board[f_dest][r_dest].getPiece() == nullptr
                && abs(r_source - r_dest) == 2 && abs(f_source - f_dest) == 0
                && static_cast<CG_king *>(m_board[f_source][r_source].getPiece())->getHasMoved() == false)
            {
                //This figures out which rank to use.  If the king is moving right,
                //the rank should be the rook on the right, and vice versa.
                int rook_rank = 7 == (r_dest + 1) ? 7 : 0;

                if ( translation == 7 )
                {
                    rook_rank = 0 == (r_dest - 1) ? 0 : 7;
                }

                //This determines what side to put the rook on after castling.
                //If the King castled right, the Rook should be on the King's left,
                //and vice versa.
                int rook_side = rook_rank == 0 ? 1 : -1;

                //We need to make sure that the Rook is in the proper place, that it is of the same color,
                //and that it hasn't moved.
                if(m_board[f_source][r_source].getPiece()->move((File) f_source, (Rank) r_source, (File) f_dest, (Rank) r_dest)
                   && (m_board[f_source][rook_rank].getPiece()->getPieceColor() == currentPlayer &&
                       m_board[f_source][rook_rank].getPiece()->getPieceName() == "Rook" &&
                       static_cast<CG_rook *>(m_board[f_source][rook_rank].getPiece())->getHasMoved() == false))
                {
                    //Check to see if the path between the King and the Rook is clear.
                    if(CheckForClearPath( f_source, r_source, f_source, rook_rank))
                    {
                        //Check to see if the King were to move, would the King be in check.
                        if ( !CheckKingInCheck(f_source, r_source, f_dest, r_dest))
                        {
                            m_board[f_dest][r_dest].setPiece(m_board[f_source][r_source].getPiece());
                            m_board[f_dest][r_dest].getPiece()->UpdatePiece();
                            m_board[f_source][r_source].setPiece();

                            m_board[f_dest][r_dest+rook_side].setPiece(m_board[f_source][rook_rank].getPiece());
                            m_board[f_dest][r_dest+rook_side].getPiece()->UpdatePiece();
                            m_board[f_dest][rook_rank].setPiece();
                            move_made = true;
                            m_whiteToMove = !m_whiteToMove;
                        }
                    }
                }
            }
            //If the destination doesn't have a piece
            //or the destination has a piece of a different color
            else if(m_board[f_dest][r_dest].getPiece() == nullptr ||
               m_board[f_source][r_source].getPiece()->getPieceColor() !=
               m_board[f_dest][r_dest].getPiece()->getPieceColor())
            {
                //If the piece can actually make that movement pattern
                if(m_board[f_source][r_source].getPiece()->move((File) f_source, (Rank) r_source, (File) f_dest, (Rank) r_dest))
                {
                    if(CheckForClearPath( f_source, r_source, f_dest, r_dest))
                    {
                        //Make a check to see if the moving player's king would be
                        //in check after that move would be made.  If so, then that
                        //movement cannot be made.
                        if ( !CheckKingInCheck( f_source, r_source, f_dest, r_dest ))
                        {
                            //Move the piece from its source to the destination.
                            m_board[f_dest][r_dest].setPiece(m_board[f_source][r_source].getPiece());
                            //Update the piece to show that it has moved.
                            m_board[f_dest][r_dest].getPiece()->UpdatePiece();
                            //Remove the piece from its original location.
                            m_board[f_source][r_source].setPiece();
                            move_made = true;
                            m_whiteToMove = !m_whiteToMove;

                            //Add move to history list
                            m_history.setNext(m_board, m_board[f_source][r_source], m_board[f_dest][r_dest]);

                        }
                    }
                }
            }
        //}
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
        temp = m_board[source_file][source_rank].getPiece()->getPieceColor() ? '1' : '0';
        //temp = m_board[source_file][source_rank].getPiece()->getPieceColor() + 48;
        //ret_str += QString(temp);
        ret_str.append(temp);
    }

    //Return the QString representing the CG_piece in the CG_square.
    return ret_str;
}

bool CG_board::getPieceColorAt(int source_file, int source_rank)
{
    //Get the piece
    CG_piece * tempPiece = m_board[source_file][source_rank].getPiece();

    return tempPiece != nullptr ? tempPiece->getPieceColor() : false;
}

bool CG_board::CheckForClearPath(int f_to, int r_to, int f_from, int r_from)
{
    bool path_clear = true;
    QString pieceName = "";

    if ( m_board[f_to][r_to].getPiece() != nullptr )
    {
        pieceName = m_board[f_to][r_to].getPiece()->getPieceName();
    }

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

void CG_board::resetBoard()
{
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

    for (int row = 2; row < 7; row++)
        for (int col = 0; col < 8; col++)
            m_board[row][col].setPiece(nullptr);

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

    //Reset board history
    m_history.resetHistory();

    //Reset white to first
    m_whiteToMove = true;
}

void CG_board::flipBoard()
{
    for (int rank = 0; rank < 4; ++rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            CG_square temp;
            temp.setSquare(File(7 - rank), file);
            temp.setPiece(m_board[7 - rank][file].getPiece());

            m_board[7 - rank][file].setSquare(File(rank), file);
            m_board[7 - rank][file].setPiece(m_board[rank][file].getPiece());

            m_board[rank][file].setSquare(temp.getFile(), temp.getRank());
            m_board[rank][file].setPiece(temp.getPiece());
        }
    }
}

void CG_board::startOfGameFlipBoard()
{
    flipBoard();

    int king_queen_rank = -1;
    int king_file = -1;
    int queen_file = -1;

    for (int rank = 0; rank < 4; ++rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            if (m_board[rank][file].getPieceName() == "King")
            {
                king_file = file;
                king_queen_rank = rank;
            }
            else if (m_board[rank][file].getPieceName() == "Queen")
            {
                queen_file = file;
                king_queen_rank = rank;
            }
            else if (m_board[rank][file].getPieceName() == "Pawn")
                m_board[rank][file].getPiece()->ToggleDirection();
        }
    }

    CG_square temp;
    temp.setSquare(File(king_queen_rank), king_file);
    temp.setPiece(m_board[king_queen_rank][king_file].getPiece());

    m_board[king_queen_rank][queen_file].setSquare(File(king_queen_rank), king_file);
    m_board[king_queen_rank][queen_file].setPiece(m_board[king_queen_rank][king_file].getPiece());

    m_board[king_queen_rank][king_file].setSquare(temp.getFile(), temp.getRank());
    m_board[king_queen_rank][king_file].setPiece(temp.getPiece());
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

bool CG_board::CheckKingInCheck(int f_source, int r_source, int f_dest, int r_dest)
{
    bool king_inCheck = false;
    CG_board temp_board(*this);
    int king_rank = 1;
    int king_file = 1;
    bool king_found = false;
    CG_Color playerMoving = m_whiteToMove ? WHITE : BLACK;

    //This finds the king of the player currently moving pieces.
    for( int rank = 1; rank <= 8 && !king_found; rank++ )
    {
        for( int file = 1; file <= 8 && !king_found; file++ )
        {
            //If the king of the player currently moving pieces exists in this location,
            //mark that location for future use in the method.
            if( temp_board.m_board[file-1][rank-1].getPiece() != nullptr &&
                (CG_Color(temp_board.m_board[file-1][rank-1].getPiece()->getPieceColor()) == playerMoving)
                && temp_board.m_board[file-1][rank-1].getPiece()->getPieceName() == "King"
              )
            {
                king_rank = rank;
                king_file = file;
                king_found = true;
            }
        }
    }

    //If the king is the piece moving, we'll update our king_rank & king_file
    //to show that for validation purposes.
    if ( king_rank == r_source + 1 && king_file == f_source + 1 )
    {
        king_rank = r_dest + 1;
        king_file = f_dest + 1;
    }

    //Move the piece on the temporary board to test the movement out.
    temp_board.m_board[f_dest][r_dest].setPiece(temp_board.m_board[f_source][r_source].getPiece());
    temp_board.m_board[f_source][r_source].setPiece();


    //Check to see if any of the opposing player's pieces is capable of taking the
    //king of the player currently moving pieces.
    for ( int rank = 1; rank <= 8 && !king_inCheck; rank++ )
    {
        for ( int file = 1; file <= 8 && !king_inCheck; file++ )
        {
            if ( temp_board.m_board[file-1][rank-1].getPiece() != nullptr
                 && temp_board.m_board[file-1][rank-1].getPiece()->getPieceColor() != playerMoving )
            {
                if ( temp_board.m_board[file-1][rank-1].getPiece()->move(File(king_file-1),
                                     Rank(king_rank-1), File(file-1), Rank(rank-1)))
                {
                    if (temp_board.CheckForClearPath(file-1, rank-1, king_file-1, king_rank-1))
                    {
                        king_inCheck = true;
                    }
                }
            }
        }
    }

    return king_inCheck;
}

void CG_board::callHistoryBackward()
{
    m_history.moveBack();

    //Set each individual square in board to temp
    for(int rank = 0; rank < NUMBER_OF_RANKS; rank++)
    {
        for (int file = 0; file < NUMBER_OF_RANKS; file++)
        {
            qDebug() << "New rank: "  << m_history.getCurrentBoard()[rank][file].getRank();
            qDebug() << "New file: "  << m_history.getCurrentBoard()[rank][file].getFile();
            qDebug() << "New piece: " << m_history.getCurrentBoard()[rank][file].getPiece();
            qDebug() << "-----------";

            m_board[rank][file].setRank(m_history.getCurrentBoard()[rank][file].getRank());
            m_board[rank][file].setFile(m_history.getCurrentBoard()[rank][file].getFile());
            m_board[rank][file].setPiece(m_history.getCurrentBoard()[rank][file].getPiece());
        }
    }
}

void CG_board::callHistoryForward()
{
    m_history.moveForward();

    //Set each individual square in board to temp
    for(int rank = 0; rank < NUMBER_OF_RANKS; rank++)
    {
        for (int file = 0; file < NUMBER_OF_RANKS; file++)
        {
            m_board[rank][file].setRank(m_history.getCurrentBoard()[rank][file].getRank());
            m_board[rank][file].setFile(m_history.getCurrentBoard()[rank][file].getFile());
            m_board[rank][file].setPiece(m_history.getCurrentBoard()[rank][file].getPiece());
        }
    }
}
