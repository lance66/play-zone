#include "CG_match.h"
#include <stdio.h>

CG_Match::CG_Match(CG_playerConnection* player1, CG_playerConnection* player2, int time_control, QObject * parent)
    : QObject(parent), m_blackPlayerConnection(player2), m_whitePlayerConnection(player1), m_timeControl(time_control),
      m_whiteReady(false), m_blackReady(false)
{

    qDebug() << "Match between "
             << m_whitePlayerConnection->getUsername() << " ("
             << m_whitePlayerConnection->getELO() << ") "
             << "and "
             << m_blackPlayerConnection->getUsername() << " ("
             << m_blackPlayerConnection->getELO() << ") "
             << "has been started.";

    connect(m_blackPlayerConnection, &CG_playerConnection::playerMadeMove, this, &CG_Match::onBlackPlayerMove);
    connect(m_whitePlayerConnection, &CG_playerConnection::playerMadeMove, this, &CG_Match::onWhitePlayerMove);
    connect(m_blackPlayerConnection, &CG_playerConnection::playerReady, this, &CG_Match::onPlayerReady);
    connect(m_whitePlayerConnection, &CG_playerConnection::playerReady, this, &CG_Match::onPlayerReady);

    startMatch();
}

void CG_Match::startMatch()
{
    //Notify white player of match
    //m_whitePlayerConnection->getSocket()->write("Game Started.");
    m_whitePlayerConnection->beginConnectingToPlayer(m_blackPlayerConnection, WHITE);
    //Notify black player of match
    //m_blackPlayerConnection->getSocket()->write("Game Started.");
    m_blackPlayerConnection->beginConnectingToPlayer(m_whitePlayerConnection, BLACK);
    //Game starts
}

/****************************************************************
*	Purpose:  Constructor.  Initializes white's and black's
*             id.
*
*     Entry:  NA
*
*      Exit:  Data members are initialized.
****************************************************************/
//CG_Match::CG_Match()
//    :whiteID(777), blackID(666), isWhiteToMove(true),
//     isMatchOver(false), whiteSocket(nullptr), blackSocket(nullptr),
//     socket(nullptr), matchID(0), winner(0), loser(0)
//{
//    qDebug() << "Default CG_Match Constructor Called.";
//}

/****************************************************************
*	Purpose:  Constructor.  Initializes white's and black's
*             id.
*
*     Entry:  Two arguments, one for white's id, and the other
*             black's id.
*
*      Exit:  Data members are initialized.
****************************************************************/
//CG_Match::CG_Match(int whteID, int blckID, QTcpSocket *&whiteSocket, QTcpSocket *&blackSocket)
//    :whiteID(whteID), blackID(blckID), whiteSocket(whiteSocket),
//     blackSocket(blackSocket), isWhiteToMove(true), isMatchOver(false),
//     socket(nullptr), matchID(0), winner(0), loser(0), whitePlayer(nullptr),
//     blackPlayer(nullptr)
//{
//    //Convert IDs into const char *'s to write to socket
//    //Convert int to string

//    //Function doesn't work.  Make sure function works before you uncomment this!!!!!!!
//    //convertIDToCharConstPtr(whiteID, blackID);

//    std::string str_whiteID = std::to_string( whiteID );
//    std::string str_blackID = std::to_string( blackID );

//    const char * tempWhite = nullptr;
//    tempWhite = const_cast<char *>(str_whiteID.c_str());
//    strcpy_s(whitePlayer, 10, tempWhite);

//    const char * tempBlack = nullptr;
//    tempBlack = const_cast<char *>(str_blackID.c_str());
//    strcpy_s(blackPlayer, 10, tempBlack);

//    //Notifies both players
//    notifyPlayersOfMatchStarting( whiteSocket, blackSocket, blackPlayer, whitePlayer );

//    //Notify players they are in a match with opponent
//    qDebug() << "Match between " << whiteID << " and " << blackID << " has been started.";
//}

