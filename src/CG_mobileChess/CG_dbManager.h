#ifndef CG_DBMANAGER_H
#define CG_DBMANAGER_H

#include <QString>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QCryptographicHash>  // Needed for encrypting in SHA256

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
