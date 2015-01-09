#include "mythread.h"

MyThread::MyThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    //thread starts here
      qDebug() << socketDescriptor << " Starting thread";
      socket = new QTcpSocket();
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

void MyThread::readyRead()
{
     QByteArray Data = socket->readLine();

     //Only write to socket if user presses enter
     qDebug() << socketDescriptor << " says: " << Data;

     //Only send the message when the user presses enter
     //socket->write(Data);
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}

qintptr MyThread::getSocketDescriptor()
{
    return socketDescriptor;
}
