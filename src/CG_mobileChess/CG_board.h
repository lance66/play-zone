#ifndef CG_BOARD_H
#define CG_BOARD_H

#include <QObject>
#include <QString>
#include "CG_history.h"
#include "CG_square.h"

class CG_board : public QObject
{
    Q_OBJECT

public:
    //Default constructor
    CG_board();
    //Copy COnstructor
    CG_board(const CG_board & copy);

public slots:

    bool move(int f_source, int r_source, int f_dest, int r_dest);
    void callHistoryBackward();
    void callHistoryForward();
    QString getSquare(int source_file, int source_rank);
    void resetBoard();

    bool CheckForClearPath(int f_source, int r_source, int f_dest, int r_dest);
    void CheckRookMovement(int f_source, int r_source, int f_dest, int r_dest, bool & valid);
    void CheckBishopMovement(int f_source, int r_source, int f_dest, int r_dest, bool & valid);
    bool CheckKingInCheck( int f_source, int r_source, int f_dest, int r_dest );

private:
    CG_square m_board[8][8];
    CG_history m_history;
    bool m_whiteToMove;
};

#endif // CG_BOARD_H
