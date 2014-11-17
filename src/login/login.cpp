#include "login.h"

Login::Login(QWidget * parent) :
    QWidget(parent), gb_login("Login"), lbl_username("Username"), lbl_password("Password"),
    lbl_email("Email"), btn_login("Login"), btn_register("Register")
{
    //Connect to database
    db_login = QSqlDatabase::addDatabase("QSQLITE");

    //Need to change this line to find the chessgames.db in your own path
    //Should be in the login folder, but can't use a relative path in the
    //database name.
    db_login.setDatabaseName("C:/Users/Jake/Desktop/JP/Play-Zone/play-zone/src/login/chessgames.db");

    //For deployment use the line below rather than the one above
    //db_login.setDatabaseName(QDir::currentPath() + "/chessgames.db");

    //Hide the password entry
    le_password.setEchoMode(QLineEdit::Password);

    gb_login.setStyleSheet("background: white");
    btn_login.setStyleSheet("background: grey");
    btn_register.setStyleSheet("background: grey");

    //Add all the controls to the login layout
    gl_login.addWidget(&lbl_username, 0, 0);
    gl_login.addWidget(&le_username, 0, 1);

    gl_login.addWidget(&lbl_password, 1, 0);
    gl_login.addWidget(&le_password, 1, 1);

    gl_login.addWidget(&lbl_email, 2, 0);
    gl_login.addWidget(&le_email, 2, 1);

    lbl_email.hide();
    le_email.hide();

    gl_login.addWidget(&btn_login, 3, 0, 1, 2);
    gl_login.addWidget(&btn_register, 4, 0, 1, 2);
    gl_login.addWidget(&lbl_isOpen, 5, 0, 1, 2, Qt::AlignCenter);

    //Set the group box to the login layout
    gb_login.setLayout(&gl_login);

    //Add the login group box to the layout of the widget
    gl_widget.addWidget(&gb_login, 0, 0, 1, -1);

    //Set the widget to the layout
    setLayout(&gl_widget);

    //Connect Login button to the appropriate slot
    connect(&btn_login, SIGNAL(released()), this, SLOT(on_btn_login_clicked()));

    //Connect Register button to the appropriate slot
    connect(&btn_register, SIGNAL(released()), this, SLOT(on_btn_register_clicked()));

    //Connect username validation color to username when text is changed
    connect(&le_username, SIGNAL(textChanged(QString)), this, SLOT(setUsernameValidator()));
}

void Login::on_btn_login_clicked()
{
    QString username, password;
    username = le_username.text();
    password = le_password.text();

    if(!db_login.open())
        lbl_isOpen.setText("Failed to connect to the database");

    QSqlQuery qry( db_login );
    qry.prepare( "SELECT * FROM CG_user WHERE Username= ? AND Passwd= ? COLLATE NOCASE" );
    qry.addBindValue(username);
    qry.addBindValue(password);

    if(qry.exec())
    {
        int count = 0;

        for (; qry.next(); count++);

        if(count == 1)
        {
            lbl_isOpen.setText("username and password is correct");

            //Hide the login screen
            //this->hide();

            //Create splash screen
           //SplashScreen splashScreen;
           //splashScreen.setModal(true);
           //splashScreen.exec();
        }
        if(count > 1)
            lbl_isOpen.setText("Duplicate username and password.");
        if(count < 1)
            lbl_isOpen.setText("username and password is not correct");
    }

    db_login.close();
}

void Login::on_btn_register_clicked()
{
    if(!db_login.open())
        lbl_isOpen.setText("Failed to connect to the database");

    QSqlQuery qry( db_login );
    qry.prepare( "SELECT * FROM CG_user WHERE Username= ? COLLATE NOCASE" );
    qry.addBindValue(le_username.text());

    if(qry.exec())
    {
        int count = 0;

        for (; qry.next(); count++);

        if (count == 0)
        {
            lbl_email.show();
            le_email.show();
            connect(&btn_register, SIGNAL(released()), this, SLOT(addUser()));
        }
        else
        {
            le_username.setStyleSheet("background: #FF7777");
            lbl_isOpen.setText("User already exists.");
        }
    }

    db_login.close();
}

void Login::addUser()
{
    QString username, password, email;
    username = le_username.text();
    password = le_password.text();
    email = le_email.text();

    if(!db_login.open())
        lbl_isOpen.setText("Failed to connect to the database");

    QSqlQuery qry( db_login );
    qry.prepare( "INSERT INTO CG_user (Username, Passwd, Email) VALUES(?, ?, ?)" );
    qry.addBindValue(username);
    qry.addBindValue(password);
    qry.addBindValue(email);

    if(qry.exec())
        lbl_isOpen.setText("Successfully created user.");

    db_login.close();
}

void Login::resizeEvent(QResizeEvent * event)
{
    //Resize depending on portrait orientation vs landscape orientation
    if (width() > height())
    {
        gb_login.setMaximumWidth(width() / 2);
        gb_login.setMaximumHeight(height());
    }
    else
    {
        gb_login.setMaximumWidth(width());
        gb_login.setMaximumHeight(height() / 2);
    }
}

void Login::setUsernameValidator()
{
    Validator vld_username(lbl_isOpen);

    if (vld_username.validUsername(le_username.text()))
        le_username.setStyleSheet("background: #77FF77");
    else
        le_username.setStyleSheet("background: #FF7777");

    update();
}
