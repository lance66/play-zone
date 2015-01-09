#include "cg_match.h"

CG_Match::CG_Match()
    :whiteID(777), blackID(666)
{
    qDebug() << "Roar!!!!";
}

CG_Match::CG_Match(int whteID, int blckID)
    :whiteID(777), blackID(666)
{
    //Set data members to arguments
    this->whiteID = whteID;
    this->blackID = blckID;

    //Notify players they are in a match with opponent
    qDebug() << "Match between " << whiteID << " and " << blackID << " has been started.";
}

void CG_Match::sendMoveToServer(int whiteID, int blackID)
{
    //Read data into socket
    QByteArray data = socket->readLine();




}