/****************************************************************
*	Purpose:  Starts the match between two players.
*
*     Entry:  The id's for both the white and black sockets, and
*             the TcpSockets for both players, so that they may
*             be able to transmit their moves to each other.
*
*      Exit:  Starts the match between two players.
****************************************************************/
//void CG_Match::startMatch(int whiteID, int blackID, QTcpSocket *whiteSocket, QTcpSocket *blackSocket)
//{
//    QByteArray playerMove;
//    qDebug() << "Match between " << whiteID << " and " << blackID << "has been started.";

//    //Notify white player of match
//    notifyPlayerOfOpponent(whiteSocket, "white", blackID);

//    //Notify black player of match
//    notifyPlayerOfOpponent(blackSocket, "black", whiteID);

//    //Game starts
//    bool gameOver = false;
//    bool isWhiteTurn = true;

//    while (!gameOver)
//    {
//        //Prompt white player to move
//        promptPlayerMove(whiteSocket);

//        //Prompt to black player to wait
//        promptPlayerWait(blackSocket);

//        //Calls readPlayerMove to get the white player's move.
//        playerMove = readPlayerMove(whiteSocket);

//        //Write white player's move to black socket
//        writePlayerMoveToOpponent(whiteID, blackSocket, playerMove);

//        //Switch sides
//        isWhiteTurn = !isWhiteTurn;

//        //Prompt black player to move
//        promptPlayerMove(blackSocket);

//        //Prompt to white player to wait
//        promptPlayerWait(whiteSocket);

//        //Calls readPlayerMove to get the black player's move.
//        playerMove = readPlayerMove(blackSocket);

//        //Write black player's move to white socket
//        writePlayerMoveToOpponent(blackID, whiteSocket, playerMove);

//        //Switch turn
//        isWhiteTurn = !isWhiteTurn;
//    }
//}

/****************************************************************
*	Purpose:  Converts player id to a type of const char *
*
*     Entry:  Integer representing the players id.
*
*      Exit:  Converts the passed in player id to a type
*             const char *.
****************************************************************/
//void CG_Match::convertIDToCharConstPtr(int whiteID, int blackID )
//{
//    std::string str_whiteID = std::to_string( whiteID );
//    std::string str_blackID = std::to_string( blackID );

//    const char * tempWhite = const_cast<char *>(str_whiteID.c_str());
//    strcpy_s(whitePlayer, 10, tempWhite);

//    const char * tempBlack = nullptr;
//    tempBlack = const_cast<char *>(str_blackID.c_str());
//    strcpy_s(blackPlayer, 10, tempBlack);
//}

/****************************************************************
*	Purpose:  Notifies players that the match is about to start.
*
*     Entry:  character pointer for the black player, and a
*             character pointer for the white player.
*
*      Exit:  Notifies both players that a match is starting.
****************************************************************/
//void CG_Match::notifyPlayersOfMatchStarting( QTcpSocket *&whiteSocket, QTcpSocket *&blackSocket, const char * blackPlayer, const char * whitePlayer )
//{
//    //Notify white player of match
//    notifyPlayerOfMatchStarting( whiteSocket, blackPlayer, "white pieces" );

//    //Notify black player of match
//    notifyPlayerOfMatchStarting( blackSocket, whitePlayer, "black pieces" );
//}


void CG_Match::onBlackPlayerMove(int startRank, int startFile, int endRank, int endFile)
{
    m_whitePlayerConnection->forwardOpponentMove(startRank,startFile,endRank,endFile);
}

void CG_Match::onWhitePlayerMove(int startRank, int startFile, int endRank, int endFile)
{
     m_blackPlayerConnection->forwardOpponentMove(startRank,startFile,endRank,endFile);
}

