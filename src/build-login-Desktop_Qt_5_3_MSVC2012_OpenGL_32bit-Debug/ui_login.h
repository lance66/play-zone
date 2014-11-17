/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *centralWidget;
    QLabel *lbl_isOpen;
    QGroupBox *gb_login;
    QPushButton *pbtn_login;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *le_password;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *le_username;
    QLabel *lbl_logo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(919, 295);
        centralWidget = new QWidget(login);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lbl_isOpen = new QLabel(centralWidget);
        lbl_isOpen->setObjectName(QStringLiteral("lbl_isOpen"));
        lbl_isOpen->setGeometry(QRect(20, 190, 871, 16));
        gb_login = new QGroupBox(centralWidget);
        gb_login->setObjectName(QStringLiteral("gb_login"));
        gb_login->setGeometry(QRect(120, 10, 261, 131));
        pbtn_login = new QPushButton(gb_login);
        pbtn_login->setObjectName(QStringLiteral("pbtn_login"));
        pbtn_login->setGeometry(QRect(120, 90, 75, 23));
        layoutWidget = new QWidget(gb_login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 60, 187, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        le_password = new QLineEdit(layoutWidget);
        le_password->setObjectName(QStringLiteral("le_password"));
        le_password->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(le_password);

        layoutWidget1 = new QWidget(gb_login);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 30, 189, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        le_username = new QLineEdit(layoutWidget1);
        le_username->setObjectName(QStringLiteral("le_username"));

        horizontalLayout_2->addWidget(le_username);

        lbl_logo = new QLabel(centralWidget);
        lbl_logo->setObjectName(QStringLiteral("lbl_logo"));
        lbl_logo->setGeometry(QRect(10, 20, 101, 91));
        login->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(login);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 919, 26));
        login->setMenuBar(menuBar);
        mainToolBar = new QToolBar(login);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        login->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(login);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        login->setStatusBar(statusBar);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QApplication::translate("login", "login", 0));
        lbl_isOpen->setText(QApplication::translate("login", "[+]Status", 0));
        gb_login->setTitle(QApplication::translate("login", "login", 0));
        pbtn_login->setText(QApplication::translate("login", "Login", 0));
        label_2->setText(QApplication::translate("login", "Password", 0));
        label->setText(QApplication::translate("login", "Username", 0));
        lbl_logo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
