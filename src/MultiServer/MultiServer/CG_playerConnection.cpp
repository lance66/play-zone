#include "CG_playerConnection.h"

/****************************************************************
*   Purpose:  Constructor. Initializes data members.
*
*     Entry:  NA
*
*      Exit:  Data members are initialized.
****************************************************************/
CG_playerConnection::CG_playerConnection(qintptr ID, QObject *parent) :
    QThread(parent), m_username("Trudodyr"), m_ELO(2715), m_countryFlag("United States")
{
    this->socketDescriptor = ID;
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
void CG_playerConnection::run()
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
     QByteArray Data = socket->readLine();

     //When the user presses enter...
     socket->write(Data);
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
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
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
    return socket;
}

/****************************************************************
*   Purpose:  Retrives socket descriptor.
*
*     Entry:  NA
*
*      Exit:  Socket descriptor is returned.
****************************************************************/
qintptr CG_playerConnection::getSocketDescriptor() const
{
    return socketDescriptor;
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
