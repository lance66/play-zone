#include "cg_playerThread.h"

/****************************************************************
*   Purpose:  Constructor. Initializes data members.
*
*     Entry:  NA
*
*      Exit:  Data members are initialized.
****************************************************************/
CG_PlayerThread::CG_PlayerThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
    Data_Ary = new char[10];
    strcpy(Data_Ary, "");
}

/****************************************************************
 *  Purpose:  Destructor
 *    Entry:
 *     Exit:
****************************************************************/
CG_PlayerThread::~CG_PlayerThread()
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
void CG_PlayerThread::run()
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
void CG_PlayerThread::readyRead()
{
     QByteArray Data = socket->readLine();

     if(Data.at(0) == ':')
     {
         qDebug() << socketDescriptor << " says: " << Data_Ary;
         strcpy(Data_Ary, "");
     }
     else if(Data.at(0) == 0x0d)
     {
         qDebug() << socketDescriptor << " says: " << Data_Ary;
         strcpy(Data_Ary, "");
     }
     else if(strlen(Data_Ary) < 9)
     {
         strcat(Data_Ary, Data);
     }

     //Only send the message when the user presses enter
     //qDebug() << socketDescriptor << " says: " << Data_Ary;
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
void CG_PlayerThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}

QTcpSocket *CG_PlayerThread::getSocket()
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
qintptr CG_PlayerThread::getSocketDescriptor()
{
    return socketDescriptor;
}
