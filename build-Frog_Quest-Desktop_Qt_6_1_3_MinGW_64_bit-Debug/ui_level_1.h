/********************************************************************************
** Form generated from reading UI file 'level_1.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/


#ifndef UI_LEVEL_1_H
#define UI_LEVEL_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "my_gl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *Main_Character;
    MyGL *openGLWidget;
    QLabel *Change_text_label;
    QLabel *Ground;
    QLabel *BackGround;
    QLabel *platform_1;
    QLabel *platform_2;
    QLabel *Icon_Fly;
    QLabel *Fly_Counter;
    QLabel *fly_goal_1;
    QLabel *fly_goal_2;
    QLabel *fly_goal_3;
    QLabel *Wall_1;
    QLabel *Wall_2;
    QLabel *Wall_3;
    QLabel *Wall_4;
    QLabel *Wall_5;
    QLabel *Door_1;
    QLabel *spawn_point;
    QLabel *warp_zone;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(4374, 703);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Main_Character = new QLabel(centralwidget);
        Main_Character->setObjectName(QString::fromUtf8("Main_Character"));
        Main_Character->setGeometry(QRect(40, 140, 151, 191));
        openGLWidget = new MyGL(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, -10, 16, 21));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        Change_text_label = new QLabel(centralwidget);
        Change_text_label->setObjectName(QString::fromUtf8("Change_text_label"));
        Change_text_label->setGeometry(QRect(50, 0, 49, 16));
        Ground = new QLabel(centralwidget);
        Ground->setObjectName(QString::fromUtf8("Ground"));
        Ground->setGeometry(QRect(-10, 660, 1441, 61));
        BackGround = new QLabel(centralwidget);
        BackGround->setObjectName(QString::fromUtf8("BackGround"));
        BackGround->setGeometry(QRect(-40, 0, 1411, 731));
        platform_1 = new QLabel(centralwidget);
        platform_1->setObjectName(QString::fromUtf8("platform_1"));
        platform_1->setGeometry(QRect(310, 400, 221, 31));
        platform_2 = new QLabel(centralwidget);
        platform_2->setObjectName(QString::fromUtf8("platform_2"));
        platform_2->setGeometry(QRect(530, 170, 221, 31));
        Icon_Fly = new QLabel(centralwidget);
        Icon_Fly->setObjectName(QString::fromUtf8("Icon_Fly"));
        Icon_Fly->setGeometry(QRect(0, 0, 51, 51));
        Fly_Counter = new QLabel(centralwidget);
        Fly_Counter->setObjectName(QString::fromUtf8("Fly_Counter"));
        Fly_Counter->setGeometry(QRect(50, 0, 61, 41));
        QFont font;
        font.setPointSize(25);
        font.setBold(true);
        font.setItalic(true);
        Fly_Counter->setFont(font);
        fly_goal_1 = new QLabel(centralwidget);
        fly_goal_1->setObjectName(QString::fromUtf8("fly_goal_1"));
        fly_goal_1->setGeometry(QRect(540, 70, 31, 31));
        fly_goal_2 = new QLabel(centralwidget);
        fly_goal_2->setObjectName(QString::fromUtf8("fly_goal_2"));
        fly_goal_2->setGeometry(QRect(760, 510, 31, 31));
        fly_goal_3 = new QLabel(centralwidget);
        fly_goal_3->setObjectName(QString::fromUtf8("fly_goal_3"));
        fly_goal_3->setGeometry(QRect(330, 280, 31, 31));
        Wall_1 = new QLabel(centralwidget);
        Wall_1->setObjectName(QString::fromUtf8("Wall_1"));
        Wall_1->setGeometry(QRect(650, 450, 21, 251));
        Wall_2 = new QLabel(centralwidget);
        Wall_2->setObjectName(QString::fromUtf8("Wall_2"));
        Wall_2->setGeometry(QRect(870, 450, 21, 251));
        Wall_3 = new QLabel(centralwidget);
        Wall_3->setObjectName(QString::fromUtf8("Wall_3"));
        Wall_3->setGeometry(QRect(1150, 40, 21, 251));
        Wall_4 = new QLabel(centralwidget);
        Wall_4->setObjectName(QString::fromUtf8("Wall_4"));
        Wall_4->setGeometry(QRect(1150, -140, 21, 251));
        Wall_5 = new QLabel(centralwidget);
        Wall_5->setObjectName(QString::fromUtf8("Wall_5"));
        Wall_5->setGeometry(QRect(1150, 250, 21, 251));
        Door_1 = new QLabel(centralwidget);
        Door_1->setObjectName(QString::fromUtf8("Door_1"));
        Door_1->setGeometry(QRect(1150, 450, 21, 251));
        spawn_point = new QLabel(centralwidget);
        spawn_point->setObjectName(QString::fromUtf8("spawn_point"));
        spawn_point->setGeometry(QRect(50, 510, 49, 51));
        warp_zone = new QLabel(centralwidget);
        warp_zone->setObjectName(QString::fromUtf8("warp_zone"));
        warp_zone->setGeometry(QRect(1210, 510, 81, 141));
        MainWindow->setCentralWidget(centralwidget);
        BackGround->raise();
        Main_Character->raise();
        openGLWidget->raise();
        Change_text_label->raise();
        Ground->raise();
        platform_1->raise();
        platform_2->raise();
        Icon_Fly->raise();
        Fly_Counter->raise();
        fly_goal_1->raise();
        fly_goal_2->raise();
        fly_goal_3->raise();
        Wall_1->raise();
        Wall_2->raise();
        Wall_3->raise();
        Wall_4->raise();
        Wall_5->raise();
        Door_1->raise();
        spawn_point->raise();
        warp_zone->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Main_Character->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        Change_text_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        Ground->setText(QCoreApplication::translate("MainWindow", "Ground", nullptr));
        BackGround->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        platform_1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        platform_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        Icon_Fly->setText(QCoreApplication::translate("MainWindow", "fly", nullptr));
        Fly_Counter->setText(QCoreApplication::translate("MainWindow", "3/3", nullptr));
        fly_goal_1->setText(QCoreApplication::translate("MainWindow", "fly", nullptr));
        fly_goal_2->setText(QCoreApplication::translate("MainWindow", "fly", nullptr));
        fly_goal_3->setText(QCoreApplication::translate("MainWindow", "fly", nullptr));
        Wall_1->setText(QCoreApplication::translate("MainWindow", "Wall", nullptr));
        Wall_2->setText(QCoreApplication::translate("MainWindow", "Wall", nullptr));
        Wall_3->setText(QCoreApplication::translate("MainWindow", "Wall", nullptr));
        Wall_4->setText(QCoreApplication::translate("MainWindow", "Wall", nullptr));
        Wall_5->setText(QCoreApplication::translate("MainWindow", "Wall", nullptr));
        Door_1->setText(QCoreApplication::translate("MainWindow", "Door", nullptr));
        spawn_point->setText(QCoreApplication::translate("MainWindow", "spawn", nullptr));
        warp_zone->setText(QCoreApplication::translate("MainWindow", "warp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVEL_1_H
