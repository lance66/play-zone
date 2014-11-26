#include "CG_validator.h"

CG_validator::CG_validator(QLabel & feedback) :
    lbl_feedback(&feedback)
{ }

/***************************************************************************
 * Function Name:  CheckLength
 *
 * Purpose:  Check to see if the username passed in is of a length between
 * 2 and 20 characters.  Returns a value describing whether the QString
 * passed or failed this check.
 *
 * Entry:  Takes in a QString which represents a username of a user that is
 * attempting to login or register.
 *
 * Exit:  Returns a boolean value describing if the username fits the
 * length of a valid username.  A false value is returned if the username's
 * length is less than 2 characters long or more than 20 characters long.
 **************************************************************************/
bool CG_validator::CheckLength(QString username)
{
    bool valid_length = true;

    if (username.length() < 2) //If a username is less than 2 characters long.
    {
        valid_length = false;
        lbl_feedback->setText("Username is too short.");
    }
    else if (username.length() > 20) //If a username is more than 20 characters long.
    {
        valid_length = false;
        lbl_feedback->setText("Username is too long.");
    }

    return valid_length;
}

bool CG_validator::CheckNotNull(QString username)
{
    bool not_null = true;

    if (username.isNull())
    {
        not_null = false;
        lbl_feedback->setText("Please enter username.");
    }

    return not_null;
}

bool CG_validator::CheckValidCharacters(QString username)
{
    bool valid_characters = true;

    QRegExp regex("^([a-z]*[A-Z]*[0-9]*\\-*\\.*\\s*)*$"); //Any string with only the characters
                                                          //a-z, A-Z, 0-9, -, (space), and .

    if (!username.contains(regex))
    {
        valid_characters = false;
        lbl_feedback->setText("Username contains invalid characters.");
    }

    return valid_characters;
}

bool CG_validator::CheckInvalidPeriods(QString username)
{
    bool valid_period_placement = true;

    QRegExp FrontPeriodRegex("^\\.+.*$"); //Any string that starts with a period.
    QRegExp BackPeriodRegex("^.*\\.+$");  //Any string that ends with a period.

    if (FrontPeriodRegex.indexIn(username) != -1)
    {
        valid_period_placement = false;
        lbl_feedback->setText("Username can't have a period at the front.");
    }

    if (BackPeriodRegex.indexIn(username) != -1)
    {
        valid_period_placement = false;
        lbl_feedback->setText("Username can't have a period at the back.");
    }

    return valid_period_placement;
}

bool CG_validator::CheckForWebsite(QString username)
{
    bool notAWebsite = true;
    QRegExp WebsiteRegex("^.*\\.+\\b(com|co|uk|org|net)\\b$");

    if (WebsiteRegex.indexIn(username) != -1)
    {
        notAWebsite = false;
        lbl_feedback->setText("Username can't be a website.");
    }

    return notAWebsite;
}

bool CG_validator::CheckForInvalidSpaces(QString username)
{
    bool validSpaces = true;
    QRegExp startWithSpace("^\\s.*$");
    QRegExp endWithSpace("^.*\\s$");
    QRegExp doubleSpaces("^.*\\s\\s.*$");

    if (startWithSpace.indexIn(username) != -1)
    {
        validSpaces = false;
        lbl_feedback->setText("Username can't start with a space.");
    }
    if (endWithSpace.indexIn(username) != -1)
    {
        validSpaces = false;
        lbl_feedback->setText("Username can't end with a space.");
    }
    if (doubleSpaces.indexIn(username) != -1)
    {
        validSpaces = false;
        lbl_feedback->setText("Username can't contain 2 consecutive spaces.");
    }

    return validSpaces;
}

bool CG_validator::CheckValidUsername(QString username)
{
    bool valid_username = true;

    valid_username = CheckNotNull(username) && CheckLength(username) &&
                     CheckValidCharacters(username) && CheckInvalidPeriods(username) &&
                     CheckForWebsite(username) && CheckForInvalidSpaces(username);

    if (valid_username)
        lbl_feedback->clear();

    return valid_username;
}

bool CG_validator::CheckUniqueUsername(QString username)
{
    bool unique_username = true;
    int count = 0;

    //Connect to database
    QSqlDatabase db_logins = QSqlDatabase::addDatabase("QSQLITE");

    //For deployment use the line below rather than the one above
    db_logins.setDatabaseName(QDir::currentPath() + "/chessgames.db");

    if(!db_logins.open())
        lbl_feedback->setText("Failed to connect to the database");

    QSqlQuery qry( db_logins );
    qry.prepare( "SELECT UserID FROM CG_user WHERE Username = ?" );
    qry.addBindValue(username);

    if(qry.exec())
    {
        for(; qry.next(); count++);

        if (count > 0)
        {
            unique_username = false;
            lbl_feedback->setText("That username already exists.");
        }
    }

    db_logins.close();

    return unique_username;
}
