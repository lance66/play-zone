#include "CG_server.h"
#include <iostream>

/****************************************************************
*   Purpose:  Constructor.  Initializes QTcpServer
*
*     Entry:  NA
*
*      Exit:  Data members are initialized.
****************************************************************/

CG_Server::CG_Server(QObject *parent) : QTcpServer(parent)
{
    qDebug() << "Welcome to the Chessgames Mobile Server!";

    //When queue is ready, match players and start match
    //connect(this, SIGNAL(playersReadyToBeMatched()), this, SLOT(startOneMinuteMatch()));
    m_queueConnectTimer.setInterval(1000);
    m_queueConnectTimer.stop();
    connect(&m_queueConnectTimer, &QTimer::timeout, this, &CG_Server::queueTimerExpired);

}

//Document header needed
CG_Server::~CG_Server()
{
    qDebug() << "Chessgames Mobile Server has been shutdown!";
}

/****************************************************************
*   Purpose:  Starts the server, and notifies user that it is
*             listening for connections.
*
*     Entry:  Called after an instances of a CG_Server object is
*             created.
*
*      Exit:  Starts the server.
****************************************************************/
void CG_Server::StartServer()
{
    //QHostAddress add("192.168.1.100");
    if(!this->listen(QHostAddress::LocalHost,9556))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Chessgames server started!";
        qDebug() << "Listening on: " <<  serverAddress().toString() << " ...\r\n";
    }
}

/****************************************************************
*   Purpose:  Checks to see if any connections are pending
*             accepts any connections that are waiting to
*             be connected. Adds thread to queue, and if
*             two players are in a queue, it initializes
*             a match.
*
*     Entry:  NA
*
*      Exit:  Pending connections are accepts, threads are
*             added to queue, and match is initialized if there
*             are two players in queue.
****************************************************************/
void CG_Server::incomingConnection(qintptr socketDescriptor)
{
    // Chess player connected
    qDebug() << socketDescriptor << " Connecting...";

    QTcpSocket * socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);

    addPlayerConnection(socket);
}

void CG_Server::addPlayerToQueue(CG_playerConnection * playerConnection)
{

}

/****************************************************************
*   Purpose:  Adds user to the list of client connections, and
*             prints the number of players online, so tha
*
*     Entry:  A client connection of type QTcpSocket, so that
*             it may be added to the list of client connections.
*
*      Exit:  Adds the player to the list of client connections,
*             and prints the number of players online.
****************************************************************/
void CG_Server::addPlayerConnection( QTcpSocket *chessPlayer)
{

    CG_playerConnection * player = new CG_playerConnection("","",chessPlayer,0,this);
    connect(player, &CG_playerConnection::queueJoinTypeRequest, this, &CG_Server::handleJoinQueue);
    connect(player, &CG_playerConnection::playerDisconnected,this, &CG_Server::clientDisconnected );
    m_connectedPlayers.append(player);
    player->sendRequestPlayerInfo();
    qDebug() << "\nNumber of players online: " << m_connectedPlayers.size();
}

void CG_Server::queueTimerExpired()
{
    if(m_minuteQueue.length() >= 2)
    {
        CG_playerConnection * player1 = m_minuteQueue.takeFirst();
        CG_playerConnection * player2 = m_minuteQueue.takeFirst();
        CG_Match * match = new CG_Match(player1,player2, 1, this);
        m_openMatches.append(match);
    }
    else if(m_fiveMinuteQueue.length() >= 2)
    {
        CG_playerConnection * player1 = m_fiveMinuteQueue.takeFirst();
        CG_playerConnection * player2 = m_fiveMinuteQueue.takeFirst();
        CG_Match * match = new CG_Match(player1,player2,5,this);
        m_openMatches.append(match);
    }
    else if(m_thirtyMinuteQueue.length() >= 2)
    {
        CG_playerConnection * player1 = m_thirtyMinuteQueue.takeFirst();
        CG_playerConnection * player2 = m_thirtyMinuteQueue.takeFirst();
        CG_Match * match = new CG_Match(player1,player2,30,this);
        m_openMatches.append(match);
    }
    else
        m_queueConnectTimer.stop();
}



/****************************************************************
*   Purpose:  Disconnects the client by detecting that a
*             client has disconnected, and removes the client.
*
*     Entry:  Entered whenever a client disconnects from the
*             server.
*
*      Exit:  Disconnects the client.
****************************************************************/
void CG_Server::clientDisconnected()
{
    CG_playerConnection * player = qobject_cast<CG_playerConnection *>(sender());
    m_connectedPlayers.removeOne(player);
    player->deleteLater();
}

/****************************************************************
 *  Purpose:  Removes specified client from the connection's
 *            list, and deletes the client socket.
 *
 *    Entry:  Pointer to a client socket, so that specified
 *            client are removed from the connections list.
 *
 *     Exit:  Removes specified client, and deletes the client
 *            socket.
****************************************************************/
void CG_Server::removeAllClientConnections(QTcpSocket *client)
{
    for(int i = 0; i < m_connectedPlayers.length(); ++i)
    {
        CG_playerConnection * player = m_connectedPlayers.at(i);
        player->getSocket()->close();
        player->deleteLater();
    }

    qDebug() << "It worked!  Client disconnected!";
}

void CG_Server::saveUserInfoToDatabase()
{

}

void CG_Server::loadUserInfoFromDatabase()
{

}

void CG_Server::updateServerInfo()
{

}

void CG_Server::handleJoinQueue(TimeControl time_type)
{
    CG_playerConnection * player = qobject_cast<CG_playerConnection*>(sender());
    switch(time_type)
    {
        case ONE_MINUTE:

            m_minuteQueue.append(player);
            if(m_minuteQueue.length() >= 2)
                m_queueConnectTimer.start();
            break;
        case FIVE_MINUTE:
            m_fiveMinuteQueue.append(player);
            if(m_fiveMinuteQueue.length() >= 2)
                m_queueConnectTimer.start();
            break;
        case THIRTY_MINUTE:
            m_thirtyMinuteQueue.append(player);
            if(m_thirtyMinuteQueue.length() >= 2)
                m_queueConnectTimer.start();
            break;
        default:
            qDebug() << "Error invalid Time Control received.";
            break;
    }
}

void CG_Server::disconnectPlayer(int playerID)
{

}

int CG_Server::getMatchCount()
{
    return m_openMatches.length();
}

int CG_Server::getPlayerCount()
{
    return m_connectedPlayers.length();
}

int CG_Server::getQueueCount()
{
    return (m_minuteQueue.length() + m_fiveMinuteQueue.length() + m_thirtyMinuteQueue.length());
}


void CG_Server::oneMinuteGameRequest(int playerID)
{

}

void CG_Server::fiveMinuteGameRequest(int playerID)
{

}

void CG_Server::thirtyMinuteGameRequest(int playerID)
{

}

void CG_Server::kibitzGameRequest(int playerID, int matchID)
{

}

void CG_Server::connectToOpponent(int playerID, int opponent, int timeControl)
{

}

void CG_Server::sendMove(int playerID, int opponent, int fromFile, int fromRank, int toFile, int toRank)
{

}

void CG_Server::sendResignation(int playerID, int opponent)
{

}

void CG_Server::sendCheckMate(int playerID, int opponent)
{

}

void CG_Server::removeFromQueue(int playerID)
{

}

void CG_Server::checkTimeOut()
{

}

void CG_Server::updateBoard(int playerID, QString updatedboard[8][8])
{

}
