#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
//#include <QDebug>
#include <QVector>
#include <QQueue>
#include <QList>
#include "CG_match.h"
#include "mythread.h"

/************************************************************************
* Class: CG_Server
*
* Constructors:
*   explicit MyServer(QObject *parent = 0);
*
* Slots:
*   void clientDisconnected()
*       Detects that a client disconnected from the server
*       and removes the client.
*
* Methods:
*   void StartServer()
*       Starts the server.
*   void incomingConnection(qintptr socketDescriptor)
*       Accepts any pending connections.
*   void sendMove(QTcpSocket *client)
*       Sends the move to the client
*************************************************************************/
class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void StartServer();


signals:

public slots:
protected slots:
    void clientDisconnected();

protected:
    void incomingConnection(qintptr socketDescriptor);
    void sendMove(QTcpSocket *client, qintptr socketDescriptor);

    QList<QTcpSocket *> clientConnections;
    QVector<CG_Match> matches;
    QQueue<int> oneMinuteQueue;
};

#endif // MYSERVER_H
