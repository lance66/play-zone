#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
//#include <QDebug>
#include <QVector>
#include <QQueue>
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

protected:
    void incomingConnection(qintptr socketDescriptor);
    QVector<CG_Match> matches;
    QQueue<int> oneMinuteQueue;

};

#endif // MYSERVER_H
