#include <QCoreApplication>
#include <QDebug>
#include <iostream>

// Ra = your rating
// Rb = opponent's rating
// Sa = result (i.e. 1 = win, .5 = draw, 0 = loss)

int calculateELO(int Ra, int Rb, double Sa)
{
    //Elo from player 1 and player 2 and result of the match

    // Set K-Factor (i.e. this number determines how big the rating changes)
    int K = 15;

    // Calculate Elo from wikipedia formula
    double Ea = 1/(1 + pow(10, ( (Rb - Ra)/400 ) ));

    // Return new Elo (also on wikipedia)
    return (Ra + (int)(K*(Sa - Ea)));
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "My ELO: " << 1925;
    qDebug() << "My new ELO after I beat someone 2620: " << calculateELO(1925, 2620, 1);
    qDebug() << "My new ELO after I drew someone 2620: " << calculateELO(1925, 2620, .5);
    qDebug() << "My new ELO after I lost to someone 2620: " << calculateELO(1925, 2620, 0);

    return a.exec();
}
