#include "myserver.h"
#include <iostream>

/**************************************************************
*   Purpose:  Constructor.  Initializes QTcpServer
*
*     Entry:  NA
*
*      Exit:  Data members are initialized.
****************************************************************/
MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{

}

/**************************************************************
*   Purpose:  Starts the server, and notifies user that it is
*               listening for connections.
*
*     Entry:  Called after an instances of a MyServer object is
*             created.
*
*      Exit:  Starts the server.
****************************************************************/
void MyServer::StartServer()
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

/**************************************************************
*   Purpose:  Checks to see if any connections are pending
*             accepts any connections that are waiting to
*             be connected. Adds thread to queue, and if
*             two players are in a queue, it initializes
*             a match.
*
*    Entry:  NA
*
*     Exit:  Pending connections are accepts, threads are
*            added to queue, and match is initialized if there
*            are two players in queue.
****************************************************************/
void MyServer::incomingConnection(qintptr socketDescriptor)
{
    //Create new socket
    QTcpSocket *chessPlayer = new QTcpSocket;

    //Set socket descriptor to socket descriptor it was assigned
    chessPlayer->setSocketDescriptor(socketDescriptor);

    //When player disconnects, call client disconnected
    connect(chessPlayer, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    //Add user to list of client connections
    clientConnections.append(chessPlayer);

    //Print number of players online
    qDebug() << "\nNumber of players online: " << clientConnections.size();

    //Sample function that sends move from server to player
    sendMove(chessPlayer, chessPlayer->socketDescriptor());

    qDebug() << socketDescriptor << " Connecting...";
    MyThread *thread = new MyThread(socketDescriptor,this);

    int ID = static_cast<int>(thread->getSocketDescriptor());

    //Add thread to queue
    oneMinuteQueue.enqueue(ID);

    connect(thread, SIGNAL(finished()),this, SLOT(clientDisconnected()));
    connect(thread, SIGNAL(finished()),thread, SLOT(deleteLater()));
    thread->start();

    //If two players in queue, initiate match
    if(oneMinuteQueue.length() >= 2)
    {
        int firstID = oneMinuteQueue.first();
        oneMinuteQueue.dequeue();

        int secondID = oneMinuteQueue.first();
        oneMinuteQueue.dequeue();

        CG_Match match(firstID, secondID, clientConnections.front(), clientConnections.back());
        matches.append(match);
    }
}

/**************************************************************
*   Purpose:  Disconnects the client by detecting that a
*             client has disconnected, and removes the client.
*
*     Entry:  Entered whenever a client disconnects from the
*             server.
*
*      Exit:  Disconnects the client.
****************************************************************/
void MyServer::clientDisconnected()
{
    //Detect client that disconnected
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    //If client is not null remove client
    if (client != nullptr)
    {
        //Remove from list of connections
        clientConnections.removeAll(client);

        //Delete client
        client->deleteLater();
        qDebug() << "It worked!  Client disconnected!";
    }

    else
        clientConnections.removeAll(client);
}

/**************************************************************
*   Purpose:  Sends the move to the client.
*
*     Entry:  Called whenever a client moves.
*
*      Exit:  Notifies client of move.
****************************************************************/
void MyServer::sendMove(QTcpSocket *client, qintptr socketDescriptor)
{
    //If client is null, get out of here
    if(!client)
    {
        return;
    }

    //Below is a series of conversions in order to write the
    //socket descriptor to the socket

    //Convert qintptr to int
    int temp = static_cast<int>(socketDescriptor);

    //Convert int to string
    std::string s = std::to_string(temp);

    //Convert string to const char *
    char const *pchar = s.c_str();

    //Write to client
    client->write("Hello, ");
    client->write(pchar);
    client->write("! ");
    client->flush();

    //In case of lag, wait for bytes to write to client
    client->waitForBytesWritten(3000);
}