void CG_Match::onPlayerReady()
{
    CG_playerConnection * player = qobject_cast<CG_playerConnection*>(sender());
    if(m_whitePlayerConnection == player)
        m_whiteReady = true;
    else
        m_blackReady = true;

    if(m_whiteReady && m_blackReady)
    {
        m_whitePlayerConnection->sendMatchConnected();
        m_blackPlayerConnection->sendMatchConnected();
    }
}

/****************************************************************
*	Purpose:  Notifies the player passed in that the match is
*             starting, and who they are playing against.
*
*     Entry:  Player socket, so that we can send the message
*             Character pointer containing the opposing players,
*             information.
*
*      Exit:  Notifies the white player who they are playing
*             against, and that the match is starting.
****************************************************************/
//void CG_Match::notifyPlayerOfMatchStarting(QTcpSocket *&playerSocket, const char * player, const char * msg)
//{
//    playerSocket->write("\nYou are playing with the ");
//    playerSocket->write(msg);
//    playerSocket->write(" against ");
//    playerSocket->write(player);
//    playerSocket->write(".");
//    playerSocket->flush();
//    playerSocket->waitForBytesWritten(3000);
//}

/****************************************************************
*	Purpose:  Destructor - closes the sockets of both players
*
*     Entry:  NA
*
*      Exit:  Closes the sockets for both players
****************************************************************/
CG_Match::~CG_Match()
{
    //Close sockets
    //whiteSocket->close();
    //blackSocket->close();
}

/****************************************************************
*	Purpose:  Sets the player id's for both players involved
*             in the match.
*
*     Entry:  Two id's of type int, one for each player.
*
*      Exit:  Sets up the id's for both players.
****************************************************************/
//void CG_Match::setPlayerIDs(int whteID, int blckID)
//{
//    this->whiteID = whteID;
//    this->blackID = blckID;
//}

/****************************************************************
*	Purpose:  Sets the player sockets for both players involved
*             in the match.
*
*     Entry:  Two QTcpSockets, one for each player.
*
*      Exit:  Sets up the socket's for both players.
****************************************************************/
//void CG_Match::setPlayerSockets(QTcpSocket *whiteSocket, QTcpSocket *blackSocket)
//{
//    this->whiteSocket = whiteSocket;
//    this->blackSocket = blackSocket;
//}

/****************************************************************
*	Purpose:  Gets the opposing player's latest move by reading
*             the move from the opposing player's socket, and
*             sending it to white by writing the move to white's
*             socket.
*
*     Entry:  NA
*
*      Exit:  Opposing players move is sent to player, who has
*             the active turn.
****************************************************************/
//void CG_Match::readPlayersMove(QTcpSocket *playerSocket, QByteArray move)
//{
//    playerSocket->write(move);
//}

/****************************************************************
*	Purpose:  Sets the white id to the value passed in.
*
*     Entry:  an id that will be assigned to the whiteID
*             member.
*
*      Exit:  Sets the whiteID to the value that was passed in.
****************************************************************/
//void CG_Match::setWhiteID(int whiteID)
//{
//    this->whiteID = whiteID;
//}

/****************************************************************
*	Purpose:  Gets the value of the white id
*
*     Entry:  NA
*
*      Exit:  Value of white id is returned.
****************************************************************/
//int CG_Match::getWhiteID() const
//{
//    return this->whiteID;
//}

///****************************************************************
//*	Purpose:  Sets the black id to the value that was passed
//*             in.
//*
//*     Entry:  An id that will be assigned to the black id.
//*
//*      Exit:  Black id member is assigned the value that was
//*             passed in.
//****************************************************************/
//void CG_Match::setBlackID(int blackID)
//{
//    this->blackID = blackID;
//}

///****************************************************************
//*	Purpose:  Gets the value of the black id.
//*
//*     Entry:  NA
//*
//*      Exit:  Value of black id is returned.
//****************************************************************/
//int CG_Match::getBlackID() const
//{
//    return this->blackID;
//}

