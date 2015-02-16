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

public slots:

    void move(int f_source, int r_source, int f_dest, int r_dest);

    QString getSquare(int source_file, int source_rank);

private:
    CG_square m_board[8][8];
};

#endif // CG_BOARD_H
