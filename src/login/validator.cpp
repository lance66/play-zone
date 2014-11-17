#include "validator.h"

Validator::Validator(QLabel & feedback) :
    lbl_feedback(&feedback)
{ }

bool Validator::CheckLength(QString username)
{
    bool valid_length = true;

    if (username.length() < 2)
    {
        valid_length = false;
        lbl_feedback->setText("Username is too short.");
    }
    else if (username.length() > 20)
    {
        valid_length = false;
        lbl_feedback->setText("Username is too long.");
    }

    return valid_length;
}

bool Validator::CheckNotNull(QString username)
{
    bool not_null = true;

    if (username.isNull())
    {
        not_null = false;
        lbl_feedback->setText("Please enter username.");
    }

    return not_null;
}

bool Validator::CheckValidCharacters(QString username)
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

bool Validator::CheckInvalidPeriods(QString username)
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

bool Validator::CheckForWebsite(QString username)
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

bool Validator::CheckForInvalidSpaces(QString username)
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

bool Validator::validUsername(QString username)
{
    bool valid_username = true;

    valid_username = CheckNotNull(username) && CheckLength(username) &&
                     CheckValidCharacters(username) && CheckInvalidPeriods(username) &&
                     CheckForWebsite(username) && CheckForInvalidSpaces(username);

    if (valid_username)
        lbl_feedback->clear();

    return valid_username;
}
