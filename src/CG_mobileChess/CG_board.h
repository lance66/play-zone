#ifndef CG_BOARD_H
#define CG_BOARD_H

#include <QObject>
#include <QString>
#include "CG_square.h"

//enum CG_Color {WHITE, BLACK};

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
//        if(m_board[f_source][r_source].getPiece() != 0)
//        {
//            if(m_board[f_dest][r_dest].getPiece() == 0)
//            {
//                if(m_board[f_source][r_source].getPiece()->move((File) f_source, (Rank) r_source, (File) f_dest, (Rank) r_dest))
//                {
//                    m_board[f_dest][r_dest].setPiece(m_board[f_source][r_source].getPiece());
//                    m_board[f_source][r_source].setPiece(0);
//                }
//            }
//        }
//    }
//    QString getSquare(int source_file, int source_rank)
//    {
//        // Temporary just for testing
//        return "Pawn0";

//        // The below should be uncommented and the above deleted once m_board is filled
//        //return m_board[source_file][source_rank].getPieceName() + ((QString) m_board[source_file][source_rank].getPiece()->getPieceColor());
//    }

private:
    CG_piece * m_board[8][8];
    CG_square enPassant;
    CG_Color turn;

    //CG_square m_board[8][8];
};

#endif // CG_BOARD_H
