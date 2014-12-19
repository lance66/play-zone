#ifndef CG_LOBBY_H
#define CG_LOBBY_H

/************************************************************************
* Class: CG_lobby
*
* Constructors:
*	CG_lobby(CG_user * user, QWidget * parent = 0)
*
* Slots:
*   void on_btn_oneMinuteGame_clicked()
*       Allows a user to play a 1 minute game and sends that information
*       to the server.
*   void on_btn_fiveMinuteGame_clicked()
*       Allows a user to play a 5 minute game and sends that information
*       to the server.
*   void on_btn_thirtyMinuteGame_clicked()
*       Allows a user to play a 30 minute game and sends that information
*       to the server.
*
* Methods:
*   virtual void resizeEvent(QResizeEvent * event)
*       Resizes based on whether width is greater than height or vice
*       versa.
*************************************************************************/

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "CG_user.h"

class CG_lobby
{
    Q_OBJECT

    public:
        CG_lobby(CG_user * user, QWidget * parent = 0);

    private slots:
        void on_btn_oneMinuteGame_clicked();
        void on_btn_fiveMinuteGame_clicked();
        void on_btn_thirtyMinuteGame_clicked();
        void on_btn_logout_clicked();

    protected:
        virtual void resizeEvent(QResizeEvent * event);

    private:
        CG_user * cg_usr;

        QPushButton btn_oneMinuteGame;
        QPushButton btn_fiveMinuteGame;
        QPushButton btn_thirtyMinuteGame;
        QPushButton btn_logout;

        QPixmap pm_logo;
        QLabel lbl_logo;

        QGridLayout gl_widget;
};

#endif
