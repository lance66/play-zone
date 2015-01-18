#include "mythread.h"

/****************************************************************
*   Purpose:  Constructor. Initializes data members.
*
*     Entry:  NA
*
*      Exit:  Data members are initialized.
****************************************************************/
MyThread::MyThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

/****************************************************************
 *  Purpose:  Destructor
 *    Entry:
 *     Exit:
****************************************************************/
MyThread::~MyThread()
{
}

/****************************************************************
*   Purpose:  Starts thread, and notifies client that they
*             are connected.
*
*     Entry:  NA
*
*      Exit:  Thread is started, and client is notified.
****************************************************************/
void MyThread::run()
{

    qDebug() << socketDescriptor << " Starting thread";
    socket = new QTcpSocket;

    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << socketDescriptor << " Client Connected";

    exec();
}

/****************************************************************
*   Purpose:  Sends user's message, and writes message to
*             the socket.
*
*     Entry:  NA
*
*      Exit:  Sends users message, and writes it to the socket.
****************************************************************/
void MyThread::readyRead()
{
     QByteArray Data = socket->readLine();

     //Only send the message when the user presses enter
     qDebug() << socketDescriptor << " says: " << Data;
}

/****************************************************************
*   Purpose: Notifies the users that the server is
*            disconnected and closes the socket, when server
*            disconnects.
*
*    Entry:  NA
*
*     Exit:  Closes socket, and notifies user of disconnection.
****************************************************************/
void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}

QTcpSocket *MyThread::getSocket()
{
    return socket;
}

/****************************************************************
*   Purpose:  Retrives socket descriptor.
*
*     Entry:  NA
*
*      Exit:  Socket descriptor is returned.
****************************************************************/
qintptr MyThread::getSocketDescriptor()
{
    return socketDescriptor;
}
