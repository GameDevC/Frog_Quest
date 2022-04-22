/********************************************************************************
** Form generated from reading UI file 'Scene1.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENE1_H
#define UI_SCENE1_H

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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(896, 689);
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
        Change_text_label->setGeometry(QRect(50, 0, 801, 41));
        Ground = new QLabel(centralwidget);
        Ground->setObjectName(QString::fromUtf8("Ground"));
        Ground->setGeometry(QRect(0, 390, 901, 61));
        BackGround = new QLabel(centralwidget);
        BackGround->setObjectName(QString::fromUtf8("BackGround"));
        BackGround->setGeometry(QRect(-90, -120, 1281, 871));
        MainWindow->setCentralWidget(centralwidget);
        BackGround->raise();
        Main_Character->raise();
        openGLWidget->raise();
        Change_text_label->raise();
        Ground->raise();

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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENE1_H
