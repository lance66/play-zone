#include "CG_lobby.h"

/**************************************************************
*	  Purpose:  Constructor.  Initializes widget, layout,
*               buttons and pixel map.
*
*     Entry:  User has logged in.
*
*     Exit:  Data members are initialized and stylesheets are
*            set, widgets are grouped appropriately and signals
*            are connected to slots.
****************************************************************/

CG_lobby::CG_lobby(CG_user * user, QWidget * parent) :
    QWidget(parent), btn_oneMinuteGame("1 minute"),
    btn_fiveMinuteGame("5 minute"), btn_thirtyMinuteGame("30 minute"),
    pm_logo("cg_logo_hires_app.png")
{
    //Pass the reference to the CG_user
    cg_usr = user;

    //Set the styles of the controls
    //gb_login.setStyleSheet("background: #448ed3; border-style: outset; border-radius: 10px; border-color: #448ed3; min-width: 10em; padding: 6px;");
    btn_oneMinuteGame.setStyleSheet("background: #b6ee65;");
    btn_fiveMinuteGame.setStyleSheet("background: #b6ee65;");
    btn_thirtyMinuteGame.setStyleSheet("background: #b6ee65;");
    btn_logout.setStyleSheet("background: #b6ee65;");

    lbl_logo.setPixmap(pm_logo);

    //Add all the controls to the login layout
    gl_widget.addWidget(&lbl_logo, 0, 0);
    gl_widget.addWidget(&btn_oneMinuteGame, 1, 0);
    gl_widget.addWidget(&btn_fiveMinuteGame, 2, 0);
    gl_widget.addWidget(&btn_thirtyMinuteGame, 3, 0);

    //Set the widget to the layout
    setLayout(&gl_widget);

    //Connect the button for a 1 minute game to the appropriate slot
    connect(&btn_oneMinuteGame, SIGNAL(released()), this, SLOT(on_btn_oneMinuteGame_clicked()));

    //Connect the button for a 5 minute game to the appropriate slot
    connect(&btn_fiveMinuteGame, SIGNAL(released()), this, SLOT(on_btn_fiveMinuteGame_clicked()));

    //Connect the button for a 30 minute game to the appropriate slot
    connect(&btn_thirtyMinuteGame, SIGNAL(released()), this, SLOT(on_btn_thirtyMinuteGame_clicked()));

    //Connect the logout button to the appropriate slot
    connect(&btn_logout, SIGNAL(released()), this, SLOT(on_btn_logout_clicked()));
}

/**************************************************************
*	  Purpose:  To allow the user to play a 1 minute game.
*
*     Entry:  User has clicked the button for a 1 minute game.
*
*     Exit:  User will play a 1 minute game.
****************************************************************/

void CG_lobby::on_btn_oneMinuteGame_clicked()
{ }

/**************************************************************
*	  Purpose:  To allow the user to play a 5 minute game.
*
*     Entry:  User has clicked the button for a 5 minute game.
*
*     Exit:  User will play a 5 minute game.
****************************************************************/

void CG_lobby::on_btn_fiveMinuteGame_clicked()
{ }

/**************************************************************
*	  Purpose:  To allow the user to play a 30 minute game.
*
*     Entry:  User has clicked the button for a 30 minute game.
*
*     Exit:  User will play a 30 minute game.
****************************************************************/

void CG_lobby::on_btn_thirtyMinuteGame_clicked()
{ }

/**************************************************************
*	  Purpose:  Logs the user out.
*
*     Entry:  User is in the lobby.
*
*     Exit:  User is logged out of their account.
****************************************************************/

void CG_lobby::on_btn_logout_clicked()
{ }

/**************************************************************
*	  Purpose: Lobby screen is optimized to appropriate size.
*
*     Entry:  User is logged in.
*
*     Exit:  Screen is resized depending on whether the width
*            width is greater than the height.
****************************************************************/

void CG_lobby::resizeEvent(QResizeEvent * event)
{ }
