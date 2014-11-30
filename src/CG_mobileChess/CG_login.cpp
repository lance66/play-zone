#include "CG_login.h"

CG_login::CG_login(QWidget * parent) :
    QWidget(parent), gb_login(""), //lbl_username(), lbl_password(),
    btn_login("Login"), btn_register("Register"), pm_logo("cg_logo_hires_app.png"),
    db_chessgames(QDir::currentPath() + "/chessgames.db")
{   
    //Hide the password entry
    le_password.setEchoMode(QLineEdit::Password);

    gb_login.setStyleSheet("background: #448ed3; border-style: outset; border-radius: 10px;border-color: #448ed3;min-width: 10em; padding: 6px;");
    btn_login.setStyleSheet("background: #b6ee65;");
    btn_register.setStyleSheet("background: #b6ee65;");
    le_username.setStyleSheet("background: #FFFFFF;");
    le_password.setStyleSheet("background: #FFFFFF;");
    le_email.setStyleSheet("background: #FFFFFF;");

    lbl_logo.setPixmap(pm_logo);

    //Add all the controls to the login layout
    //gl_login.addWidget(&lbl_username, 0, 0);

    gl_login.addWidget(&lbl_logo, 0, 0);
    gl_login.addWidget(&le_username, 1, 0);

    //gl_login.addWidget(&lbl_password, 1, 0);
    gl_login.addWidget(&le_password, 2, 0);

    //gl_login.addWidget(&lbl_email, 2, 0);
    gl_login.addWidget(&le_email, 3, 0);

    //lbl_email.hide();
    le_email.hide();

    le_username.setPlaceholderText("Chessgames username");
    le_password.setPlaceholderText("Chessgames password");

    gl_login.addWidget(&btn_login, 4, 0, 1, 2);
    gl_login.addWidget(&btn_register, 5, 0, 1, 2);
    gl_login.addWidget(&lbl_isOpen, 6, 0, 1, 2, Qt::AlignCenter);

    ss_splashScreen = new CG_splashScreen;
    gl_login.addWidget(ss_splashScreen, 7, 0);
    ss_splashScreen->hide();

    //Set the group box to the login layout
    gb_login.setLayout(&gl_login);

    //Add the login group box to the layout of the widget
    gl_widget.addWidget(&lbl_logo, 0, 0, 1, 1, Qt::AlignHCenter | Qt::AlignBottom);
    gl_widget.addWidget(&gb_login, 1, 0);

    //Set the widget to the layout
    setLayout(&gl_widget);

    //Connect Login button to the appropriate slot
    connect(&btn_login, SIGNAL(released()), this, SLOT(on_btn_login_clicked()));

    //Connect Register button to the appropriate slot
    connect(&btn_register, SIGNAL(released()), this, SLOT(on_btn_register_clicked()));

    //Connect username validation color to username when text is changed
    connect(&le_username, SIGNAL(textChanged(QString)), this, SLOT(setUsernameValidator()));
}

CG_login::~CG_login()
{
    delete ss_splashScreen;
}

void CG_login::on_btn_login_clicked()
{
    if (!db_chessgames.CorrectUserInfo(le_username.text(), le_password.text()))
        lbl_isOpen.setText("Username or password is incorrect.");
    else
        lbl_isOpen.setText("Successfully logged in.");

    //Ensure email is hidden while logging in
    le_email.hide();
}

void CG_login::on_btn_register_clicked()
{
    if (!db_chessgames.UserExists(le_username.text()))
    {
        le_email.setPlaceholderText("Enter email");
        le_email.show();
        connect(&btn_register, SIGNAL(released()), this, SLOT(addUser()));
    }
    else
    {
        le_username.setStyleSheet("background: #FF7777");
        lbl_isOpen.setText("User already exists.");
    }

    setUsernameValidator();
}

void CG_login::addUser()
{
    if (db_chessgames.AddUser(le_username.text(), le_password.text(), le_email.text()))
        lbl_isOpen.setText("Successfully created user.");
}

void CG_login::resizeEvent(QResizeEvent * event)
{
    //Resize depending on portrait orientation vs landscape orientation
    if (width() > height())
        gb_login.setMaximumSize(width() / 2, height());
    else
        gb_login.setMaximumSize(width(), height() / 2);
}

void CG_login::setUsernameValidator()
{
    CG_validator vld_username(lbl_isOpen);

    if (le_email.isVisible())
    {
        if (vld_username.CheckValidUsername(le_username.text()))
            le_username.setStyleSheet("background: #77FF77");
        else
            le_username.setStyleSheet("background: #FF7777");
    }

    update();
}
