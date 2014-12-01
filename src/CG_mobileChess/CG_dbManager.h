#ifndef CG_DBMANAGER_H
#define CG_DBMANAGER_H

#include <QString>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QCryptographicHash>  // Needed for encrypting in SHA256

/******************************************************************************
* Class: CG_dbManager
*
* Constructors:
*	CG_dbManager(QString str_connection)
*       Opens the SQLite database for connection based upon the db path passed.
*
* Methods:
*   bool UserExists(QString str_username)
*       Returns whether or not a user with the passed username exists in
*       the database.
*   bool CorrectUserInfo(QString str_username, QString str_password)
*       Returns whether or not the username and password info are correct
*       and in the database.
*   bool AddUser(QString str_username, QString str_password, QString str_email)
*       Returns true if the user is successfully added into the database.
*******************************************************************************/

class CG_dbManager
{
    public:
        CG_dbManager(QString str_connection);

        bool UserExists(QString str_username);
        bool CorrectUserInfo(QString str_username, QString str_password);
        bool AddUser(QString str_username, QString str_password, QString str_email);
        void EncryptPassword(QString & password);

    private:
        QSqlDatabase db_login;
};

#endif
