#include "myserver.h"

/**************************************************************
*	  Purpose:  Constructor.  Initializes QTcpServer
*
*     Entry:  NA
*
*     Exit:  Data members are initialized.
****************************************************************/
MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{

}

/**************************************************************
*	  Purpose:  Starts the server, and notifies user that it is
*               listening for connections.
*
*     Entry:  Called after an instances of a MyServer object is
*             created.
*
*     Exit:  Starts the server.
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
*	  Purpose:  Checks to see if any connections are pending
*               accepts any connections that are waiting to
*               be connected. Adds thread to queue, and if
*               two players are in a queue, it initializes
*               a match.
*
*     Entry:  NA
*
*     Exit: Pending connections are accepts, threads are
*           added to queue, and match is initialized if there
*           are two players in queue.
****************************************************************/
void MyServer::incomingConnection(qintptr socketDescriptor)
{
    while (hasPendingConnections())
    {
        QTcpSocket *chessPlayer = nextPendingConnection();
        connect(chessPlayer, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

        //Add user to list of client connections
        clientConnections.append(chessPlayer);
    }

    qDebug() << socketDescriptor << " Connecting...";
    MyThread *thread = new MyThread(socketDescriptor,this);

    int ID = static_cast<int>(thread->getSocketDescriptor());

    //Add thread to queue
    oneMinuteQueue.enqueue(ID);

    //If two players in queue, initiate match
    if(oneMinuteQueue.length() >= 2)
    {
        int firstID = oneMinuteQueue.first();
        oneMinuteQueue.dequeue();

        int secondID = oneMinuteQueue.first();
        oneMinuteQueue.dequeue();

        CG_Match firstMatch(firstID, secondID);

        matches.append(firstMatch);
    }

    connect(thread, SIGNAL(finished()),thread, SLOT(deleteLater()));
    thread->start();
}

/**************************************************************
*	  Purpose:  Disconnects the client by detecting that a
*               client has disconnected, and removes the client.
*
*     Entry:  Entered whenever a client disconnects from the
*             server.
*
*     Exit:  Disconnects the client.
****************************************************************/
void MyServer::clientDisconnected()
{
    //Detect client that disconnected
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    //If client is not null remove client
    if (client != nullptr)
    {
        clientConnections.removeAll(client);
        client->deleteLater();
    }
}

/**************************************************************
*	  Purpose:  Sends the move to the client.
*
*     Entry:  Called whenever a client moves.
*
*     Exit:  Notifies client of move.
****************************************************************/
void MyServer::sendMove(QTcpSocket *client)
{
    if(!client)
        return;

    client->write("Hello!\n\n\n\n");
}
