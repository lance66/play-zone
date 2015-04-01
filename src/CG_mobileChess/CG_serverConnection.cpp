#include "CG_serverConnection.h"
#include "CG_pawn.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

CG_serverConnection::CG_serverConnection(QObject *parent) : QObject(parent)
{

}

CG_serverConnection::~CG_serverConnection()
{

}

void CG_serverConnection::handleConnections()
{
    connect(m_socket, &QTcpSocket::readyRead, this, &CG_serverConnection::onDataReady);
    connect(m_socket, &QTcpSocket::disconnected, this, &CG_serverConnection::onDisconnect);

    //If you are the black pieces, change the pawn to go in opposite direction
//    connect(this, &CG_serverConnection::iAmBlack, &CG_pawn, &CG_pawn::ToggleDirection);
    //QObject::connect(this, &CG_serverConnection::iAmBlack, &CG_pawn, &CG_pawn::ToggleDirection);
}

void CG_serverConnection::sendPlayerInfo(QString username, int ELO, QString countryFlag)
{
    //Create local JSON object
    QJsonObject userInfo;

    //Create object
    userInfo["PacketHeader"] = PLAYER_INFO;
    userInfo["Username"] = username;
    userInfo["ELO"] = ELO;
    userInfo["CountryFlag"] = countryFlag;

    //Create JSON document
    QJsonDocument doc;
    doc.setObject(userInfo);

    //Debug
    qDebug() << doc.toJson();

    //Send over socket
    m_socket->write(doc.toBinaryData());
}

void CG_serverConnection::setPlayerInfo(QString username, int ELO, QString countryFlag)
{
    m_username = username;
    m_ELO = ELO;
    m_countryFlag = countryFlag;
}

void CG_serverConnection::onConnectedToLobby(QJsonObject &data)
{
    m_connectionState = QUEUE;

    int playerCount = data["PlayerCount"].toInt();
    int matchCount = data["MatchCount"].toInt();
    int queueCount = data["QueueCount"].toInt();

    qDebug() << playerCount;
    qDebug() << matchCount;
    qDebug() << queueCount;
}

void CG_serverConnection::onPairedWithPlayer(QJsonObject &data)
{
    m_connectionState = WAITING_FOR_OPPONENT;

    QString opponent = data["Opponent"].toString();
    int ELO = data["ELO"].toInt();
    bool IsWhite = data["IsWhite"].toBool();

    qDebug() << opponent;
    qDebug() << ELO;
    qDebug() << IsWhite;

    m_opponent = opponent;
    m_opponentELO = ELO;

    // TODO -- Change name to isOpponentWhite
    m_isWhite = IsWhite;

    //Emit opponent received
    emit opponentReceived();

    //Emit signal that player is black because opponent is white
    if(m_isWhite == true)
    {
        emit iAmBlack();
    }

    sendReady();
}

void CG_serverConnection::onGameReady()
{
    m_connectionState = GAME_IN_PROGRESS;

    emit matchConnected();
}

void CG_serverConnection::onConnect()
{

}

void CG_serverConnection::onDisconnect()
{
    qDebug() << m_username << " has disconnected.";
}

void CG_serverConnection::onDataReady()
{
    m_messageBuffer.append(m_socket->readAll());
    if(m_socket->bytesAvailable() == 0)
    {
        QJsonDocument message_received = QJsonDocument::fromBinaryData(m_messageBuffer);
        QJsonObject data;
        data = message_received.object();

        PacketHeader header = (PacketHeader) data["PacketHeader"].toInt();
        qDebug() << header;
        this->handleRequest(header, data);

        //Clear buffer
        m_messageBuffer.clear();
    }

    else
        this->onDataReady();

}

void CG_serverConnection::handleRequest(PacketHeader requestID, QJsonObject &data)
{
    switch(requestID)
    {
    case PLAYER_INFO:
        this->sendPlayerInfo(m_username, m_ELO, m_countryFlag);
        break;
    case QUEUE_CONNECTED:
        this->onConnectedToLobby(data);
        break;
    case CONNECTING_TO_GAME:
        this->onPairedWithPlayer(data);
        break;
    case GAME_READY:
        this->onGameReady();
        break;
    case OPPONENT_MOVE:
        this->onOpponentMoved(data);
        break;
    default:
        qDebug() << "Invalid state.";
        break;
    }
}

void CG_serverConnection::connectToServer(QString address, int port)
{
    m_socket = new QTcpSocket;

    this->handleConnections();
    m_socket->connectToHost(address, port);
}

void CG_serverConnection::sendMove(int fromFile, int fromRank, int toFile, int toRank)
{
    //Create local JSON object
    QJsonObject moveInfo;

    //Create object
    moveInfo["PacketHeader"] = OPPONENT_MOVE;
    moveInfo["StartFile"] = fromFile;
    moveInfo["StartRank"] = fromRank;
    moveInfo["EndFile"] = toFile;
    moveInfo["EndRank"] = toRank;

    //Create JSON document
    QJsonDocument doc;
    doc.setObject(moveInfo);

    //Debug
    qDebug() << doc.toJson();

    //Send over socket
    m_socket->write(doc.toBinaryData());
}

void CG_serverConnection::onOpponentMoved(QJsonObject &data)
{
    int fromFile = data["StartFile"].toInt();
    int fromRank = data["StartRank"].toInt();
    int toFile = data["EndFile"].toInt();
    int toRank = data["EndRank"].toInt();

    qDebug() << fromFile;
    qDebug() << fromRank;
    qDebug() << toFile;
    qDebug() << toRank;

    emit networkPlayerMoved(fromFile, fromRank, toFile, toRank);
}

QString CG_serverConnection::getOpponent()
{
    return m_opponent;
}

int CG_serverConnection::getOpponentELO()
{
    return m_opponentELO;
}

void CG_serverConnection::sendReady()
{
    //Create local JSON object
    QJsonObject userInfo;

    //Create object
    userInfo["PacketHeader"] = PLAYER_READY;

    //Create JSON document
    QJsonDocument doc;
    doc.setObject(userInfo);

    //Debug
    qDebug() << doc.toJson();

    //Send over socket
    m_socket->write(doc.toBinaryData());
}

void CG_serverConnection::sendQueueType(int timeControl)
{
    //Create local JSON object
    QJsonObject userInfo;

    //Create object
    userInfo["PacketHeader"] = QUEUE_REQUEST;
    userInfo["TimeControl"] = timeControl;

    //Create JSON document
    QJsonDocument doc;
    doc.setObject(userInfo);

    //Send over socket
    m_socket->write(doc.toBinaryData());
}

bool CG_serverConnection::getColor()
{
    return m_isWhite;
}
