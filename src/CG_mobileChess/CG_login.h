#ifndef LOGIN_H
#define LOGIN_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDir>
#include "CG_validator.h"
#include "CG_splashScreen.h"

class CG_login : public QWidget
{
    Q_OBJECT

    public:
        CG_login(QWidget * parent = 0);

    private slots:
        void on_btn_login_clicked();
        void on_btn_register_clicked();
        void addUser();

        //This is for the text changed slot of the username
        void setUsernameValidator();

    protected:
        virtual void resizeEvent(QResizeEvent * event);

    private:
        //CG_splashScreen ss_splashScreen;

        QGroupBox gb_login;

        QLabel lbl_username;
        QLineEdit le_username;

        QLabel lbl_password;
        QLineEdit le_password;

        QLabel lbl_email;
        QLineEdit le_email;

        QPushButton btn_login;
        QPushButton btn_register;

        QLabel lbl_isOpen;

        QLabel lbl_logo;

        QGridLayout gl_widget;
        QGridLayout gl_login;

        QSqlDatabase db_login;
};

#endif
