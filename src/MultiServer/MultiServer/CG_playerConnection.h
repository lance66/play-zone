#ifndef CG_playerConnection_H
#define CG_playerConnection_H

#include <QThread>
#include <QString>
#include <QTcpSocket>
#include <QDebug>
#include <QEvent>

/************************************************************************
* Class: CG_playerConnection
*
* Constructors:
*   explicit CG_playerConnection(qintptr ID, QObject *parent = 0)
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
class CG_playerConnection : public QThread
{
    Q_OBJECT
public:
    explicit CG_playerConnection(qintptr ID, QObject *parent = 0);
    ~CG_playerConnection();


    //Setters
    void setUsername(QString username);
    void setELO(int ELO);

    //Getters
    qintptr getSocketDescriptor() const;
    QString getUsername() const;
    int getELO() const;
    QTcpSocket *getSocket();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void run();
    void readyRead();
    void disconnected();

public slots:

private:
    QTcpSocket *socket;
    QString m_username;
    int m_ELO;
    QString m_countryFlag;

};

#endif // CG_playerConnection_H
