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

        bool CheckLength(QString username);
        bool CheckNotNull(QString username);
        bool CheckValidCharacters(QString username);
        bool CheckInvalidPeriods(QString username);
        bool CheckForWebsite(QString username);
        bool CheckForInvalidSpaces(QString username);
        bool CheckValidUsername(QString username);
        bool CheckUniqueUsername(QString username);

    private:
        QLabel * lbl_feedback;
};

#endif
