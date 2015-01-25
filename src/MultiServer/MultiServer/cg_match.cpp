#include "cg_match.h"

/****************************************************************
*	Purpose:  Constructor.  Initializes white's and black's
*             id.
*
*     Entry:  NA
*
*      Exit:  Data members are initialized.
****************************************************************/
CG_Match::CG_Match()
    :whiteID(777), blackID(666)
{
    qDebug() << "Default CG_Match Constructor Called.";
}

/****************************************************************
*	Purpose:  Constructor.  Initializes white's and black's
*             id.
*
*     Entry:  Two arguments, one for white's id, and the other
*             black's id.
*
*      Exit:  Data members are initialized.
****************************************************************/
CG_Match::CG_Match(int whteID, int blckID, QTcpSocket *&whiteSocket, QTcpSocket *&blackSocket)
    :whiteID(777), blackID(666)
{
    //Set data members to arguments
    setPlayerIDs( whteID, blckID );
    setPlayerSockets( whiteSocket, blackSocket );

    isWhiteToMove = false;

    //Convert IDs into const char *'s to write to socket
    //Convert int to string
    std::string str_whiteID = std::to_string( whiteID );
    std::string str_blackID = std::to_string( blackID );

    char const * whitePlayer = str_whiteID.c_str();
    char const * blackPlayer = str_blackID.c_str();

    //Notifies both players
    notifyPlayersOfMatchStarting( whiteSocket, blackSocket, blackPlayer, whitePlayer );

    //Notify players they are in a match with opponent
    qDebug() << "Match between " << whiteID << " and " << blackID << " has been started.";
}

/****************************************************************
*	Purpose:  Starts the match between two players.
*
*     Entry:  The id's for both the white and black sockets, and
*             the TcpSockets for both players, so that they may
*             be able to transmit their moves to each other.
*
*      Exit:  Starts the match between two players.
****************************************************************/
void CG_Match::startMatch(int whiteID, int blackID, QTcpSocket *whiteSocket, QTcpSocket *blackSocket)
{
    qDebug() << "Match between " << whiteID << " and " << blackID << "has been started.";

    std::string str_whiteID = std::to_string( whiteID );
    std::string str_blackID = std::to_string( blackID );

    char const * whitePlayer = str_whiteID.c_str();
    char const * blackPlayer = str_blackID.c_str();

    //Notify white player of match
    whiteSocket->write("\r\nYou are playing with the white pieces against ");
    whiteSocket->write(blackPlayer);
    whiteSocket->write(".");
    whiteSocket->flush();
    whiteSocket->waitForBytesWritten(3000);

    //Notify black player of match
    blackSocket->write("\r\nYou are playing with the black pieces against ");
    blackSocket->write(whitePlayer);
    blackSocket->write(".");
    blackSocket->flush();
    blackSocket->waitForBytesWritten(3000);

    //Match starts
    bool gameOver = false;
    bool isWhiteTurn = true;

    while (gameOver != true)
    {
        //Prompt white player to move
        whiteSocket->write("\r\n\r\nEnter move: ");
        whiteSocket->flush();
        whiteSocket->waitForBytesWritten(3000);

        //Prompt to black player to wait
        blackSocket->write("\r\n\r\nWaiting for opponent to move...");
        blackSocket->flush();
        blackSocket->waitForBytesWritten(3000);

        QByteArray temp;
        QByteArray whiteMove;

        //Wait for white to enter move
        do
        {
            whiteSocket->waitForReadyRead();
            temp = whiteSocket->readAll();
            whiteMove += temp;
        }

        while(temp.at(0) != 0x0d);

        //Write move to black socket
        blackSocket->write("\r\n");
        blackSocket->write(whitePlayer);
        blackSocket->write(" moves: ");
        blackSocket->write(whiteMove);

        //Switch sides
        isWhiteTurn = !isWhiteTurn;

        //Prompt black player to move
        blackSocket->write("\r\n\r\nEnter move: ");
        blackSocket->flush();
        blackSocket->waitForBytesWritten(3000);

        //Prompt to white player to wait
        whiteSocket->write("\r\n\r\nWaiting for opponent to move...");
        whiteSocket->flush();
        whiteSocket->waitForBytesWritten(3000);

        QByteArray temp1;
        QByteArray blackMove;
        //Wait for black to enter move
        do
        {
            blackSocket->waitForReadyRead();
            temp1 = blackSocket->readLine();
            blackMove += temp1;
        }
        while(temp1.at(0) != 0x0d);

        //Write move to white socket
        whiteSocket->write("\r\n");
        whiteSocket->write(blackPlayer);
        whiteSocket->write(" moves: ");
        whiteSocket->write(blackMove);

        //Switch turn
        isWhiteTurn = !isWhiteTurn;
    }
}

/****************************************************************
*	Purpose:  Converts player id to a type of const char *
*
*     Entry:  Integer representing the players id.
*
*      Exit:  Converts the passed in player id to a type
*             const char *.
****************************************************************/
void CG_Match::convertIDToCharConstPtr( const char *& whitePlayer, const char *& blackPlayer, int whiteID, int blackID )
{
    std::string str_whiteID = std::to_string( whiteID );
    std::string str_blackID = std::to_string( blackID );

    whitePlayer = str_whiteID.c_str();
    blackPlayer = str_blackID.c_str();
}

