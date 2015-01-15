#include "CG_dbManager.h"

/**************************************************************
*	  Purpose:  Constructor. Opens the database based upon the
*               db path specified.
*
*     Entry:  User has opened the app.
*
*     Exit:  The database is set to SQLite and the path to the
*            db is specified.
****************************************************************/

CG_dbManager::CG_dbManager(QString str_connection)
{
    //Connect to database
    db_login = QSqlDatabase::addDatabase("QSQLITE");
    db_login.setDatabaseName(str_connection);
}

/**************************************************************
*	  Purpose:  To check whether or not the user entered the
*               correct username and password and it exists in
*               the database.
*
*     Entry:  User has clicked the login button
*
*     Exit:  Returns whether or not the login info is correct.
****************************************************************/

bool CG_dbManager::correctUserInfo(QString str_username, QString str_password)
{
    int count = 0;

    if(db_login.open())
    {
        //Calls encryption password
        encryptPassword(str_password);

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

/**************************************************************
*	  Purpose:  To check whether or not the user exists in the
*               database.
*
*     Entry:  User has clicked the register button
*
*     Exit:  Returns whether or not the user exists.
****************************************************************/

bool CG_dbManager::userExists(QString str_username)
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

/**************************************************************
*	  Purpose:  To add a user into the database with the passed
*               parameters: username, password and email.
*
*     Entry:  User has clicked the register button
*
*     Exit:  Returns whether or not the user was successfully
*            added into the database.
****************************************************************/

bool CG_dbManager::addUser(QString str_username, QString str_password, QString str_email)
{
    bool added_user = false;

    if(db_login.open())
    {
        //Calls encryption password
        encryptPassword( str_password );

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

/**************************************************************
*	  Purpose:  To encrypt a password using the SHA256 hashing
*               function.
*
*     Entry:  User is attempting to login or register.
*
*     Exit:  Alters the password string based upon the SHA256
*            encryption.
****************************************************************/

void CG_dbManager::encryptPassword(QString & password)
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
