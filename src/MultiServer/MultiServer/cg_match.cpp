#include "cg_match.h"

/**************************************************************
*	  Purpose:  Constructor.  Initializes white's and black's
*               id.
*
*     Entry:  NA
*
*     Exit:  Data members are initialized.
****************************************************************/
CG_Match::CG_Match()
    :whiteID(777), blackID(666)
{
    qDebug() << "Roar!!!!";
}

/**************************************************************
*	  Purpose:  Constructor.  Initializes white's and black's
*              id.
*
*     Entry:  Two arguments, one for white's id, and the other
*             black's id.
*
*     Exit:  Data members are initialized.
****************************************************************/
CG_Match::CG_Match(int whteID, int blckID)
    :whiteID(777), blackID(666)
{
    //Set data members to arguments
    this->whiteID = whteID;
    this->blackID = blckID;

    //Notify players they are in a match with opponent
    qDebug() << "Match between " << whiteID << " and " << blackID << " has been started.";
}

/**************************************************************
*	  Purpose:  Sends move to the server
*
*     Entry:  Two arguments, one for white's id, and the other
*             black's id.
*
*     Exit:  Populates the QByteArray with the number of bytes
*            that were read
****************************************************************/
void CG_Match::sendMoveToServer(int whiteID, int blackID)
{
    //Read data into socket
    QByteArray data = socket->readLine();




}

/**************************************************************
*	  Purpose:  Sets the white id to the value passed in.
*
*     Entry:  an id that will be assigned to the whiteID
*             member.
*
*     Exit:  Sets the whiteID to the value that was passed in.
****************************************************************/
void CG_Match::setWhiteID(int whiteID)
{
    this->whiteID = whiteID;
}

/**************************************************************
*	  Purpose:  Gets the value of the white id
*
*     Entry:  NA
*
*     Exit:  Value of white id is returned.
****************************************************************/
int CG_Match::getWhiteID()
{
    return this->whiteID;
}

/**************************************************************
*	  Purpose:  Sets the black id to the value that was passed
*               in.
*
*     Entry:  An id that will be assigned to the black id.
*
*     Exit:  Black id member is assigned the value that was
*            passed in.
****************************************************************/
void CG_Match::setBlackID(int blackID)
{
    this->blackID = blackID;
}

/**************************************************************
*	  Purpose:  Gets the value of the black id.
*
*     Entry:  NA
*
*     Exit:  Value of black id is returned.
****************************************************************/
int CG_Match::getBlackID()
{
    return this->blackID;
}

/**************************************************************
*	  Purpose:  Sets the tcp client to the address that was
*               passed in.
*
*     Entry:  a QTcpSocket pointer that will be assigned to the
*             QTcpSocket member.
*
*     Exit:  Member socket points to socket that was passed in.
****************************************************************/
void CG_Match::setTcpSocket(QTcpSocket *socket)
{
    this->socket = socket;
}

/**************************************************************
*	  Purpose:  Retrieves the member socket.
*
*     Entry:  NA
*
*     Exit:  Returns the pointer to the socket.
****************************************************************/
QTcpSocket * CG_Match::getTcpSocket()
{
    return this->socket;
}
