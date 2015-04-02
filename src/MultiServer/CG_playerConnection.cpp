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
CG_playerConnection::CG_playerConnection(QString username, int countryname, QTcpSocket * socket, int elo_rating,  QObject *parent):
    QObject(parent), m_username(username), m_countryname(countryname), m_socket(socket), m_ELO(elo_rating)
{
    // Set up signals and slots properly with readyRead and disconnect methods
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

void CG_playerConnection::connections()
{
    connect(m_socket, &QTcpSocket::readyRead, this, &CG_playerConnection::readyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &CG_playerConnection::disconnected);
}

void CG_playerConnection::sendRequestPlayerInfo()
{
    // Create local JSON document
    QJsonDocument message;

    // Create local JSON object
    QJsonObject   request;

    // Create packet header to tell client what the server is requesting
    request["PacketHeader"] = PLAYER_INFO;

    // Set JSON object to JSON document, so server can write object to socket
    message.setObject(request);

    // Convert document to byte array
    QByteArray message_out = message.toBinaryData();

    // Write document (i.e. which is now a byte array) to socket
    m_socket->write(message_out);
}

void CG_playerConnection::sendConnectedToQueue()
{
    // Create local JSON document that will hold JSON object.
    // Needed to write send object over socket
    QJsonDocument message;

    // Create local JSON object to hold our request that the server will send to the client
    QJsonObject   request;

    // When sending a request, always include a packet header, so the client knows
    // how to handle the request
    request["PacketHeader"] = QUEUE_CONNECTED;

    // Detect which server is sending request
    CG_Server * server = qobject_cast<CG_Server *>(this->parent());

    // Build our JSON object
    request["PlayerCount"]  = server->getPlayerCount();
    request["MatchCount"]   = server->getMatchCount();
    request["QueueCount"]   = server->getQueueCount();

    // Set object to document
    message.setObject(request);

    // Convert JSON document to byte array
    QByteArray message_out = message.toBinaryData();

    // Write JSON document over socket
    m_socket->write(message_out);
}

void CG_playerConnection::sendConnectingToGame(QString players_name, int elo, int countryFlag, bool color)
{
    // Create local JSON document
    QJsonDocument message;

    // Create local JSON object
    QJsonObject   request;

    // Build object
    request["PacketHeader"] = CONNECTING_TO_GAME;
    request["Opponent"]  = players_name;
    request["ELO"]       = elo;
    request["CountryFlag"] = countryFlag;
    request["IsWhite"]   = color;

    // Set object to document (i.e. so we can write this to the socket)
    message.setObject(request);

    // Convert document to byte array
    QByteArray message_out = message.toBinaryData();

    // Write document (i.e. which is now a byte array) to socket
    m_socket->write(message_out);
}

void CG_playerConnection::sendMatchConnected()
{
    // Create local JSON document
    QJsonDocument message;

    // Create local JSON object
    QJsonObject   request;

    // Create packet header to tell client what type of request the server is making
    request["PacketHeader"] = GAME_READY;

    // Bind JSON object to JSON document to write to socket
    message.setObject(request);

    // Convert JSON document to byte array
    QByteArray message_out = message.toBinaryData();

    // Write document (i.e which is now a byte array) to socket
    m_socket->write(message_out);
}

// TODO -- Change name from forwardOpponentMove to sendOpponentMove
void CG_playerConnection::forwardOpponentMove(int startRank, int startFile,int endRank, int endFile)
{
    // Create local JSON document
    QJsonDocument message;

    // Create local JSON object
    QJsonObject   request;

    // Create packet header to notify opponent we want to send them a move
    request["PacketHeader"] = OPPONENT_MOVE;

    // Four items are needed to construct a move
    // (i.e. From Row, From Column, To Row, To Column)
    request["StartRank"] = startRank;
    request["StartFile"] = startFile;
    request["EndRank"] = endRank;
    request["EndFile"] = endFile;

    // Set object to JSON document
    message.setObject(request);

    //Convert JSON document to byte array
    QByteArray message_out = message.toBinaryData();

    // Write document (i.e. which is now a byte array) to socket
    m_socket->write(message_out);
}

void CG_playerConnection::handleRequest(PacketHeader requestID, QJsonObject &data)
{
    // When server receives request from client, handle it according to packet header
    // which details what information to expect from client
    switch(requestID)
    {
    case PLAYER_INFO:
        // Client will send information about who connected to server
        // (i.e. username, ELO, country flag, etc)
        // almost immediately after they connect to server
        parsePlayerInfo(data);
        break;

    case OPPONENT_MOVE:
        // When opponent moves, expect fromFile, fromRank, toFile, toRank to be sent
        parsePlayerMove(data);
        break;

    case QUEUE_REQUEST:
        // Client will request what type of queue they want to be placed in
        // (i.e. OneMinute, FiveMinute or ThirtyMinute queues)
        parseQueueJoinRequest(data);
        break;

    case PLAYER_READY:
        // When client is ready for the game, emit playerReady() signal
        parseReady(data);
        break;

    default:
        // If packet header does not match anything in the case statement...
        qDebug() << "Bad Request ID received";
    }
}

void CG_playerConnection::parsePlayerInfo(QJsonObject &data)
{
    // When client sends their information to the server,
    // Store information inside data members of CG_playerConnection
    m_username = data["Username"].toString();
    m_ELO      = data["ELO"].toInt();
    m_countryname = data["CountryFlag"].toInt();
}

void CG_playerConnection::parsePlayerMove(QJsonObject & data)
{
    // When client sends a move, build the JSON object
    int startRank = data["StartRank"].toInt();
    int startFile = data["StartFile"].toInt();
    int endRank   = data["EndRank"].toInt();
    int endFile   = data["EndFile"].toInt();

    // Send signal that player made a move
    emit playerMadeMove(startRank,startFile,endRank,endFile);
}

void CG_playerConnection::parseQueueJoinRequest(QJsonObject &data)
{
    // Get time control that the client requested (i.e. 1, 5, or 30 minute)
    TimeControl timeControl = TimeControl(data["TimeControl"].toInt());

    // Send signal to type of time control they selected
    emit queueJoinTypeRequest(timeControl);
}

void CG_playerConnection::parseReady(QJsonObject &data)
{
    emit playerReady();
}

void CG_playerConnection::beginConnectingToPlayer(CG_playerConnection *player, bool color)
{
    // Connect to opponent
    sendConnectingToGame(player->getUsername(),player->getELO(), player->getCountryFlag(), color);
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
    // Read socket and put in byte array
    m_messagebuffer.append(m_socket->readAll());

    // Check if we are done reading the socket
    if(m_socket->bytesAvailable() == 0)
    {
        // Create local JSON document from message we just read
        QJsonDocument  message_received =  QJsonDocument::fromBinaryData(m_messagebuffer);

        // Create local JSON object from document
        QJsonObject    message(message_received.object());

        // Create appropriate packet header
        PacketHeader   header = (PacketHeader)message["PacketHeader"].toInt();

        //Pass packet header to handle request, so we know what is being asked to do
        handleRequest(header,message);

        //Clear the message buffer because the server will use it again later
        m_messagebuffer.clear();
    }
    else
        // If we are not done reading the socket, keep reading the socket
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
    // Echo whoever disconnected from server
    qDebug() << "Client " << m_username << " disconnected";

    // Delete their socket at server's convenience
    m_socket->deleteLater();

    // Send signal to notify other classes that client disconnected
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

void CG_playerConnection::setCountryFlag(int countryFlag)
{
    m_countryname = countryFlag;
}

int CG_playerConnection::getCountryFlag() const
{
    return m_countryname;
}
