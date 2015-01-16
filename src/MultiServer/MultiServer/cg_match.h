#ifndef CG_MATCH_H
#define CG_MATCH_H

#include <QDebug>
#include <QTcpSocket>

/************************************************************************
* Class: CG_Match
*
* Constructors:
*	CG_Match()
*   CG_Match(int whiteID, int blackID)
*
* Methods:
*   void sendMoveToServer(int whiteID, int blackID);
*       Sends move to the server.
*   void setWhiteID(int whiteID)
*       sets the id for white
*   int getWhiteID()
*       gets the id for white
*   void setBlackID(int blackID)
*       sets the id for black
*   int getBlackID()
*       gets the id for black
*
*   void setTcpSocket(QTcpSocket *socket);
*   QTcpSocket * getTcpSocket();
*************************************************************************/
class CG_Match
{
    public:
        CG_Match();
        CG_Match(int whiteID, int blackID, QTcpSocket *whiteSocket, QTcpSocket *blackSocket);

        void sendMoveToServer(int whiteID, int blackID);

        void setWhiteID(int whiteID);
        int getWhiteID();

        void setBlackID(int blackID);
        int getBlackID();

        void setIsWhiteToMove(bool &isWhiteToMove);

        void setTcpSocket(QTcpSocket *socket);
        QTcpSocket * getTcpSocket();

    private:
        int whiteID;
        int blackID;
        bool isWhiteToMove;
        QTcpSocket *whiteSocket;
        QTcpSocket *blackSocket;
        QTcpSocket *socket;
};

#endif // CG_MATCH_H
