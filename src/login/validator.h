#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <QRegExp>
#include <QLabel>
#include <QDebug>

class Validator
{
    public:
        Validator(QLabel & feedback);

        bool CheckLength(QString username);
        bool CheckNotNull(QString username);
        bool CheckValidCharacters(QString username);
        bool CheckInvalidPeriods(QString username);
        bool CheckForWebsite(QString username);
        bool CheckForInvalidSpaces(QString username);
        bool validUsername(QString username);

    private:
        QLabel * lbl_feedback;
};

#endif
