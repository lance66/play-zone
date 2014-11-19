#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class SplashScreen : public QWidget
{
    Q_OBJECT

    public:
        explicit SplashScreen(QWidget *parent = 0);
        explicit SplashScreen(QString, QWidget *parent = 0);

    private:
        QLabel lbl_welcome;
        QGridLayout gl_splashScreen;

};

#endif // SPLASHSCREEN_H
