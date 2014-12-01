#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <QRegExp>
#include <QLabel>
#include <QDebug>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class CG_validator
{
    public:
        CG_validator(QLabel & feedback);

        bool CheckUsernameLength(QString username);
        bool CheckUsernameNotNull(QString username);
        bool CheckUsernameValidCharacters(QString username);
        bool CheckUsernameInvalidPeriods(QString username);
        bool CheckUsernameForWebsite(QString username);
        bool CheckUsernameForInvalidSpaces(QString username);
        bool CheckValidUsername(QString username);
        bool CheckUniqueUsername(QString username);

        bool CheckPasswordLength(QString password);
        bool CheckRequiredPasswordCharacters(QString password);
        bool CheckValidPassword(QString password);

        bool CheckValidEmailAddress(QString email);

    private:
        QLabel * lbl_feedback;
};

#endif
