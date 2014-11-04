#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget win;

    QLabel hello("Hello World!");

    QGridLayout layout;

    layout.addWidget(&hello);
    win.setLayout(&layout);

    win.show();

    return app.exec();
}
