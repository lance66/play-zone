#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class CG_splashScreen : public QWidget
{
    Q_OBJECT

    public:
        CG_splashScreen(QWidget *parent = 0);
        CG_splashScreen(QString, QWidget *parent = 0);
        void setText(QString str);

    private:
        QLabel lbl_welcome;
        QGridLayout gl_splashScreen;

};

#endif