///****************************************************************
//*	Purpose:  Sets the tcp client to the address that was
//*             passed in.
//*
//*     Entry:  QTcpSocket pointer that will be assigned to the
//*             QTcpSocket member.
//*
//*      Exit:  Member socket points to socket that was passed in.
//****************************************************************/
//void CG_Match::setTcpSocket(QTcpSocket *socket)
//{
//    this->socket = socket;
//}

///****************************************************************
//*	Purpose:  Retrieves the member socket.
//*
//*     Entry:  NA
//*
//*      Exit:  Returns the pointer to the socket.
//****************************************************************/
//QTcpSocket * CG_Match::getTcpSocket() const
//{
//    return this->socket;
//}

///****************************************************************
// *  Purpose:  Changes whose turn it is, by inverting the boolean
// *            value move contains.
// *
// *    Entry:  Bool to determine if it is or is not's white's turn
// *            to move.
// *
// *     Exit:  Move inverts, so opponent can move their piece.
//****************************************************************/
//void CG_Match::setIsWhiteToMove(bool &move)
//{
//    move = !move;
//}

///****************************************************************
// *  Purpose:  Sets the white players socket.
// *
// *    Entry:  NA
// *
// *     Exit:  whiteSocket is set.
//****************************************************************/
//void CG_Match::setWhiteSocket(QMap<int, QTcpSocket *> socket, int whiteID)
//{
//    whiteSocket = socket[whiteID];
//}

///****************************************************************
// *  Purpose:  Sets the black players socket.
// *
// *    Entry:  NA
// *
// *     Exit:  blackSocket is set.
//****************************************************************/
//void CG_Match::setBlackSocket(QMap<int, QTcpSocket *> socket, int blackID)
//{
//    blackSocket = socket[blackID];
//}

////CG_Match::CG_Match(userInfo whitePlayer, userInfo blackPlayer, int timeControl)
////{
////
////}

//void CG_Match::notifyPlayerOfOpponent(QTcpSocket * player, const char * playerColor,
//                                      int opponent)
//{
//    //Convert int to const char *
//    char buf[256];
//    sprintf_s(buf, "%d", opponent);

//    player->write("\r\nYou are playing the ");
//    player->write(playerColor);
//    player->write(" pieces against ");
//    player->write(buf);
//    player->write(".");
//    player->flush();
//    player->waitForBytesWritten(3000);
//}

//void CG_Match::promptPlayerMove(QTcpSocket * player)
//{
//    player->write("\r\n\r\nEnter move: ");
//    player->flush();
//    player->waitForBytesWritten(3000);
//}

//void CG_Match::promptPlayerWait(QTcpSocket *player)
//{
//    player->write("\r\n\r\nWaiting for opponent to move...");
//    player->flush();
//    player->waitForBytesWritten(3000);
//}

//QByteArray CG_Match::readPlayerMove(QTcpSocket * player)
//{
//    QByteArray temp;
//    QByteArray playerMove;

//    //Wait for white to enter move
//    do
//    {
//        player->waitForReadyRead();
//        temp = player->readAll();
//        playerMove += temp;
//    }
//    while(temp == nullptr || temp.at(0) != 0x0d);

//    return playerMove;
//}

//void CG_Match::writePlayerMoveToOpponent(int ID,
//                                         QTcpSocket* opponent,
//                                         QByteArray playerMove)
//{
//    //Convert int to const char *
//    char buf[256];
//    sprintf_s(buf, "%d", ID);

//    opponent->write("\r\n");
//    opponent->write(buf);
//    opponent->write(" moves: ");
//    opponent->write(playerMove);
//}

void CG_Match::setWhitePlayerConnection(CG_playerConnection *whitePlayerConnection)
{
    m_whitePlayerConnection = whitePlayerConnection;
}

void CG_Match::setBlackPlayerConnection(CG_playerConnection *blackPlayerConnection)
{
    m_blackPlayerConnection = blackPlayerConnection;
}
