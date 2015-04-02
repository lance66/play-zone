#ifndef CG_DBMANAGER_H
#define CG_DBMANAGER_H

#include <QString>
#include <QVariant>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QFile>
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
*   QString getCurrentELO(QString str_username)
*       Returns the current ELO of a user.
*******************************************************************************/

class CG_dbManager : public QObject
{
    Q_OBJECT

    public:
        CG_dbManager(QString str_connection);

    public slots:
        bool userExists(QString str_username);
        bool correctUserInfo(QString str_username, QString str_password);
        bool addUser(QString str_username, QString str_password, QString str_email);
        bool updateCountryFlag(QString str_username, int country_flag);
        int getCountryFlag(QString str_username);
        void encryptPassword(QString & password);

        QString getCurrentELO(QString str_username);

    private:
        QSqlDatabase db_login;
};

#endif
