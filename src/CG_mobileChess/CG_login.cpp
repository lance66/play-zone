#include "CG_login.h"

/**************************************************************
*	  Purpose:  Constructor.  Initializes widget, group box,
*               buttons and pixel map.
*
*     Entry:  User has opened the app.
*
*     Exit:  Data members are initialized and stylesheets are
*            set, widgets are grouped appropriately and signals
*            are connected to slots.
****************************************************************/

CG_login::CG_login(CG_user * user, QWidget * parent) :
    QWidget(parent), cg_validator(lbl_isOpen), gb_login(""), btn_login("Login"),
    btn_register("Register"), pm_logo("cg_logo_hires_app.png")
{   
    //Pass the reference to the CG_user
    cg_usr = user;

    //Hide the password entry
    le_password.setEchoMode(QLineEdit::Password);

    gb_login.setStyleSheet("background: #448ed3; border-style: outset; border-radius: 10px; border-color: #448ed3; min-width: 10em; padding: 6px;");
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

    //Connect password validation color to password when text is changed
    connect(&le_password, SIGNAL(textChanged(QString)), this, SLOT(setPasswordValidator()));

    //Connect email validation color to email when text is changed
    connect(&le_email, SIGNAL(textChanged(QString)), this, SLOT(setEmailValidator()));
}

/**************************************************************
*	  Purpose:  Destructor.  Deletes CG_user.
*
*     Entry:  Close login window button has been pressed.
*
*     Exit:  Login screen is exited.
****************************************************************/

CG_login::~CG_login()
{

}

/**************************************************************
*	  Purpose:  To check whether the user entered a valid
*               username and password.
*
*     Entry:  User has clicked the login button
*
*     Exit:  User is notified whether he has been sucessfully
*            logged in or not.
****************************************************************/

void CG_login::on_btn_login_clicked()
{
    //If username and password is not correct, display
    if (!cg_usr->LogIn(le_username.text(), le_password.text()))
        lbl_isOpen.setText("Username or password is incorrect.");
    else
        //If username and password is correct, display user is logged in
        lbl_isOpen.setText("Successfully logged in. Hello, " + le_username.text() + "!");

    //Ensure email is hidden while logging in
    le_email.hide();
}

/**************************************************************
*	  Purpose:  To check if user already exists in database,
*               and call username validator.
*
*     Entry:  Username and password has been validated at login
*             screen.
*
*     Exit:  User is notified that user has been successfully
*            created.
****************************************************************/

void CG_login::on_btn_register_clicked()
{
    //If user already exists in the database
    if (!cg_usr->GetUser(le_username.text()))
    {
        le_email.setPlaceholderText("Enter email");
        le_email.show();
        connect(&btn_register, SIGNAL(released()), this, SLOT(addUser()));
    }
    else
    {
        //User does not exist, change background to red and notify user
        le_username.setStyleSheet("background: #FF7777");
        lbl_isOpen.setText("User already exists.");
    }

    setUsernameValidator();
}

/**************************************************************
*	  Purpose:  User is added to database.
*
*     Entry:  Username and password has been validated at login
*             screen.
*
*     Exit:  User is notified that user has been successfully
*            created.
****************************************************************/

void CG_login::addUser()
{
    if (setUsernameValidator() && setPasswordValidator() && setEmailValidator())
        if (cg_usr->AddUser(le_username.text(), le_password.text(), le_email.text()))
            lbl_isOpen.setText("Successfully created user.");
}

/**************************************************************
*	  Purpose:  Login screen is optimized to appropriate size.
*
*     Entry:  User opens login screen.
*
*     Exit:  Screen is resized depending on whether the width
*            width is greater than the height.
****************************************************************/

void CG_login::resizeEvent(QResizeEvent * event)
{
    //Resize depending on portrait orientation vs landscape orientation
    if (width() > height())
        gb_login.setMaximumSize(width() / 2, height());
    else
        gb_login.setMaximumSize(width(), height() / 2);
}

/**************************************************************
*	  Purpose:  Ensures the username is valid when registering.
*
*     Entry:  User has clicked register.
*
*     Exit:  Displays whether the username is valid or not.
****************************************************************/

bool CG_login::setUsernameValidator()
{
    bool valid_username = true;

    //If email is visible, that must mean user clicked the register button
    if (le_email.isVisible())
    {
        //If user enters valid username, background = green.  Else, background = red.
        if (cg_validator.CheckValidUsername(le_username.text()))
            le_username.setStyleSheet("background: #77FF77");
        else
        {
            valid_username = false;
            le_username.setStyleSheet("background: #FF7777");
        }
    }

    //Go back to login screen
    update();

    return valid_username;
}

/**************************************************************
*	  Purpose:  Ensures the password is valid when registering.
*
*     Entry:  User has clicked register.
*
*     Exit:  Displays whether the password is valid or not.
****************************************************************/

bool CG_login::setPasswordValidator()
{
    bool valid_password = true;

    //If email is visible, that must mean user clicked the register button
    if (le_email.isVisible())
    {
        //If user enters valid password, background = green. Else, background = red.
        if (cg_validator.CheckValidPassword(le_password.text()))
            le_password.setStyleSheet("background: #77FF77");
        else
        {
            valid_password = false;
            le_password.setStyleSheet("background: #FF7777");
        }
    }

    //Go back to login screen
    update();

    return valid_password;
}

/**************************************************************
*	  Purpose:  Ensures the email is valid when registering.
*
*     Entry:  User has clicked register.
*
*     Exit:  Displays whether the email is valid or not.
****************************************************************/

bool CG_login::setEmailValidator()
{
    bool valid_email = true;

    //If email is visible, that must mean user clicked the register button
    if (le_email.isVisible())
    {
        //If user enters valid email, background = green. Else, background = red.
        if (cg_validator.CheckValidEmailAddress(le_email.text()))
            le_email.setStyleSheet("background: #77FF77");
        else
        {
            valid_email = false;
            le_email.setStyleSheet("background: #FF7777");
        }
    }

    //Go back to login screen
    update();

    return valid_email;
}
