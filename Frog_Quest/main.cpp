#include "mainwindow.h"
//#include "level_1.h"
#include "timer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //level_1 lvl1;
    //lvl1.show();

    //Timer timer;
    //timer.show();

    return a.exec();
}
