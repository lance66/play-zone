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
    m_whitePlayerConnection->beginConnectingToPlayer(m_blackPlayerConnection, WHITE);
    m_blackPlayerConnection->beginConnectingToPlayer(m_whitePlayerConnection, BLACK);
}

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
*	Purpose:  Destructor - closes the sockets of both players
*
*     Entry:  NA
*
*      Exit:  Closes the sockets for both players
****************************************************************/
CG_Match::~CG_Match()
{
}

void CG_Match::setWhitePlayerConnection(CG_playerConnection *whitePlayerConnection)
{
    m_whitePlayerConnection = whitePlayerConnection;
}

void CG_Match::setBlackPlayerConnection(CG_playerConnection *blackPlayerConnection)
{
    m_blackPlayerConnection = blackPlayerConnection;
}
