#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{

}


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

void MyServer::sendMove(QTcpSocket *client)
{
    if(!client)
        return;

    client->write("Hello!\n\n\n\n");
}
