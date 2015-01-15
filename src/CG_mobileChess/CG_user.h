#ifndef CG_USER_H
#define CG_USER_H

#include <QString>
#include <QObject>
#include "CG_dbManager.h"

/************************************************************************
* Class: CG_user
*
* Constructors:
*	CG_user(CG_dbManager * dbManager)
*       Sets up the user to reference the main db manager.
*
* Methods:
*   bool AddUser(QString username, QString password, QString email)
*       Returns whether or not the user was successfully added to the
*       database.
*   bool GetUser(QString username)
*       Returns whether or not a user with the given username exists.
*   bool LogIn(QString username, QString password)
*       Returns whether or not the user info given is correct.
*************************************************************************/

class CG_user : public QObject
{
    Q_OBJECT

    public:
        CG_user(CG_dbManager * dbManager);

    public slots:
        bool addUser(QString username, QString password, QString email);
        bool getUser(QString username);
        bool logIn(QString username, QString password);

        QString getUsername() { return str_username; }

    private:
        CG_dbManager * db_chessgames;

        QString str_username;
        QString str_email;
        QString str_joinDate;
        QString str_currentELO;

        int int_numGames;

        float flt_totalScore;
        float flt_totalOpponentELO;
};

#endif
