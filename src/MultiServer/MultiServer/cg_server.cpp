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
    connect(this, SIGNAL(playersReadyToBeMatched()), this, SLOT(startOneMinuteMatch()));
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
    if(!this->listen(QHostAddress::Any,1234))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Chessgames server started!";
        qDebug() << "Listening...\r\n";
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

    // Every new connection will run in a newly created thread
    CG_playerConnection * playerConnection = new CG_playerConnection(socketDescriptor, this);

    // Once thread is not needed, thread is deleted
    connect(playerConnection, SIGNAL(finished()), playerConnection, SLOT(deleteLater()));

    // Start thread
    playerConnection->start();

    //Add player to queue
    this->addPlayerToQueue(playerConnection);

    // Call this member from reimplemented incomingConnection()
    // because we do not want to break the Pending Connections mechanism.
    this->addPendingConnection(playerConnection->getSocket());

//    //Create new socket
//    QTcpSocket *chessPlayer = new QTcpSocket;

//    //Set socket descriptor to socket descriptor it was assigned
//    chessPlayer->setSocketDescriptor(socketDescriptor);

//    //Add user to list of client connections
//    addPlayerConnection(socketDescriptor, chessPlayer);

//    //Print which socket descriptor is connecting
//    qDebug() << socketDescriptor << " Connecting...";

//    //Create thread for player logging on
//    CG_playerConnection *thread = new CG_playerConnection(socketDescriptor,this);

//    //Socket descriptors are int pointers...so they need to be converted to an int
//    int ID = static_cast<int>(thread->getSocketDescriptor());

//    //When player disconnects, call client disconnected
//    connect(chessPlayer, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
//    connect(chessPlayer, SIGNAL(disconnected()), this, SLOT(deleteLater()));
//    connect(thread, SIGNAL(finished()),this, SLOT(clientDisconnected()));
//    connect(thread, SIGNAL(finished()),thread, SLOT(deleteLater()));

//    //Start thread
//    thread->start();

//    //Add thread to queue
//    oneMinuteQueue.enqueue(ID);

//    //If two players in queue, pair them and initiate match
//    if(oneMinuteQueue.length() >= 2)
//    {
//        startOneMinuteMatch();
//    }
}

void CG_Server::addPlayerToQueue(CG_playerConnection * playerConnection)
{
    //Add player to queue
    this->oneMinuteQueue.enqueue(playerConnection);

    //Number of players in queue
    qDebug() << "Number of players in queue: " << oneMinuteQueue.count();

    //If two players in queue, pair them and initiate match
    if(oneMinuteQueue.count() >= 2)
    {
        emit playersReadyToBeMatched();
    }
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
void CG_Server::addPlayerConnection(int socketDescriptor, QTcpSocket *chessPlayer)
{
    //Add user to dictionary of client connections
    clientConnections.insert(socketDescriptor, chessPlayer);

    //Print number of players online
    qDebug() << "\nNumber of players online: " << clientConnections.size();
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
void CG_Server::startOneMinuteMatch()
{
    qDebug() << "Match started!";

    //Create match
    CG_Match * temp = new CG_Match(oneMinuteQueue);

    //Add match to vector of matches
    matches.append(temp);

    //Start match
    temp->startMatch();

//    int firstID = oneMinuteQueue.first();
//    oneMinuteQueue.dequeue();

//    int secondID = oneMinuteQueue.first();
//    oneMinuteQueue.dequeue();

//    match.setWhiteID(firstID);
//    match.setBlackID(secondID);
//    match.setWhiteSocket(clientConnections, firstID);
//    match.setBlackSocket(clientConnections, secondID);
//    matches.append(match);
//    match.startMatch(firstID, secondID, clientConnections[firstID], clientConnections[secondID]);
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
void CG_Server::clientDisconnected(CG_playerConnection * playerConnection)
{
    //Remove thread from queue
    oneMinuteQueue.removeAll(playerConnection);

/*    //Detect client that disconnected
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    //If client is not null remove client
    if (client != nullptr)
    {
        removeAllClientConnections(client);
        //remove from queue
        //if in match, destroy match
    }
    else
        clientConnections.remove(static_cast<int>(client->socketDescriptor())*/
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
    //Remove from list of connections
    clientConnections.remove(static_cast<int>(client->socketDescriptor()));

    //Delete client
    client->deleteLater();
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

void CG_Server::disconnectPlayer(int playerID)
{

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
