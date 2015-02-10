#include "CG_user.h"

/**************************************************************
*	  Purpose:  Constructor.  Passes the reference of the
*               main db manager to the class.
*
*     Entry:  The db manager has been set up.
*
*     Exit:  A reference to the main db manager has been passed
*            to the class.
****************************************************************/

CG_user::CG_user(CG_dbManager * dbManager)
{
    db_chessgames = dbManager;
    str_username = "Radjabov";
    str_currentELO = "2710";
}

/**************************************************************
*	  Purpose:  To check whether the user entered a valid
*               username and password.
*
*     Entry:  User has clicked the login button
*
*     Exit:  Returns whether or not the username and password
*            are correct.
****************************************************************/

bool CG_user::logIn(QString username, QString password)
{
    bool logged_in = false;

    if (db_chessgames->correctUserInfo(username, password))
        logged_in = true;

    return logged_in;
}

/**************************************************************
*	  Purpose:  To check if user exists in database.
*
*     Entry:  User has clicked the register button
*
*     Exit:  Returns whether or not the user exists in the
*            database.
****************************************************************/

bool CG_user::getUser(QString username)
{
    bool user_exists = false;

    if(db_chessgames->userExists(username))
        user_exists = true;

    return user_exists;
}

/**************************************************************
*	  Purpose:  To add a user to the database.
*
*     Entry:  Username and password has been validated at login
*             screen.
*
*     Exit:  Returns whether or not the user has been
*            successfully added to the database.
****************************************************************/

bool CG_user::addUser(QString username, QString password, QString email)
{
    bool added_user = false;

    if (db_chessgames->addUser(username, password, email))
        added_user = true;

    return added_user;
}

