#ifndef CG_MATCH_H
#define CG_MATCH_H

#include <QDebug>
#include <QTcpSocket>

class CG_Match
{
public:
    CG_Match();
    CG_Match(int whiteID, int blackID);

    void sendMoveToServer(int whiteID, int blackID);

    int whiteID;
    int blackID;
    QTcpSocket *socket;
};

#endif // CG_MATCH_H
