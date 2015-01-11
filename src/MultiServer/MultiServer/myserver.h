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
    QVector<CG_Match> matches;
    QList<QTcpSocket *> clientConnections;
    QQueue<int> oneMinuteQueue;
    void sendMove(QTcpSocket *client);


};

#endif // MYSERVER_H
