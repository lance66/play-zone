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
