
#include "level_1.h"
#include "timer.h"
#include "ui_level_1.h"
#include "my_gl.h"
#include "animationcontroller.h"

//#include "level_1.h"
//#include "ui_level_1.h"

#include <QPixmap>
#include <QLayout>
#include <QProgressBar>
#include <QTimer>
#include <string>
#include <iostream>

level_1::level_1(QWidget *parent) : QMainWindow(parent), ui(new Ui::level_1)
{
    ui->setupUi(this);
}

level_1::~level_1()
{
    delete ui;
}

//virtual level_1::~level_1(){

//}


