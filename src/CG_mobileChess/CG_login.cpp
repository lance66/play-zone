#include "CG_login.h"
#include <QCryptographicHash>  // Needed for encrypting in SHA256

CG_login::CG_login(QWidget * parent) :
    QWidget(parent), gb_login(""), //lbl_username(), lbl_password(),
    btn_login("Login"), btn_register("Register")
{   
    //Connect to database
    db_login = QSqlDatabase::addDatabase("QSQLITE");

    //For deployment use the line below rather than the one above
    db_login.setDatabaseName(QDir::currentPath() + "/chessgames.db");

    //Hide the password entry
    le_password.setEchoMode(QLineEdit::Password);

    gb_login.setStyleSheet("background: #448ed3");
    btn_login.setStyleSheet("background: #b6ee65");
    btn_register.setStyleSheet("background: #b6ee65");
    le_username.setStyleSheet("background: #FFFFFF");
    le_password.setStyleSheet("background: #FFFFFF");
    le_email.setStyleSheet("background: #FFFFFF;");

    //Add all the controls to the login layout
    //gl_login.addWidget(&lbl_username, 0, 0);
    gl_login.addWidget(&le_username, 0, 0);

    //gl_login.addWidget(&lbl_password, 1, 0);
    gl_login.addWidget(&le_password, 1, 0);

    //gl_login.addWidget(&lbl_email, 2, 0);
    gl_login.addWidget(&le_email, 2, 0);

    //lbl_email.hide();
    le_email.hide();

    le_username.setPlaceholderText("Chessgames username");
    le_password.setPlaceholderText("Chessgames password");

    gl_login.addWidget(&btn_login, 3, 0, 1, 2);
    gl_login.addWidget(&btn_register, 4, 0, 1, 2);
    gl_login.addWidget(&lbl_isOpen, 5, 0, 1, 2, Qt::AlignCenter);

    ss_splashScreen = new CG_splashScreen;
    gl_login.addWidget(ss_splashScreen, 6, 0);
    ss_splashScreen->hide();

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

CG_login::~CG_login()
{
    delete ss_splashScreen;
}

void CG_login::on_btn_login_clicked()
{
    QString username, password;
    username = le_username.text();

    // Calls the encryption method
    EncryptPassword( password );

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
           //gb_login.hide();

           //Create splash screen
           //ss_splashScreen->setText(le_username.text());
           //ss_splashScreen->show();
        }
        if(count > 1)
            lbl_isOpen.setText("Duplicate username and password.");
        if(count < 1)
            lbl_isOpen.setText("username and password is not correct");
    }

    db_login.close();
}

void CG_login::on_btn_register_clicked()
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
            //lbl_email.show();
            le_email.setPlaceholderText("Enter email");
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

void CG_login::addUser()
{
    QString username, password, email;
    username = le_username.text();
    email = le_email.text();

    if(!db_login.open())
        lbl_isOpen.setText("Failed to connect to the database");

    // Calls encryption password
    EncryptPassword( password );

    QSqlQuery qry( db_login );
    qry.prepare( "INSERT INTO CG_user (Username, Passwd, Email) VALUES(?, ?, ?)" );
    qry.addBindValue(username);
    qry.addBindValue(password);
    qry.addBindValue(email);

    if(qry.exec())
        lbl_isOpen.setText("Successfully created user.");

    db_login.close();
}

void CG_login::resizeEvent(QResizeEvent * event)
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

void CG_login::setUsernameValidator()
{
    CG_validator vld_username(lbl_isOpen);

    if (vld_username.CheckValidUsername(le_username.text()))
        le_username.setStyleSheet("background: #77FF77");
    else
        le_username.setStyleSheet("background: #FF7777");

    update();
}

void CG_login::EncryptPassword( QString & password )
{
    // Takes the text in the le_password and converts it to Utf8, so it can be placed in a type of 'const char *' next
    QByteArray passwordInBytes = le_password.text().toUtf8();

    // casting the data in passwordInBytes (currently in the form of 'Utf8' to a type of 'const char *'
    const char * convertedPasswordToVerify = passwordInBytes.constData();

            /* Instantiating an object that will create the hashing key for the password. Takes an argument specifying
             * the encryption type you would like be executed on the string */
    QCryptographicHash sha256PasswordEncryptionGenerator( QCryptographicHash::Sha256 );

    // Adding the data to password encryption generator
    sha256PasswordEncryptionGenerator.addData( convertedPasswordToVerify );

    // Converting the password to the hash key using the result method and placing it in password.
    password = (QString)sha256PasswordEncryptionGenerator.result();
}
