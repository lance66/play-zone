#ifndef CG_MATCH_H
#define CG_MATCH_H

#include <QDebug>
#include <QTcpSocket>
#include <QMap>
#include <QString>
#include <QQueue>
#include "CG_playerConnection.h"

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
class CG_Match : public QObject
{
    public:
        CG_Match(CG_playerConnection* player1,CG_playerConnection* player2, int time_control, QObject * parent);
        ~CG_Match();

        void startMatch();
        void setWhitePlayerConnection(CG_playerConnection *whitePlayerConnection);
        void setBlackPlayerConnection(CG_playerConnection *blackPlayerConnection);

    public slots:
        void onWhitePlayerMove(int startRank, int startFile,int endRank, int endFile);
        void onBlackPlayerMove(int startRank, int startFile,int endRank, int endFile);
        void onPlayerReady();
    private:
        CG_playerConnection * m_whitePlayerConnection;
        CG_playerConnection * m_blackPlayerConnection;
        bool m_whiteReady;
        bool m_blackReady;
        int  m_timeControl;
};

#endif // CG_MATCH_H
