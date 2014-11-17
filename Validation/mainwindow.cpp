#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::CheckLength(QString username)
{
    bool valid_length = true;

    if (username.length() < 2)
    {
     valid_length = false;
     this->ui->txt_UsernameError->appendPlainText("Your username must be atleast 2 characters long.\n");
    }
    else if (username.length() > 20)
    {
        valid_length = false;
        this->ui->txt_UsernameError->appendPlainText("Your username can be a maximum of 20 characters long.\n");
    }

    return valid_length;
}

bool MainWindow::CheckNotNull(QString username)
{
 bool not_null = true;

 if (username.isNull())
 {
     not_null = false;
     this->ui->txt_UsernameError->appendPlainText("You must enter a username.\n");
 }

 return not_null;
}

bool MainWindow::CheckValidCharacters(QString username)
{
    bool valid_characters = true;
    QRegExp regex("^([a-z]*[A-Z]*[0-9]*\\-*\\.*\\s*)*$"); //Any string with only the characters
                                                          //a-z, A-Z, 0-9, -, (space), and .

   if(!username.contains(regex))
    {
           valid_characters = false;
           this->ui->txt_UsernameError->appendPlainText("Your username contains invalid characters.\n");
    }

    return valid_characters;
}

bool MainWindow::CheckInvalidPeriods(QString username)
{
    bool valid_period_placement = true;
    QRegExp FrontPeriodRegex("^\\.+.*$"); //Any string that starts with a period.
    QRegExp BackPeriodRegex("^.*\\.+$"); //Any string that ends with a period.

    if(FrontPeriodRegex.indexIn(username) != -1)
    {
        valid_period_placement = false;
        this->ui->txt_UsernameError->appendPlainText("Your username cannot begin with a period.\n");
    }

    if(BackPeriodRegex.indexIn(username) != -1)
    {
        valid_period_placement = false;
        this->ui->txt_UsernameError->appendPlainText("Your username cannot end with a period.\n");
    }

    return valid_period_placement;

}

bool MainWindow::CheckForWebsite(QString username)
{
    bool notAWebsite = true;
    QRegExp WebsiteRegex("^.*\\.+\\b(com|co|uk|org|net)\\b$"); //A list of website domain names.

    if(WebsiteRegex.indexIn(username) != -1)
    {
        notAWebsite = false;
        this->ui->txt_UsernameError->appendPlainText("Your username cannot look like a website.\n");
    }

    return notAWebsite;
}

bool MainWindow::CheckForInvalidSpaces(QString username)
{
    bool validSpaces = true;
    QRegExp startWithSpace("^\\s.*$");
    QRegExp endWithSpace("^.*\\s$");
    QRegExp doubleSpaces("^.*\\s\\s.*$");

    if (startWithSpace.indexIn(username) != -1)
    {
        validSpaces = false;
        this->ui->txt_UsernameError->appendPlainText("Your username cannot start with a space.\n");
    }

    if(endWithSpace.indexIn(username) != -1)
    {
        validSpaces = false;
        this->ui->txt_UsernameError->appendPlainText("Your username cannot end with a space.\n");
    }

    if (doubleSpaces.indexIn(username) != -1)
    {
        validSpaces = false;
        this->ui->txt_UsernameError->appendPlainText("Your username cannot have consecutive spaces.\n");
    }

    return validSpaces;
}

void MainWindow::on_Btn_Submit_clicked()
{
    QString username;
    username = ui->txt_Username->text();
    ui->txt_UsernameError->clear();

    Validator(username);
}

bool MainWindow::Validator(QString username)
{
    bool valid_username = true;
    valid_username = CheckNotNull(username) && CheckLength(username) &&
                     CheckValidCharacters(username) && CheckInvalidPeriods(username) &&
                     CheckForWebsite(username) && CheckForInvalidSpaces(username);

    return valid_username;
}

void MainWindow::on_txt_Username_textChanged()
{
    QString username;

    username = ui->txt_Username->text();
    ui->txt_UsernameError->clear();

    if (username.length() == 0)
    {
        ui->txt_Username->setStyleSheet("background: white");
    }
    else if (!Validator(username))
    {
        ui->txt_Username->setStyleSheet("background: red");
    }
    else
    {
        ui->txt_Username->setStyleSheet("background: lightgreen");
    }
}
