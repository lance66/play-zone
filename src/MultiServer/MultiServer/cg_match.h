#ifndef CG_MATCH_H
#define CG_MATCH_H

#include <QDebug>
#include <QTcpSocket>
#include <QMap>
#include <QString>

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
        //CG_Match(userInfo whitePlayer, userInfo blackPlayer, int timeControl);
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
        void setIsWhiteToMove(bool &isWhiteToMove);
        QTcpSocket * getTcpSocket() const;

        void startMatch(int whiteID, int blackID, QTcpSocket *whiteSocket, QTcpSocket *blackSocket);

    private:
        int whiteID;
        int blackID;
        bool isWhiteToMove;
        bool isMatchOver;
        QTcpSocket *whiteSocket;
        QTcpSocket *blackSocket;
        QTcpSocket *socket;
        int matchID;
        int winner;
        int loser;
        int status;
        int timeControl;
        QString startTime;
        QString endTime;
        double whiteTime;
        double blackTime;

        //ChessClock whiteClock
        //ChessClock blackClock
        //UserInfo whitePlayer
        //UserInfo blackPlayer
        //UserInfo kibitzers
        //int eloWon
        //int eloLost

        void readPlayersMove(QTcpSocket *playerSocket, QByteArray move);
        void setPlayerIDs(int whteID, int blckID);
        void setPlayerSockets(QTcpSocket *whiteSocket, QTcpSocket *blackSocket);
};

#endif // CG_MATCH_H
