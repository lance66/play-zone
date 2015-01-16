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
    qDebug() << "Roar!!!!";
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
    std::string str_whiteID = std::to_string(whiteID);
    std::string str_blackID = std::to_string(blackID);

    //Convert string to const char *
    char const *whitePlayer = str_whiteID.c_str();
    char const *blackPlaya = str_blackID.c_str();

    //Notify white player of match
    whiteSocket->write("\nYou are playing with the white pieces against ");
    whiteSocket->write(blackPlaya);
    whiteSocket->write(".");
    whiteSocket->flush();
    whiteSocket->waitForBytesWritten(3000);

    //Notify black player of match
    blackSocket->write("\nYou are playing with the black pieces against ");
    blackSocket->write(whitePlayer);
    blackSocket->write(".");
    blackSocket->flush();
    blackSocket->waitForBytesWritten(3000);

    //Notify players they are in a match with opponent
    qDebug() << "Match between " << whiteID << " and " << blackID << " has been started.";
}

CG_Match::~CG_Match()
{
    //Close sockets
    whiteSocket->close();
    blackSocket->close();
}

void CG_Match::setPlayerIDs(int whteID, int blckID)
{
    this->whiteID = whteID;
    this->blackID = blckID;
}

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
            readBlacksMove();
        }
    }

    //If it's black turn to move
    else
    {
        readWhitesMove();
    }
}

/****************************************************************
*	Purpose:  Gets black's lates move by reading the move from
*             black's socket, and sending it to white by
*             writing the move to white's socket.
*
*     Entry:  NA
*
*      Exit:  Blacks move is sent to white.
****************************************************************/
void CG_Match::readBlacksMove()
{
    QByteArray move = blackSocket->readLine();
    whiteSocket->write(move);
}

/****************************************************************
*	Purpose:  Gets white's latest move by reading the move from
*             white's socket, and sending it to black by
*             writing the move to black's socket.
*
*     Entry:  NA
*
*      Exit:  Whites move is sent to black.
****************************************************************/
void CG_Match::readWhitesMove()
{
    QByteArray move = whiteSocket->readLine();
    blackSocket->write(move);
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
int CG_Match::getWhiteID()
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
int CG_Match::getBlackID()
{
    return this->blackID;
}

/****************************************************************
*	Purpose:  Sets the tcp client to the address that was
*               passed in.
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
QTcpSocket * CG_Match::getTcpSocket()
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

void CG_Match::setWhiteSocket(QTcpSocket *socket)
{
    whiteSocket = socket;
}

void CG_Match::setBlackSocket(QTcpSocket *socket)
{
    blackSocket = socket;
}
