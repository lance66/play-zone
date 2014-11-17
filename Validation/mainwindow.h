#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Btn_Submit_clicked();
    bool CheckLength(QString username);
    bool CheckNotNull(QString username);
    bool CheckValidCharacters(QString username);
    bool CheckInvalidPeriods(QString username);
    bool CheckForWebsite(QString username);
    bool CheckForInvalidSpaces(QString username);
    bool Validator(QString username);

    void on_txt_Username_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
