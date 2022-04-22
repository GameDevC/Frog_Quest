#include "mainwindow.h"
#include "timer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //Timer timer;
    //timer.show();

    return a.exec();
}
