#include "CG_dbManager.h"

CG_dbManager::CG_dbManager(QString str_connection)
{
    //Connect to database
    db_login = QSqlDatabase::addDatabase("QSQLITE");

    //For deployment use the line below rather than the one above
    db_login.setDatabaseName(str_connection);
}

bool CG_dbManager::CorrectUserInfo(QString str_username, QString str_password)
{
    int count = 0;

    if(db_login.open())
    {
        //Calls encryption password
        EncryptPassword(str_password);

        QSqlQuery qry( db_login );
        qry.prepare( "SELECT * FROM CG_user WHERE Username= ? AND Passwd= ? COLLATE NOCASE" );
        qry.addBindValue(str_username);
        qry.addBindValue(str_password);

        if(qry.exec())
            for (; qry.next(); count++);

        db_login.close();
    }

    //Returns if the database finds a username and password match
    return count > 0;
}

bool CG_dbManager::UserExists(QString str_username)
{
    int count = 0;

    if(db_login.open())
    {
        QSqlQuery qry( db_login );
        qry.prepare( "SELECT * FROM CG_user WHERE Username= ? COLLATE NOCASE" );
        qry.addBindValue(str_username);

        if(qry.exec())
            for (; qry.next(); count++);

        db_login.close();
    }

    return count > 0;
}

bool CG_dbManager::AddUser(QString str_username, QString str_password, QString str_email)
{
    bool added_user = false;

    if(db_login.open())
    {
        //Calls encryption password
        EncryptPassword( str_password );

        QSqlQuery qry( db_login );
        qry.prepare( "INSERT INTO CG_user (Username, Passwd, Email) VALUES(?, ?, ?)" );
        qry.addBindValue(str_username);
        qry.addBindValue(str_password);
        qry.addBindValue(str_email);

        if(qry.exec())
            added_user = true;

        db_login.close();
    }

    return added_user;
}

void CG_dbManager::EncryptPassword(QString & password)
{
    // Takes the text in the le_password and converts it to Utf8, so it can be placed in a type of 'const char *' next
    QByteArray passwordInBytes = password.toUtf8();

    // casting the data in passwordInBytes (currently in the form of 'Utf8' to a type of 'const char *'
    const char * convertedPasswordToVerify = passwordInBytes.constData();

            /* Instantiating an object that will create the hashing key for the password. Takes an argument specifying
             * the encryption type you would like be executed on the string */
    QCryptographicHash sha256PasswordEncryptionGenerator( QCryptographicHash::Sha256 );

    // Adding the data to password encryption generator
    sha256PasswordEncryptionGenerator.addData( convertedPasswordToVerify );

    // Converting the password to the hash key using the result method and placing it in password.
    password = (QString)sha256PasswordEncryptionGenerator.result();
}
