#ifndef CG_BOARD_H
#define CG_BOARD_H

#include <QObject>
#include <QString>
#include "CG_square.h"

class CG_board : public QObject
{
    Q_OBJECT

public:
    CG_board();

public slots:
    void move(int f_source, int r_source, int f_dest, int r_dest)
    {
        if(m_board[f_source][r_source].getPiece() != 0)
        {
            if(m_board[f_dest][r_dest].getPiece() == 0)
            {
                if(m_board[f_source][r_source].getPiece()->move((File) f_source, (Rank) r_source, (File) f_dest, (Rank) r_dest))
                {
                    m_board[f_dest][r_dest].setPiece(m_board[f_source][r_source].getPiece());
                    m_board[f_source][r_source].setPiece(0);
                }
            }
        }
    }
    QString getSquare(int source_file, int source_rank)
    {
        return m_board[source_file][source_rank].getPieceName() + ((QString) m_board[source_file][source_rank].getPiece()->getPieceColor());
    }

private:
    CG_square m_board[8][8];
};

#endif // CG_BOARD_H
