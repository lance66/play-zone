#ifndef CG_Server_H
#define CG_Server_H

#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QQueue>
#include <QList>
#include <QMap>
#include <QString>
#include <QSignalMapper>
#include "CG_match.h"
#include "CG_playerConnection.h"
#include <QTimer>

/************************************************************************
* Class: CG_Server
*
* Constructors:
*   explicit CG_Server(QObject *parent = 0);
*
* Slots:
*   void clientDisconnected()
*       Detects that a client disconnected from the server
*       and removes the client.
*
* Methods:
*   void StartServer()
*       Starts the server.
*   void incomingConnection(qintptr socketDescriptor)
*       Accepts any pending connections.
*   void sendMove(QTcpSocket *client)
*       Sends the move to the client
*   void addPlayerConnection(QTcpSocket *chessPlayer)
*       Adds a player connection to the list of connections.
*   void startOneMinuteMatch()
*       Starts a one minute match, when there are two or more players
*   void removeAllClientConnections(QTcpSocket *client)
*       Removes all clients from the connection's list.
*   void writeSocketDescriptorToSocket(QTcpSocket *client, qintptr socketDescriptor)
*       Follows a series of conversions to write socketDescriptor
*       to the socket.
*************************************************************************/
class CG_Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit CG_Server(QObject *parent = 0);
    ~CG_Server();
    void StartServer();
    int getPlayerCount();
    int getMatchCount();
    int getQueueCount();

signals:
    void playersReadyToBeMatched();

public slots:

protected slots:
    void clientDisconnected();
    void handleJoinQueue(TimeControl time_type);
    void queueTimerExpired();

protected:
    void incomingConnection(qintptr socketDescriptor);

    QList<CG_playerConnection*>  m_connectedPlayers;
    QList<CG_playerConnection*>  m_minuteQueue;
    QList<CG_playerConnection*>  m_fiveMinuteQueue;
    QList<CG_playerConnection*>  m_thirtyMinuteQueue;
    QList<CG_Match *>            m_openMatches;
    QTimer                       m_queueConnectTimer;

private:
    void addPlayerConnection(QTcpSocket *chessPlayer);
    void removeAllClientConnections(QTcpSocket *client);
};

#endif // CG_Server_H

// TODO -- sendCheckMate()
// TODO -- sendResignation()
// TODO -- sendDrawOffer()
// TODO -- sendDrawOfferAccepted()
// TODO -- sendStaleMate()
// TODO -- sendFiftyMoveRule()
// TODO -- sendThreeFoldRepetition()
// TODO -- sendDisconnected()
// TODO -- sendGameOver()
// TODO -- addPlayerToQueue()
// TODO -- removePlayerFromQueue()
// TODO -- kickPlayer()
