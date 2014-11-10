#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    //Set picture to logo
    //QPixmap pix* ();

    //Connect to database
    db = QSqlDatabase::addDatabase ("QODBC","Chessgames");
    db.setConnectOptions();
    db.setDatabaseName("Driver={SQL Server Native Client 11.0};Server=192.168.0.105;Port=1433;Database=Chessgames;Uid=sa;Pwd=chessgames;");
    if(db.open())
    {
       qDebug() << "Opened!";
       ui->lbl_isOpen->setText("Connected");
    }

    else
    {
       qDebug() << "Closed! " << db.lastError().text();
       ui->lbl_isOpen->setText("Not connected");
    }
}

login::~login()
{
    delete ui;
}

void login::on_pbtn_login_clicked()
{
    QString username, password;
    username = ui->le_username->text();
    password = ui->le_password->text();

    if(!db.isOpen())
    {
        qDebug() << "Failed to connect to database.";
        return;
    }

    QSqlQuery qry( db );

    if(qry.exec("SELECT * FROM CG_userCopy WHERE Username = '"+username+"' AND Passwd= '"+password+"';" ))
    {
        int count = 0;
        while(qry.next())
        {
            count++;
        }

        if(count == 1)
            ui->lbl_isOpen->setText("username and password is correct");
        if(count > 1)
            ui->lbl_isOpen->setText("Duplicate username and password.");
        if(count < 1)
            ui->lbl_isOpen->setText("username and password is not correct");
    }
}
