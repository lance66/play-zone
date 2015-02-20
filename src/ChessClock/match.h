#ifndef MATCH_H
#define MATCH_H

#include <QObject>

enum
{
    WHITE = 0,
    BLACK = 1
};

class Match : public QObject
{
    Q_OBJECT

public:
    //Constructors
    Match();
    ~Match();

    //Mutators
    bool getTurn();

public slots:
    void toggleTurn();

private:
    bool turn;

};

#endif // MATCH_H
