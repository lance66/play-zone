#ifndef CG_SERVERCONNECTION_H
#define CG_SERVERCONNECTION_H

#include <QObject>
#include <QHostInfo>
#include <QTcpSocket>
#include <QDebug>
#include "CG_piece.h"

enum ConnectionState
{
    IDLE,
    CONNECTED,
    DISCONNECTED,
    QUEUE,
    WAITING_FOR_OPPONENT,
    SENDING_PLAYER_INFO,
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
    void opponentReceived();
    void matchConnected();
    void networkPlayerMoved(int fromFile,int fromRank,int toFile,int toRank);

public slots:
    QString getOpponent();
    int getOpponentELO();
    bool getColor();

    void onConnect();
    void onDisconnect();
    void onDataReady();
    void setPlayerInfo(QString username, int ELO, QString countryFlag);
    void connectToServer(QString address, int port);
    void sendMove(int fromFile, int fromRank, int toFile, int toRank);
    void sendReady();
    void sendQueueType(int timeControl);


private:
    QHostInfo m_hostInfo;
    int m_hostPort;
    QTcpSocket * m_socket;
    ConnectionState m_connectionState;
    QByteArray m_messageBuffer;

    QString m_username;
    int m_ELO;
    QString m_countryFlag;

    QString m_opponent;
    int m_opponentELO;
    bool m_isWhite;
};

#endif // CG_SERVERCONNECTION_H
