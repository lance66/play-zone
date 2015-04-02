#ifndef CG_playerConnection_H
#define CG_playerConnection_H

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

enum GameState
{
    IDLE,
    CONNECTED,
    DISCONNECTED,
    QUEUE,
    WAITING_FOR_OPPONENT,
    WAITING_PLAYER_INFO,
    SENDING_MOVE,
    GAME_IN_PROGRESS
};

enum PacketHeader
{
    PLAYER_INFO = 0,
    QUEUE_REQUEST,
    QUEUE_CONNECTED,
    PLAYER_READY,
    CONNECTING_TO_GAME,
    GAME_READY,
    OPPONENT_MOVE
};

enum TimeControl
{
    ONE_MINUTE = 1,
    FIVE_MINUTE = 5,
    THIRTY_MINUTE = 30
};

enum PlayerColor
{
    WHITE,
    BLACK
};


class CG_playerConnection : public QObject
{
    Q_OBJECT
public:

    explicit CG_playerConnection(QString username, int countryname, QTcpSocket * socket, int elo_rating,  QObject *parent);
    ~CG_playerConnection();

    // Send Methods (Package outgoing messages)
    void sendRequestPlayerInfo();
    void sendConnectedToQueue();
    void sendConnectingToGame(QString players_name, int elo, int countryFlag, bool color);
    void sendMatchConnected();
    void beginConnectingToPlayer(CG_playerConnection * player, bool color);
    void forwardOpponentMove(int startRank, int startFile, int endRank, int endFile);

    // Receive methods (Parse incomming messages)
    void parseQueueJoinRequest(QJsonObject & data);
    void parsePlayerInfo(QJsonObject & data);
    void parsePlayerMove(QJsonObject & data);
    void parseReady(QJsonObject & data);
    void handleRequest(PacketHeader requestID, QJsonObject &data);

    void setUsername(QString username);
    void setELO(int ELO);
    void setCountryFlag(int countryFlag);
    void connections();

    QString getUsername() const;
    int getELO() const;
    int getCountryFlag() const;
    QTcpSocket *getSocket();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void playerMadeMove(int startRank, int startFile,int endRank, int endFile);
    void queueJoinTypeRequest(TimeControl time_type);
    void playerReady();
    void playerDisconnected();

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket * m_socket;
    QString      m_username;
    int          m_countryname;
    int          m_ELO;
    GameState    m_currentstate;
    QByteArray   m_messagebuffer;
};


#endif // CG_playerConnection_H
