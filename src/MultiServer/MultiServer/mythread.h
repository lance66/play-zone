#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

/************************************************************************
* Class: MyThread
*
* Constructors:
*   explicit MyThread(qintptr ID, QObject *parent = 0)
*
* Signals:
*   void error(QTcpSocket::SocketError socketerror)
*       No implementation, yet
*
* Slots:
*    void readyRead()
*       Sends message and writes to socket.
*    void disconnected()
*       Closes the socket
*
* Methods:
*   void run()
*       Starts thread
*   qintptr getSocketDescriptor()
*       Returns socket descriptor
*************************************************************************/
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID, QObject *parent = 0);
    ~MyThread();
    void run();
    qintptr getSocketDescriptor();
    QTcpSocket *getSocket();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

public slots:

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // MYTHREAD_H
