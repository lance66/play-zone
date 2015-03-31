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
    // User logs onto server, welcome user to server
    qDebug() << "Welcome to the Chessgames Mobile Server!";

    //  Do not take too long to connect or your session will timeout.
    m_queueConnectTimer.setInterval(1000);
    m_queueConnectTimer.stop();

    //  When the timer times out, notify queueTimerExpired()
    connect(&m_queueConnectTimer, &QTimer::timeout, this, &CG_Server::queueTimerExpired);
}

//Document header needed
CG_Server::~CG_Server()
{
    // If server loses connection, echo error
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
    // Possibly use QHostAddress add("192.168.1.100"); in the future

    // Tell server to listen to incoming connections on the following port

    QHostAddress add("192.168.0.118");
    if(!this->listen(QHostAddress(add), 9556))
    {
        // Could not set listener on localhost, so echo could not start server
        qDebug() << "Could not start server";
    }
    else
    {
        // Listener has been set on localhost, which means the server started
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
    // Chess player connected, echo player's unique identifier (i.e. socket descriptor)
    qDebug() << socketDescriptor << " Connecting...";

    //Create socket
    QTcpSocket * socket = new QTcpSocket();

    //Bind socket descriptor to socket
    socket->setSocketDescriptor(socketDescriptor);

    //Add player to list of connected players
    addPlayerConnection(socket);
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
    // Create new player connection
    CG_playerConnection * player = new CG_playerConnection("", "", chessPlayer, 0, this);

    // When a players joins a queue, call handle join queue to place him in the right queue
    connect(player, &CG_playerConnection::queueJoinTypeRequest, this, &CG_Server::handleJoinQueue);

    // When a player disconnects, call clientDisconnected()
    connect(player, &CG_playerConnection::playerDisconnected, this, &CG_Server::clientDisconnected );

    //Append player connection to list of connected players
    m_connectedPlayers.append(player);

    //  Tell the server your player information (i.e. username, ELO and country flag)
    player->sendRequestPlayerInfo();

    //  TODO -- Display number of players online in lobby, not just echo to console
    qDebug() << "\nNumber of players online: " << m_connectedPlayers.size();
}
void CG_Server::queueTimerExpired()
{
    if(m_minuteQueue.length() >= 2)
    {
        //First player off queue = white pieces
        CG_playerConnection * player1 = m_minuteQueue.takeFirst();

        //Second player off queue = black pieces
        CG_playerConnection * player2 = m_minuteQueue.takeFirst();

        //Create new one minute match and match the two players above
        CG_Match * match = new CG_Match(player1,player2, 1, this);

        //Append to list of matches
        m_openMatches.append(match);
    }
    else if(m_fiveMinuteQueue.length() >= 2)
    {
        //First player off queue = white pieces
        CG_playerConnection * player1 = m_fiveMinuteQueue.takeFirst();

        //Second player off queue = black pieces
        CG_playerConnection * player2 = m_fiveMinuteQueue.takeFirst();

        //Create new five minute match and match the two players above
        CG_Match * match = new CG_Match(player1,player2,5,this);

        //Append to list of matches
        m_openMatches.append(match);
    }
    else if(m_thirtyMinuteQueue.length() >= 2)
    {
        //First player off queue = white pieces
        CG_playerConnection * player1 = m_thirtyMinuteQueue.takeFirst();

        //Second player off queue = black pieces
        CG_playerConnection * player2 = m_thirtyMinuteQueue.takeFirst();

        //Create new thirty minute match and match the two players above
        CG_Match * match = new CG_Match(player1,player2,30,this);

        //Append to list of matches
        m_openMatches.append(match);
    }
    else
        //Stop timer
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
    //Detect who disconnected
    CG_playerConnection * player = qobject_cast<CG_playerConnection *>(sender());

    //Remove said player
    m_connectedPlayers.removeOne(player);

    //Let garbage collector delete player connection at its convenience
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
    // Loop through all connected players
    for(int i = 0; i < m_connectedPlayers.length(); ++i)
    {
        // Get rid of them all
        CG_playerConnection * player = m_connectedPlayers.at(i);
        player->getSocket()->close();
        player->deleteLater();
    }

    qDebug() << "It worked!  Client disconnected!";
}

// TODO -- Change time_type to timeControl
// TODO -- Change m_minuteQueue to m_oneMinuteQueue
void CG_Server::handleJoinQueue(TimeControl time_type)
{
    //Create temporary player connection to whoever wanted to join the queue
    CG_playerConnection * player = qobject_cast<CG_playerConnection*>(sender());

    //See what time control the player wanted
    switch(time_type)
    {
        case ONE_MINUTE:

            // Append player to oneMinuteQueue
            m_minuteQueue.append(player);

            // If queue has two people in it, call timer.
            // After time times out, players will be matched up.
            if(m_minuteQueue.length() >= 2)
                m_queueConnectTimer.start();

            break;

        case FIVE_MINUTE:

            // Append player to oneMinuteQueue
            m_fiveMinuteQueue.append(player);

            // If queue has two people in it, call timer.
            // After time times out, players will be matched up.
            if(m_fiveMinuteQueue.length() >= 2)
                m_queueConnectTimer.start();

            break;

        case THIRTY_MINUTE:

            // Append player to oneMinuteQueue
            m_thirtyMinuteQueue.append(player);

            // If queue has two people in it, call timer.
            // After time times out, players will be matched up.
            if(m_thirtyMinuteQueue.length() >= 2)
                m_queueConnectTimer.start();

            break;

        default:
            qDebug() << "Error invalid Time Control received.";
            break;
    }
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
    //Add up everyone in the queue and return the result
    return (m_minuteQueue.length() + m_fiveMinuteQueue.length() + m_thirtyMinuteQueue.length());
}
