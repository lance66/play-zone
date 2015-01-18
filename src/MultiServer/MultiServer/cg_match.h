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
        CG_Match(int whiteID, int blackID, QTcpSocket *&whiteSocket, QTcpSocket *&blackSocket);
        ~CG_Match();

        void sendMoveToServer(int whiteID, int blackID);

        void setWhiteID(int whiteID);
        int getWhiteID();

        void setBlackID(int blackID);
        int getBlackID();

        void setWhiteSocket(QTcpSocket *socket);
        void setBlackSocket(QTcpSocket *socket);

        void setTcpSocket(QTcpSocket *socket);
        QTcpSocket * getTcpSocket();

        void setIsWhiteToMove(bool &isWhiteToMove);

    private:
        int whiteID;
        int blackID;
        bool isWhiteToMove;
        QTcpSocket *whiteSocket;
        QTcpSocket *blackSocket;
        QTcpSocket *socket;

        void readPlayersMove(QTcpSocket *playerSocket, QByteArray move);
        void setPlayerIDs(int whteID, int blckID);
        void setPlayerSockets(QTcpSocket *whiteSocket, QTcpSocket *blackSocket);
};

#endif // CG_MATCH_H
