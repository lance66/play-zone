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

void CG_Match::setWhiteID(int whiteID)
{
    this->whiteID = whiteID;
}

int CG_Match::getWhiteID()
{
    return this->whiteID;
}

void CG_Match::setBlackID(int blackID)
{
    this->blackID = blackID;
}

int CG_Match::getBlackID()
{
    return this->blackID;
}

void CG_Match::setTcpSocket(QTcpSocket *socket)
{
    this->socket = socket;
}

QTcpSocket * CG_Match::getTcpSocket()
{
    return this->socket;
}
