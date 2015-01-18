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
*   void addPlayerConnection(QTcpSocket *chessPlayer)
*       Adds a player connection to the list of connections.
*   void startOneMinuteMatch()
*       Starts a one minute match, when there are two or more players
*   void removeAllClientConnections(QTcpSocket *client)
*       Removes all clients from the connection's list.
*   void configureThreadSignalsAndSlots(MyThread * thread)
*       Configures the signals and slots for a thread.
*   void writeSocketDescriptorToSocket(QTcpSocket *client, qintptr socketDescriptor)
*       Follows a series of conversions to write socketDescriptor
*       to the socket.
*   void delaySocket(QTcpSocket * socket, int timeToDelay)
*       Waits for bytes to write to client.
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
        CG_Match match;
        QQueue<int> oneMinuteQueue;

    private:
        void addPlayerConnection(QTcpSocket *chessPlayer);
        void startOneMinuteMatch();
        void removeAllClientConnections(QTcpSocket *client);
        void configureThreadSignalsAndSlots(MyThread * thread);
        void writeSocketDescriptorToSocket(QTcpSocket *client, qintptr socketDescriptor);
        void delaySocket(QTcpSocket * socket, int timeToDelay);
};

#endif // MYSERVER_H