/****************************************************************
*	Purpose:  Notifies players that the match is about to start.
*
*     Entry:  character pointer for the black player, and a
*             character pointer for the white player.
*
*      Exit:  Notifies both players that a match is starting.
****************************************************************/
void CG_Match::notifyPlayersOfMatchStarting( QTcpSocket *&whiteSocket, QTcpSocket *&blackSocket, const char * blackPlayer, const char * whitePlayer )
{
    //Notify white player of match
    notifyPlayerOfMatchStarting( whiteSocket, blackPlayer, "white pieces" );

    //Notify black player of match
   notifyPlayerOfMatchStarting( blackSocket, whitePlayer, "black pieces" );
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
void CG_Match::notifyPlayerOfMatchStarting(QTcpSocket *&playerSocket, const char * player, const char * msg)
{
    playerSocket->write("\nYou are playing with the ");
    playerSocket->write(msg);
    playerSocket->write(" against ");
    playerSocket->write(player);
    playerSocket->write(".");
    playerSocket->flush();
    playerSocket->waitForBytesWritten(3000);
}

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
void CG_Match::setPlayerIDs(int whteID, int blckID)
{
    this->whiteID = whteID;
    this->blackID = blckID;
}

/****************************************************************
*	Purpose:  Sets the player sockets for both players involved
*             in the match.
*
*     Entry:  Two QTcpSockets, one for each player.
*
*      Exit:  Sets up the socket's for both players.
****************************************************************/
void CG_Match::setPlayerSockets(QTcpSocket *whiteSocket, QTcpSocket *blackSocket)
{
    this->whiteSocket = whiteSocket;
    this->blackSocket = blackSocket;
}

/****************************************************************
*	Purpose:  Sends move to the server
*
*     Entry:  Two arguments, one for white's id, and the other
*             black's id.
*
*      Exit:  Populates the QByteArray with the number of bytes
*             that were read
****************************************************************/
void CG_Match::sendMoveToServer(int whiteID, int blackID)
{
    //Switch turns
    setIsWhiteToMove(isWhiteToMove);

    //If it's white's turn to move
    if(isWhiteToMove)
    {
        //Read black's socket if it's not the first move
        if(blackSocket->readLine() != nullptr)
        {
            readPlayersMove(whiteSocket, blackSocket->readLine());
        }
    }

    //If it's black turn to move
    else
    {
        readPlayersMove(blackSocket, whiteSocket->readLine());
    }
}

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
void CG_Match::readPlayersMove(QTcpSocket *playerSocket, QByteArray move)
{
    playerSocket->write(move);
}

/****************************************************************
*	Purpose:  Sets the white id to the value passed in.
*
*     Entry:  an id that will be assigned to the whiteID
*             member.
*
*      Exit:  Sets the whiteID to the value that was passed in.
****************************************************************/
void CG_Match::setWhiteID(int whiteID)
{
    this->whiteID = whiteID;
}

/****************************************************************
*	Purpose:  Gets the value of the white id
*
*     Entry:  NA
*
*      Exit:  Value of white id is returned.
****************************************************************/
int CG_Match::getWhiteID() const
{
    return this->whiteID;
}

/****************************************************************
*	Purpose:  Sets the black id to the value that was passed
*             in.
*
*     Entry:  An id that will be assigned to the black id.
*
*      Exit:  Black id member is assigned the value that was
*             passed in.
****************************************************************/
void CG_Match::setBlackID(int blackID)
{
    this->blackID = blackID;
}

/****************************************************************
*	Purpose:  Gets the value of the black id.
*
*     Entry:  NA
*
*      Exit:  Value of black id is returned.
****************************************************************/
int CG_Match::getBlackID() const
{
    return this->blackID;
}

/****************************************************************
*	Purpose:  Sets the tcp client to the address that was
*             passed in.
*
*     Entry:  QTcpSocket pointer that will be assigned to the
*             QTcpSocket member.
*
*      Exit:  Member socket points to socket that was passed in.
****************************************************************/
void CG_Match::setTcpSocket(QTcpSocket *socket)
{
    this->socket = socket;
}

/****************************************************************
*	Purpose:  Retrieves the member socket.
*
*     Entry:  NA
*
*      Exit:  Returns the pointer to the socket.
****************************************************************/
QTcpSocket * CG_Match::getTcpSocket() const
{
    return this->socket;
}

/****************************************************************
 *  Purpose:  Changes whose turn it is, by inverting the boolean
 *            value move contains.
 *
 *    Entry:  Bool to determine if it is or is not's white's turn
 *            to move.
 *
 *     Exit:  Move inverts, so opponent can move their piece.
****************************************************************/
void CG_Match::setIsWhiteToMove(bool &move)
{
    move = !move;
}

/****************************************************************
 *  Purpose:  Sets the white players socket.
 *
 *    Entry:  NA
 *
 *     Exit:  whiteSocket is set.
****************************************************************/
void CG_Match::setWhiteSocket(QMap<int, QTcpSocket *> socket, int whiteID)
{
    whiteSocket = socket[whiteID];
}

/****************************************************************
 *  Purpose:  Sets the black players socket.
 *
 *    Entry:  NA
 *
 *     Exit:  blackSocket is set.
****************************************************************/
void CG_Match::setBlackSocket(QMap<int, QTcpSocket *> socket, int blackID)
{
    blackSocket = socket[blackID];
}

//CG_Match::CG_Match(userInfo whitePlayer, userInfo blackPlayer, int timeControl)
//{
//
//}
