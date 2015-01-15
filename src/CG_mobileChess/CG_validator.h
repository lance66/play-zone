#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <QRegExp>
#include <QLabel>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


/************************************************************************
* Class: CG_validator
*
* Constructors:
*	CG_validator(QLabel & feedback)
*
* Methods:
*   bool CheckUsernameLength(QString username)
*       Returns a boolean to show if username matches the correct length.
*   bool CheckUsernameNotNull(QString username)
*       Returns a boolean to show if username is not null.
*   bool CheckUsernameValidCharacters(QString username)
*       Returns a boolean showing if username contains only valid characters.
*   bool CheckUsernameInvalidPeriods(QString username)
*       Returns a boolean showing if username uses periods correctly.
*   bool CheckUsernameForWebsite(QString username)
*       Returns a boolean showing if username looks like a website.
*   bool CheckUsernameForInvalidSpaces(QString username)
*       Returns a boolean showing if username uses spaces incorrectly.
*   bool CheckValidUsername(QString username)
*       Returns a boolean that is the result of running the username
*       through the gauntlet of username validations.
*   bool CheckPasswordLength(QString password)
*       Returns a boolean showing if a password is of a correct length.
*   bool CheckRequiredPasswordCharacters(QString password)
*       Returns a boolean showing if a password contains required characters.
*   bool CheckValidPassword(QString password)
*       Returns a boolean that is the result of running the password
*       through the gauntlet of password validations.
*   bool CheckValidEmailAddress(QString email)
*       Returns a boolean showing if an email address is valid.
*
* Data Members:
*   QLabel * lbl_feedback
*       This is a pointer to a label that will report feedback on
*       errors when validating usernames, passwords, and email addresses.
*************************************************************************/

class CG_validator : public QObject
{
    Q_OBJECT

    public:
        CG_validator(QLabel & feedback);

    public slots:
        bool CheckUsernameLength(QString username);
        bool CheckUsernameNotNull(QString username);
        bool CheckUsernameValidCharacters(QString username);
        bool CheckUsernameInvalidPeriods(QString username);
        bool CheckUsernameForWebsite(QString username);
        bool CheckUsernameForInvalidSpaces(QString username);
        bool checkValidUsername(QString username);

        bool CheckPasswordLength(QString password);
        bool CheckRequiredPasswordCharacters(QString password);
        bool checkValidPassword(QString password);

        bool checkValidEmailAddress(QString email);

        QString getFeedback() { return (*lbl_feedback).text(); }

    private:
        QLabel * lbl_feedback;
};

#endif
