#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QWidget>
#include <vector>
#include <iostream>

//#include "level_1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //level_1 lvl1;

    void keyPressEvent(QKeyEvent *);
    void timeLoop(int incrementingTime);
    void updateProgress();
    void Gravity();
    void Set_Ground();
    bool Check_Ground();
    bool Check_Platform();
    void Set_BackGround();
    void Horizontal_Drag();
    void Gravity_Pull();
    void Push_Out_Of_Ground();
    void Generate_Platforms();
    void Generate_Blocked_Zones();
    void Generate_Screen_UI();
    void Update_Fly_Count();
    void Count_All_Flies();
    void animationCaller();
    void Detect_Fly();
    void Generate_Walls();
    void Generate_Blocked_Walls();
    bool Check_Wall_Positive();
    bool Check_Wall_Negative();
    void Generate_Doors();
    void Generate_Blocked_Doors();
    bool Check_Door_Positive();
    bool Check_Door_Negative();
    void Door_Lock();
    void toSpawnPoint();
    void Generate_Warp();
    void Detect_Portal();
    void LevelSetUp();
    void setUpStageLabels();
    void deleteAllLabels();
    void FindMainCharacter();
    void FindSpecificElements();
    void clearAllArrays();
    void whenWarped();
    void TrackCharacter();

    float TIMESPACER = 1000;
    float xSpeed = 0;
    float baseSpeed = 15;
    float groundMultiplier = 2.8;
    int platformXModifier = 75;
    int platformYModifierU = 75;
    int wallXModifier = 0;
    int wallYModifier = 0;
    int platformYHolder = 0;
    int numberOfFlies = 0;
    int fliesCollected = 0;
    int flyCurrentCount = 1;
    int stageCounter = 1;


    float jumpSpeed = 50;
    float gravitySpeed = 0;

    bool inAir = false;
    bool onPlatform = false;
    bool blockedMovingXp = false;
    bool blockedMovingXn = false;
    bool blockedMovingXp2 = false;
    bool blockedMovingXn2 = false;



    //float incrementingTime = 0;


};

#endif // MAINWINDOW_H
