#ifndef CG_SERVERCONNECTION_H
#define CG_SERVERCONNECTION_H

#include <QObject>
#include <QHostInfo>
#include <QTcpSocket>
#include <QDebug>

enum ConnectionState
{
    IDLE,
    CONNECTED,
    DISCONNECTED,
    LOBBY,
    WAITING_FOR_OPPONENT,
    SENDING_PLAYER_INFO,
    SENDING_MOVE,
    GAME_IN_PROGRESS
};

enum PacketHeader
{
    PLAYER_INFO = 0,
    LOBBY_CONNECTED,
    CONNECTING_TO_GAME,
    GAME_READY,
    OPPONENT_MOVE
};

class CG_serverConnection : public QObject
{
    Q_OBJECT
public:
    explicit CG_serverConnection(QObject *parent = 0);
    ~CG_serverConnection();

    void handleConnections();

    void sendPlayerInfo(QString username, int ELO, QString countryFlag);
    void sendLoginInformation(QString username, QString password);

    //State tracking code
    void onRequestedInformationAboutClient();
    void onConnectedToLobby(QJsonObject &data);
    void onPairedWithPlayer(QJsonObject &data);
    void onOpponentMoved(QJsonObject &data);
    void onGameReady();

    void handleRequest(PacketHeader requestID, QJsonObject &data);

signals:
    void matchConnected();
    void networkPlayerMoved(int fromFile,int fromRank,int toFile,int toRank);

public slots:
    void onConnect();
    void onDisconnect();
    void onDataReady();
    void setPlayerInfo(QString username, int ELO, QString countryFlag);
    void connectToServer(QString address, int port);
    void sendMove(int fromFile, int fromRank, int toFile, int toRank);

private:
    QHostInfo m_hostInfo;
    int m_hostPort;
    QTcpSocket * m_socket;
    ConnectionState m_connectionState;
    QByteArray m_messageBuffer;

    QString m_username;
    int m_ELO;
    QString m_countryFlag;
};

#endif // CG_SERVERCONNECTION_H
