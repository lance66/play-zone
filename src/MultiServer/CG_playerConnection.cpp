#include "CG_playerConnection.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "CG_server.h"

/****************************************************************
*   Purpose:  Constructor. Initializes data members.
*
*     Entry:  NA
*
*      Exit:  Data members are initialized.
****************************************************************/
CG_playerConnection::CG_playerConnection(QString username, QString countryname, QTcpSocket * socket, int elo_rating,  QObject *parent):
    QObject(parent), m_username(username), m_countryname(countryname), m_socket(socket), m_ELO(elo_rating)
{
    connections();
}

/****************************************************************
 *  Purpose:  Destructor
 *
 *    Entry:  NA
 *
 *     Exit:  Removes the instance of the invoking player thread.
****************************************************************/
CG_playerConnection::~CG_playerConnection()
{
}

/****************************************************************
*   Purpose:  Starts thread, and notifies client that they
*             are connected.
*
*     Entry:  NA
*
*      Exit:  Thread is started, and client is notified.
****************************************************************/
 /* void CG_playerConnection::run()
{
    //Print starting thread
  qDebug() << socketDescriptor << " Starting thread";

    //Create socket
    socket = new QTcpSocket;

    //If socket descriptor cannot be set, something went wrong and emit an error
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    //When socket is ready to be read, create a direct connection
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    //Print which client is connected
    qDebug() << socketDescriptor << " Client Connected";

    //Call this function or thread will randomly stop
    exec();
}*/

void CG_playerConnection::connections()
{
    connect(m_socket, &QTcpSocket::readyRead, this, &CG_playerConnection::readyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &CG_playerConnection::disconnected);
}


void CG_playerConnection::sendConnectedToQueue()
{
    QJsonDocument message;
    QJsonObject   request;
    request["PacketHeader"] = QUEUE_CONNECTED;
    CG_Server * server = qobject_cast<CG_Server *>(this->parent());
    request["PlayerCount"]  = server->getPlayerCount();
    request["MatchCount"]   = server->getMatchCount();
    request["QueueCount"]   = server->getQueueCount();
    message.setObject(request);
    QByteArray message_out = message.toBinaryData();
    m_socket->write(message_out);
}

void CG_playerConnection::handleRequest(PacketHeader requestID, QJsonObject &data)
{
    switch(requestID)
    {
        case PLAYER_INFO:
            parsePlayerInfo(data);
            break;

        case OPPONENT_MOVE:
            parsePlayerMove(data);
            break;

        case QUEUE_REQUEST:
            parseQueueJoinRequest(data);
            break;

        case PLAYER_READY:
            parseReady(data);
            break;

        default: qDebug() << "Bad Request ID received";
    }
}


void CG_playerConnection::parsePlayerInfo(QJsonObject &data)
{
    m_username = data["Username"].toString();
    m_ELO      = data["ELO"].toInt();
    m_countryname = data["CountryFlag"].toString();


}


void CG_playerConnection::beginConnectingToPlayer(CG_playerConnection *player, bool color)
{
    sendConnectingToGame(player->getUsername(),player->getELO(),color);
}

void CG_playerConnection::sendConnectingToGame(QString players_name, int elo, bool color)
{
    QJsonDocument message;
    QJsonObject   request;
    request["PacketHeader"] = CONNECTING_TO_GAME;
    request["Opponent"]  = players_name;
    request["ELO"]       = elo;
    request["IsWhite"]   = color;
    message.setObject(request);
    QByteArray message_out = message.toBinaryData();
    m_socket->write(message_out);
}

/****************************************************************
*   Purpose:  Sends user's message, and writes message to
*             the socket.
*
*     Entry:  NA
*
*      Exit:  Sends users message, and writes it to the socket.
****************************************************************/
void CG_playerConnection::readyRead()
{
    //Read the socket and put it in a byte array
    // QByteArray Data = socket->readLine();
    m_messagebuffer.append(m_socket->readAll());
    if(m_socket->bytesAvailable() == 0)
    {
        QJsonDocument  message_received =  QJsonDocument::fromBinaryData(m_messagebuffer);
        QJsonObject    message(message_received.object());
        PacketHeader   header = (PacketHeader)message["PacketHeader"].toInt();
        handleRequest(header,message);
        m_messagebuffer.clear();
    }
    else
        this->readyRead();

}

/****************************************************************
*   Purpose: Notifies the users that the server is
*            disconnected and closes the socket, when server
*            disconnects.
*
*    Entry:  NA
*
*     Exit:  Closes socket, and notifies user of disconnection.
****************************************************************/
void CG_playerConnection::disconnected()
{
    qDebug() << "Client " << m_username << " disconnected";

    m_socket->deleteLater();
    emit playerDisconnected();

}

/****************************************************************
*   Purpose: Returns the player's socket.
*
*    Entry:  NA
*
*     Exit:  Players socket is returned.
****************************************************************/
QTcpSocket *CG_playerConnection::getSocket()
{
    return m_socket;
}

void CG_playerConnection::sendRequestPlayerInfo()
{
    QJsonDocument message;
    QJsonObject   request;
    request["PacketHeader"] = PLAYER_INFO;
    message.setObject(request);
    QByteArray message_out = message.toBinaryData();
    //qDebug() << message_out;
    m_socket->write(message_out);

}


QString CG_playerConnection::getUsername() const
{
    return m_username;
}

int CG_playerConnection::getELO() const
{
    return m_ELO;
}

void CG_playerConnection::setUsername(QString username)
{
    m_username = username;
}

void CG_playerConnection::setELO(int ELO)
{
    m_ELO = ELO;
}


void CG_playerConnection::parsePlayerMove(QJsonObject & data)
{
    int startRank = data["StartRank"].toInt();
    int startFile = data["StartFile"].toInt();
    int endRank   = data["EndRank"].toInt();
    int endFile   = data["EndFile"].toInt();

    emit playerMadeMove(startRank,startFile,endRank,endFile);
}

void CG_playerConnection::forwardOpponentMove(int startRank, int startFile,int endRank, int endFile)
{
    QJsonDocument message;
    QJsonObject   request;
    request["PacketHeader"] = OPPONENT_MOVE;
    request["StartRank"] = startRank;
    request["StartFile"] = startFile;
    request["EndRank"] = endRank;
    request["EndFile"] = endFile;
    message.setObject(request);
    QByteArray message_out = message.toBinaryData();
    m_socket->write(message_out);
}


void CG_playerConnection::parseQueueJoinRequest(QJsonObject &data)
{
    TimeControl timeControl = TimeControl(data["TimeControl"].toInt());
    emit queueJoinTypeRequest(timeControl);
}


void CG_playerConnection::parseReady(QJsonObject &data)
{
    emit playerReady();
}

void CG_playerConnection::sendMatchConnected()
{
    QJsonDocument message;
    QJsonObject   request;
    request["PacketHeader"] = GAME_READY;
    message.setObject(request);
    QByteArray message_out = message.toBinaryData();
    m_socket->write(message_out);
}


