#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDir>
#include <QFrame>
#include "CG_validator.h"
#include "CG_splashScreen.h"
#include "CG_dbManager.h"

/************************************************************************
* Class: CG_login
*
* Constructors:
*	CG_login(QWidget * parent = 0)
*
* Slots:
*   void on_btn_login_clicked()
*       Checks to see whether user entered valid username and password.
*       Displays appropriate message on whether user was able to login
*       or not.
*   void on_btn_register_clicked()
*       Checks to see if user already exists in the database.  If user
*       does not exist and they entered a valid username,
*       password and email, then addUser() is called.
*   void addUser()
*       Adds user to the database
*   void setUsernameValidator()
*       Uses regular expressions to see if user is valid or not.
*
* Methods:
*   virtual void resizeEvent(QResizeEvent * event)
*       Resizes based on whether width is greater than height or vice
*       versa.
*************************************************************************/

class CG_login : public QWidget
{
    Q_OBJECT

    public:
        CG_login(QWidget * parent = 0);
        ~CG_login();

    private slots:
        void on_btn_login_clicked();
        void on_btn_register_clicked();
        void addUser();

        //This is for the text changed slot of the username
        void setUsernameValidator();
    protected:
        virtual void resizeEvent(QResizeEvent * event);

    private:
        CG_splashScreen * ss_splashScreen;

        QGroupBox gb_login;

        //QLabel lbl_username;
        QLineEdit le_username;

        //QLabel lbl_password;
        QLineEdit le_password;

        //QLabel lbl_email;
        QLineEdit le_email;

        QPushButton btn_login;
        QPushButton btn_register;

        QLabel lbl_isOpen;

        QPixmap pm_logo;
        QLabel lbl_logo;

        QGridLayout gl_widget;
        QGridLayout gl_login;

        CG_dbManager db_chessgames;

};

#endif
