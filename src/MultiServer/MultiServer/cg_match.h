#ifndef CG_MATCH_H
#define CG_MATCH_H

#include <QDebug>
#include <QTcpSocket>
#include <QMap>

/************************************************************************
* Class: CG_Match
*
* This class is used when two clients connect into a chess match.  It
* serves the purpose of maintaining the information of the two clients,
* and managing their communication of moves between one another.
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
*   int getWhiteID()const
*       gets the id for white
*   void setBlackID(int blackID)
*       sets the id for black
*   int getBlackID()const
*       gets the id for black
*
*   void setTcpSocket(QTcpSocket *socket);
*   QTcpSocket * getTcpSocket() const;
*************************************************************************/

class CG_Match
{
    public:
        CG_Match();
        CG_Match(int whiteID, int blackID, QTcpSocket *&whiteSocket, QTcpSocket *&blackSocket);
        ~CG_Match();

        void sendMoveToServer(int whiteID, int blackID);

        void setWhiteID(int whiteID);
        int getWhiteID() const;

        void setBlackID(int blackID);
        int getBlackID() const;

        void setWhiteSocket(QMap<int, QTcpSocket *> socket, int whiteID);
        void setBlackSocket(QMap<int, QTcpSocket *> socket, int blackID);

        void setTcpSocket(QTcpSocket *socket);
        QTcpSocket * getTcpSocket() const;

        void setIsWhiteToMove(bool &isWhiteToMove);

        void startMatch(int whiteID, int blackID, QTcpSocket *whiteSocket, QTcpSocket *blackSocket);

    private:
        int whiteID;
        int blackID;
        bool isWhiteToMove;
        bool isMatchOver;
        QTcpSocket *whiteSocket;
        QTcpSocket *blackSocket;
        QTcpSocket *socket;

        void readPlayersMove(QTcpSocket *playerSocket, QByteArray move);
        void setPlayerIDs(int whteID, int blckID);
        void setPlayerSockets(QTcpSocket *whiteSocket, QTcpSocket *blackSocket);
};

#endif // CG_MATCH_H
