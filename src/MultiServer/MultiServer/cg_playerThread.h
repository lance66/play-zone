#ifndef CG_PlayerThread_H
#define CG_PlayerThread_H

#include <QThread>
#include <QString>
#include <QTcpSocket>
#include <QDebug>
#include <QEvent>

/************************************************************************
* Class: CG_PlayerThread
*
* Constructors:
*   explicit CG_PlayerThread(qintptr ID, QObject *parent = 0)
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
class CG_PlayerThread : public QThread
{
    Q_OBJECT
public:
    explicit CG_PlayerThread(qintptr ID, QObject *parent = 0);
    ~CG_PlayerThread();

    void run();
    qintptr getSocketDescriptor();
    QTcpSocket *getSocket();
    char * Data_Ary;

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

public slots:

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QString username;
    int ID;
    int ELO;
    int opponent;
    int matchID;

    //ChessClock time;
};

#endif // CG_PlayerThread_H
