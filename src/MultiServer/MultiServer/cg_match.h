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
*   void sendMoveToServer(int whiteID, int blackID)
*       Sends move to the server.
*   void setWhiteID(int whiteID)
*       Sets the id for white.
*   int getWhiteID()const
*       Gets the id for white.
*   void setBlackID(int blackID)
*       Sets the id for black.
*   int getBlackID()const
*       Gets the id for black.
*
*   void setWhiteSocket(QMap<int, QTcpSocket *> socket, int whiteID)
*       Sets up the white players socket.
*   void setBlackSocket(QMap<int, QTcpSocket *> socket, int blackID)
*       Sets up the black players socket.
*   void setTcpSocket(QTcpSocket *socket)
*       Sets up the tcp socket for the players.
*   void setIsWhiteToMove(bool &isWhiteToMove)
*       Helps determine who has the legal move.
*   QTcpSocket * getTcpSocket() const
*       Gets the players TCP socket.
*   void setTcpSocket(QTcpSocket *socket)
*       Sets up the players TCP socket.
*   QTcpSocket * getTcpSocket() const
*       Gets the players socket.
*
*   void readPlayersMove(QTcpSocket *playerSocket, QByteArray move)
*       Reads the players move, and writes it to the socket.
*   void setPlayerIDs(int whteID, int blckID)
*       Sets up the player ids for the match.
*   void setPlayerSockets(QTcpSocket *whiteSocket, QTcpSocket *blackSocket)
*       Sets up the players socket.
*   char const * convertIDToCharConstPtr(int playerID)
*       Converts the id's from integers to character constant pointers.
*   void notifyPlayersOfMatchStarting(QTcpSocket *&whiteSocket, QTcpSocket *&blackSocket, char const * blackPlayer, char const * whitePlayer)
*       Notifies the players that the match is starting.
*   void notifyPlayerOfMatchStarting(QTcpSocket *&playerSocket, char const * player, char const * msg)
*       Notifies players of the the colored pieces they are playing as,
*       and with who they are playing against.
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
        char const * convertIDToCharConstPtr(int playerID);
        void notifyPlayersOfMatchStarting(QTcpSocket *&whiteSocket, QTcpSocket *&blackSocket, char const * blackPlayer, char const * whitePlayer);
        void notifyPlayerOfMatchStarting(QTcpSocket *&playerSocket, char const * player, char const * msg);
};

#endif // CG_MATCH_H
