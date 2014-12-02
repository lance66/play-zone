#include "CG_validator.h"

CG_validator::CG_validator(QLabel & feedback) :
    lbl_feedback(&feedback)
{ }

/***************************************************************************
 *      Purpose:  Check to see if the username passed in is of a length
 *                between 2 and 20 characters.  Returns a value describing
 *                whether the QString passed or failed this check.
 *
 *      Entry:  Takes in a QString which represents a username of a user
 *              that is attempting to login or register.
 *
 *      Exit:  Returns a boolean value describing if the username fits the
 *             length of a valid username.  A false value is returned if
 *             the username's length is less than 2 characters long or more
 *             than 20 characters long.
 **************************************************************************/
bool CG_validator::CheckUsernameLength(QString username)
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
 *      Purpose:  Check to see if the username passed in is null.  If a
 *                username is null, the feedback label will be updated to
 *                let the user know they must have a username.
 *
 *      Entry:  Takes in a QString which represents a username of a user
 *              that is attempting to login or register.
 *
 *      Exit:  Returns a boolean value describing if the username is null.
 *             If a username is null, a feedback label will let the user
 *             know the error and return a false value.  Otherwise, if the
 *             username is not null, this will return a true value.
 **************************************************************************/
bool CG_validator::CheckUsernameNotNull(QString username)
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
 *      Purpose:  Check to see if the username passed in only contains
 *                valid characters within it.  Valid characters for a
 *                username include all lowercase and uppercase letters,
 *                numbers, dashes (-), spaces, and periods (.).  If a
 *                username happens to contain a character that isn't
 *                valid, it will return a value describing that.
 *
 *      Entry:  Takes in a QString which represents a username of a user
 *              that is attempting to login or register.
 *
 *      Exit:  Returns a boolean value describing if the username only
 *             contains valid characters.  If an invalid character exists
 *             in the username, it will return a false value and update a
 *             label to inform the user of the issue.
 **************************************************************************/
bool CG_validator::CheckUsernameValidCharacters(QString username)
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
 *      Purpose:  Check to see if the username passed in uses periods (.)
 *                correctly within the string of characters.  A username
 *                cannot start with a period, nor can it end with a period.
 *                If a username matches either of these cases, it will
 *                inform the user of the error.
 *
 *      Entry:  Takes in a QString which represents a username of a user
 *              that is attempting to login or register.
 *
 *      Exit:  Returns a boolean value describing if the username has a
 *             period (.) at the start of end of the username.  This will
 *             return a false value and set a label to inform the username
 *             of the error.
 **************************************************************************/
bool CG_validator::CheckUsernameInvalidPeriods(QString username)
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
 *      Purpose:  Check to see if the username passed in looks like a
 *                website or not.  If it does, it will inform the user
 *                that a username cannot look like a website and return
 *                a false value.
 *
 *      Entry:  Takes in a QString which represents a username of a user
 *              that is attempting to login or register.
 *
 *      Exit:  Returns a boolean value describing if the username looks
 *             like a website.  If it does, it will return false and set a
 *             label to inform the user of the error in their username.
 **************************************************************************/
bool CG_validator::CheckUsernameForWebsite(QString username)
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
 *      Purpose:  Check to see if the username passed in uses spaces
 *                correctly within the string.  A space is used incorrectly
 *                if the username starts or ends with a space, or if there
 *                are at least 2 spaces in a row.  If spaces are used
 *                incorrectly in the username, it will set a label to
 *                inform the user of the error and return false.
 *
 *      Entry:  Takes in a QString which represents a username of a user
 *              that is attempting to login or register.
 *
 *      Exit:  Returns a boolean value describing if the username uses
 *             spaces correctly within the string.  It will set a label to
 *             describe the error if it returns a false value.
 **************************************************************************/
bool CG_validator::CheckUsernameForInvalidSpaces(QString username)
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

/***************************************************************************
 *      Purpose:  Check to see if the username passed in fits all the
 *                requirements for a valid username.  This involves
 *                checking to see if a username is not null, of a specific
 *                length, has only valid characters, doesn't use periods
 *                incorrectly, doesn't look like a website, and that
 *                there are no incorrectly used spaces.
 *
 *      Entry:  Takes in a QString which represents a username of a user
 *              that is attempting to login or register.
 *
 *      Exit:  Returns a boolean value describing if the username fits all
 *             the specifications of a valid username.  This is done by
 *             running it through a gauntlet of validations.
 **************************************************************************/
bool CG_validator::CheckValidUsername(QString username)
{
    bool valid_username = true;

    valid_username = CheckUsernameNotNull(username) &&
                     CheckUsernameLength(username) &&
                     CheckUsernameValidCharacters(username) &&
                     CheckUsernameInvalidPeriods(username) &&
                     CheckUsernameForWebsite(username) &&
                     CheckUsernameForInvalidSpaces(username);

    if (valid_username)
        lbl_feedback->clear();

    return valid_username;
}

/***************************************************************************
 *      Purpose:  Check to see if the password passed in is at least 8
 *                characters long and less than or equal to 64 characters
 *                long.  Returns a boolean that describes if the password
 *                fulfills this requirement, and will set a label if it
 *                does not.
 *
 *      Entry:  Takes in a QString which represents a password of a user
 *              that is attempting to login or register.
 *
 *      Exit:  Returns a boolean value describing if the password is of a
 *             correct length.  Will change the error label if password
 *             does not meet the specifications.
 **************************************************************************/
bool CG_validator::CheckPasswordLength(QString password)
{
    bool valid_length = true;

    if (password.length() < 8) //If a password is less than 8 characters long.
    {
        valid_length = false;
        lbl_feedback->setText("Password is too short.");
    }
    else if (password.length() > 64) //If a password is more than 64 characters long.
    {
        valid_length = false;
        lbl_feedback->setText("Password is too long.");
    }

    return valid_length;
}

/***************************************************************************
 *      Purpose:  Check to see if the password passed in has the following
 *                characters included in it:  at least 1 lowercase letter,
 *                at least 1 uppercase letter, and at least 1 number.
 *                Will update an error label if the password does not meet
 *                these requirements.
 *
 *      Entry:  Takes in a QString which represents a password of a user
 *              that is attempting to login or register.
 *
 *      Exit:  Returns a boolean value describing if the password contains
 *             the required characters.
 **************************************************************************/
bool CG_validator::CheckRequiredPasswordCharacters(QString password)
{
    QRegExp requiredUpperCase("^.*[A-Z].*$"); //Contains an uppercase letter.
    QRegExp requiredLowerCase("^.*[a-z].*$"); //Contains a lowercase letter.
    QRegExp requiredNumber("^.*[0-9].*$"); //Contains a number.

    bool contains_requiredCharacters = true;

    if (!password.contains(requiredUpperCase) || !password.contains(requiredLowerCase)
            || !password.contains(requiredNumber)) //If the password does not contain required valid characters.
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

    if (is_email)
        lbl_feedback->clear();

    return is_email;
}

bool CG_validator::CheckValidPassword(QString password)
{
    bool valid_password = true;

    valid_password = CheckPasswordLength(password) &&
                     CheckRequiredPasswordCharacters(password);

    if (valid_password)
        lbl_feedback->clear();

    return valid_password;
}
