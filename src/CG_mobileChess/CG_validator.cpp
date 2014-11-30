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

/***************************************************************************
 * Function Name:  CheckNotNull
 *
 * Purpose:  Check to see if the username passed in is null.  If a username
 * is null, the feedback label will be updated to let the user know they
 * must have a username.
 *
 * Entry:  Takes in a QString which represents a username of a user that is
 * attempting to login or register.
 *
 * Exit:  Returns a boolean value describing if the username is null.  If a
 * username is null, a feedback label will let the user know the error and
 * return a false value.  Otherwise, if the username is not null, this will
 * return a true value.
 **************************************************************************/
bool CG_validator::CheckNotNull(QString username)
{
    bool not_null = true;

    if (username.isNull()) //If the username is null.
    {
        not_null = false;
        lbl_feedback->setText("Please enter username.");
    }

    return not_null;
}

/***************************************************************************
 * Function Name:  CheckValidCharacters
 *
 * Purpose:  Check to see if the username passed in only contains valid
 * characters within it.  Valid characters for a username include all
 * lowercase and uppercase letters, numbers, dashes (-), spaces, and
 * periods (.).  If a username happens to contain a character that isn't
 * valid, it will return a value describing that.
 *
 * Entry:  Takes in a QString which represents a username of a user that is
 * attempting to login or register.
 *
 * Exit:  Returns a boolean value describing if the username only contains
 * valid characters.  If an invalid character exists in the username, it
 * will return a false value and update a label to inform the user of the
 * issue.
 **************************************************************************/
bool CG_validator::CheckValidCharacters(QString username)
{
    bool valid_characters = true;

    QRegExp regex("^([a-z]*[A-Z]*[0-9]*\\-*\\.*\\s*)*$"); //Any string with only the characters
                                                          //a-z, A-Z, 0-9, -, (space), and .

    if (!username.contains(regex)) //If the username does not contain only valid characters.
    {
        valid_characters = false;
        lbl_feedback->setText("Username contains invalid characters.");
    }

    return valid_characters;
}

/***************************************************************************
 * Function Name:  CheckInvalidPeriods
 *
 * Purpose:  Check to see if the username passed in uses periods (.)
 * correctly within the string of characters.  A username cannot start with
 * a period, nor can it end with a period.  If a username matches either of
 * these cases, it will inform the user of the error.
 *
 * Entry:  Takes in a QString which represents a username of a user that is
 * attempting to login or register.
 *
 * Exit:  Returns a boolean value describing if the username has a period
 * (.) at the start of end of the username.  This will return a false value
 * and set a label to inform the username of the error.
 **************************************************************************/
bool CG_validator::CheckInvalidPeriods(QString username)
{
    bool valid_period_placement = true;

    QRegExp FrontPeriodRegex("^\\.+.*$"); //Any string that starts with a period.
    QRegExp BackPeriodRegex("^.*\\.+$");  //Any string that ends with a period.

    if (FrontPeriodRegex.indexIn(username) != -1) //If the username starts with a period.
    {
        valid_period_placement = false;
        lbl_feedback->setText("Username can't have a period at the front.");
    }

    if (BackPeriodRegex.indexIn(username) != -1) //If the username ends with a period.
    {
        valid_period_placement = false;
        lbl_feedback->setText("Username can't have a period at the back.");
    }

    return valid_period_placement;
}

/***************************************************************************
 * Function Name:  CheckForWebsite
 *
 * Purpose:  Check to see if the username passed in looks like a website
 * or not.  If it does, it will inform the user that a username cannot look
 * like a website and return a false value.
 *
 * Entry:  Takes in a QString which represents a username of a user that is
 * attempting to login or register.
 *
 * Exit:  Returns a boolean value describing if the username looks like a
 * website.  If it does, it will return false and set a label to inform the
 * user of the error in their username.
 **************************************************************************/
bool CG_validator::CheckForWebsite(QString username)
{
    bool notAWebsite = true;
    QRegExp WebsiteRegex("^.*\\.+\\b(com|co|uk|org|net|edu)\\b$"); //A language describing a variety of email endings.

    if (WebsiteRegex.indexIn(username) != -1) //If the username matches the website regular expression.
    {
        notAWebsite = false;
        lbl_feedback->setText("Username can't be a website.");
    }

    return notAWebsite;
}

/***************************************************************************
 * Function Name:  CheckForInvalidSpaces
 *
 * Purpose:  Check to see if the username passed in uses spaces correctly
 * within the string.  A space is used incorrectly if the username starts or
 * ends with a space, or if there are at least 2 spaces in a row.  If spaces
 * are used incorrectly in the username, it will set a label to inform the
 * user of the error and return false.
 *
 * Entry:  Takes in a QString which represents a username of a user that is
 * attempting to login or register.
 *
 * Exit:  Returns a boolean value describing if the username uses spaces
 * correctly within the string.  It will set a label to describe the error
 * if it returns a false value.
 **************************************************************************/
bool CG_validator::CheckForInvalidSpaces(QString username)
{
    bool validSpaces = true;
    QRegExp startWithSpace("^\\s.*$");
    QRegExp endWithSpace("^.*\\s$");
    QRegExp doubleSpaces("^.*\\s\\s.*$");

    if (startWithSpace.indexIn(username) != -1) //If the username starts with a space.
    {
        validSpaces = false;
        lbl_feedback->setText("Username can't start with a space.");
    }
    if (endWithSpace.indexIn(username) != -1) //If the username ends with a space.
    {
        validSpaces = false;
        lbl_feedback->setText("Username can't end with a space.");
    }
    if (doubleSpaces.indexIn(username) != -1) //If the username has 2+ spaces in a row.
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

//This function will need to be modified for its communication to the database.
//It should have to acquire database info via communication with the database manager.
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

bool CG_validator::CheckPasswordLength(QString password)
{
    bool valid_length = true;

    if (password.length() < 8) //If a username is less than 8 characters long.
    {
        valid_length = false;
        lbl_feedback->setText("Password is too short.");
    }
    else if (password.length() > 256) //If a username is more than 256 characters long.
    {
        valid_length = false;
        lbl_feedback->setText("Password is too long.");
    }

    return valid_length;
}

bool CG_validator::CheckRequiredPasswordCharacters(QString password)
{
    QRegExp requiredCharacters("^([a-z]*[A-Z]*[0-9]*)*$");

    bool contains_requiredCharacters = true;

    if (!password.contains(requiredCharacters)) //If the password does not contain required valid characters.
    {
        contains_requiredCharacters = false;
        lbl_feedback->setText("Password must contain atleast 1 lowercase letter, 1 uppercase letter, and 1 number.");
    }

    return contains_requiredCharacters;
}

bool CG_validator::CheckValidEmailAddress(QString email)
{
    QRegExp valid_email("^.+@.+\\.\\b(com|co|uk|org|net|edu)\\b$");

    bool is_email = true;

    if (valid_email.indexIn(email) == -1) //If the email doesn't match the email regular expression.
    {
        is_email = false;
        lbl_feedback->setText("You must have a valid email address.");
    }

    return is_email;
}

bool CG_validator::CheckValidPassword(QString password)
{
    bool valid_password = true;

    valid_password = CheckPasswordLength(password) &&
                     CheckRequiredPasswordCharacters(password);


    return valid_password;
}
