#include "myserver.h"
#include <iostream>

/****************************************************************
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

/****************************************************************
*   Purpose:  Starts the server, and notifies user that it is
*             listening for connections.
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
void MyServer::incomingConnection(qintptr socketDescriptor)
{
    //Create new socket
    QTcpSocket *chessPlayer = new QTcpSocket;

    //Set socket descriptor to socket descriptor it was assigned
    chessPlayer->setSocketDescriptor(socketDescriptor);

    //When player disconnects, call client disconnected
    connect(chessPlayer, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    //Add user to list of client connections
    addPlayerConnection(chessPlayer);

    //Sample function that sends move from server to player
    sendMove(chessPlayer, chessPlayer->socketDescriptor());

    qDebug() << socketDescriptor << " Connecting...";
    MyThread *thread = new MyThread(socketDescriptor,this);

    int ID = static_cast<int>(thread->getSocketDescriptor());

    //Add thread to queue
    oneMinuteQueue.enqueue(ID);

    configureThreadSignalsAndSlots(thread);

    //If two players in queue, initiate match
    if(oneMinuteQueue.length() >= 2)
        startOneMinuteMatch();
}

/****************************************************************
 *  Purpose:  Configures the signals and slots for threads of
 *            type MyThread, so that when the thread finishes
 *            we may disconnect from the client, and delete the
 *            thread. After Signals and slots are set up, the
 *            thread is started.
 *
 *    Entry:  A thread of type MyThread, so that the threads,
 *            signals and slots can be configured, and started.
 *
 *     Exot:  Configures the signals to their designated slots,
 *            and thread is started.
****************************************************************/
void MyServer::configureThreadSignalsAndSlots(MyThread * thread)
{
    // Associating finsihed signal with the clientDisconnected slot.
    connect(thread, SIGNAL(finished()),this, SLOT(clientDisconnected()));

    // Associating finished signal with deleteLater() slot.
    connect(thread, SIGNAL(finished()),thread, SLOT(deleteLater()));

    thread->start();
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
void MyServer::addPlayerConnection(QTcpSocket *chessPlayer)
{
    //Add user to list of client connections
    clientConnections.append(chessPlayer);

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
void MyServer::startOneMinuteMatch()
{
    int firstID = oneMinuteQueue.first();
    oneMinuteQueue.dequeue();

    int secondID = oneMinuteQueue.first();
    oneMinuteQueue.dequeue();

    CG_Match match(firstID, secondID, clientConnections.front(), clientConnections.back());
    matches.append(match);
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
void MyServer::clientDisconnected()
{
    //Detect client that disconnected
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    //If client is not null remove client
    if (client != nullptr)
    {
        removeAllClientConnections(client);
    }
    else
        clientConnections.removeAll(client);
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
void MyServer::removeAllClientConnections(QTcpSocket *client)
{
    //Remove from list of connections
    clientConnections.removeAll(client);

    //Delete client
    client->deleteLater();
    qDebug() << "It worked!  Client disconnected!";
}

/****************************************************************
*   Purpose:  Sends the move to the client by writing the socket
*             descriptor to the socket.
*
*     Entry:  Called whenever a client moves.
*
*      Exit:  Notifies client of move by writing it to the client
*             socket.
****************************************************************/
void MyServer::sendMove(QTcpSocket *client, qintptr socketDescriptor)
{
    //If client is null, get out of here
    if(!client)
    {
        return;
    }

    writeSocketDescriptorToSocket(client, socketDescriptor);
}

/****************************************************************
 *  Purpose:  Writes the socket descriptor to the socket, by
 *            going through a series of conversions in order to
 *            write to the socket.
 *
 *    Entry:  QTcpSocket pointer that will be written to, after
 *            all conversions take place. and a qintptr that will
 *            that contains the descriptor that will be sent to
 *            the client.
 *
 *     Exit:  Socket descriptor will have gone through a series
 *            of conversions to write to the client socket.
****************************************************************/
void MyServer::writeSocketDescriptorToSocket(QTcpSocket *client, qintptr socketDescriptor)
{
    //Convert qintptr to int
    int temp = static_cast<int>(socketDescriptor);

    //Convert int to string
    std::string s = std::to_string(temp);

    //Convert string to char const *
    char const *pchar = s.c_str();

    //Write to client
    client->write("Hello, ");
    client->write(pchar);
    client->write("! ");
    client->flush();

    delaySocket(client, 3000);
}

/****************************************************************
 *  Purpose:  Delays the socket, in case of lag.
 *
 *    Entry:  Socket that will be delayed, and the time to delay
 *            the socket, measured in milliseconds.
 *
 *     Exit:  Delays the socket by the specified time.
****************************************************************/
void MyServer::delaySocket(QTcpSocket *socket, int timeToDelay)
{
    //In case of lag, wait for bytes to write to client
    socket->waitForBytesWritten(timeToDelay);
}
