#ifndef CG_BOARD_H
#define CG_BOARD_H

#include <QObject>
#include <QString>
#include "CG_square.h"

class CG_board : public QObject
{
    Q_OBJECT

public:
    //Default constructor
    CG_board();

    //Member functions
    CG_piece *piecePosition(CG_square square);
    CG_piece *piecePosition(File file, Rank rank);
    void move(CG_square from, CG_square to);
    void move(CG_square from, CG_square to, CG_square enPassant);
    void tryMove(CG_square from, CG_square to);

public slots:


//    void move(int f_source, int r_source, int f_dest, int r_dest)
//    {
//        if(m_board[f_source][r_source] != 0)
//        {
//            if(m_board[f_dest][r_dest] == 0)
//            {
//                if(m_board[f_source][r_source]->move((File)f_source, r_source, (File)f_dest, r_dest))
//                {
//                    m_board[f_dest][r_dest] = m_board[f_source][r_source];
//                    m_board[f_source][r_source] = 0;
//                }
//            }
//        }
//    }


    void move(int f_source, int r_source, int f_dest, int r_dest)
    {
        if(m_board[f_source][r_source].getPiece() != nullptr)
        {
            if(m_board[f_dest][r_dest].getPiece() == nullptr)
            {
                if(m_board[f_source][r_source].getPiece()->move((File) f_source, (Rank) r_source, (File) f_dest, (Rank) r_dest))
                {
                    m_board[f_dest][r_dest].setPiece(m_board[f_source][r_source].getPiece());
                    m_board[f_source][r_source].setPiece(0);
                }
            }
        }

        //CG_square temp = m_board[f_source][r_source].getPiece();

    }
    QString getSquare(int source_file, int source_rank)
    {
        //Black pieces
        /*if(source_file == 0 && source_rank == 0)
            return "Rook1";
        else if (source_file == 1 && source_rank == 0)
            return "Knight1";
        else if (source_file == 2 && source_rank == 0)
            return "Bishop1";
        else if (source_file == 3 && source_rank == 0)
            return "Queen1";
        else if (source_file == 4 && source_rank == 0)
            return "King1";
        else if (source_file == 5 && source_rank == 0)
            return "Bishop1";
        else if (source_file == 6 && source_rank == 0)
            return "Knight1";
        if(source_file == 7 && source_rank == 0)
            return "Rook1";

        //White pieces
        else if (source_file == 0 && source_rank == 7)
            return "Rook0";
        else if (source_file == 1 && source_rank == 7)
            return "Knight0";
        else if (source_file == 2 && source_rank == 7)
            return "Bishop0";
        else if (source_file == 3 && source_rank == 7)
            return "Queen0";
        else if (source_file == 4 && source_rank == 7)
            return "King0";
        else if (source_file == 5 && source_rank == 7)
            return "Bishop0";
        else if (source_file == 6 && source_rank == 7)
            return "Knight0";
        else if (source_file == 7 && source_rank == 7)
            return "Rook0";

        //Don't forget about the pawns

        //Black pawns
        else if(source_rank == 1)
            return "Pawn1";

        //White pawns
        else if(source_rank == 6)
            return "Pawn0";

        //Empty squares
        else
            return "";*/

        // The below should be uncommented and the above deleted once m_board is filled
        char temp = '\0';

        if (m_board[source_file][source_rank].getPiece() != nullptr)
            temp = m_board[source_file][source_rank].getPiece()->getPieceColor() + 48;

        return m_board[source_file][source_rank].getPieceName() + QString(temp);
    }

private:
    //CG_piece * m_board[8][8];
    //CG_Color turn;

    CG_square m_board[8][8];
};

#endif // CG_BOARD_H
