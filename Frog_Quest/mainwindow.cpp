#include "mainwindow.h"
#include "timer.h"
#include "ui_mainwindow.h"
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
#include <QHBoxLayout>
#include <QLabel>
#include "LevelStorage.cpp"
//#include <QMediaPlayer>

#include <QtGui>
#include <QtWidgets>

using namespace std;

//top left, position 0 | top right, position 1 | bottom left, position 2 | bottom right, position 3
vector<vector<int>> BlockedZone;
QList<QLabel*> flyHolder;
QList<QLabel*> trobbelHolder;
QList<QLabel*> spikeyHolder;
QList<QLabel*> ratHatterHolder;
vector<vector<int>> WallBlockedZone;
vector<vector<int>> DoorBlockedZone;
vector<vector<int>> TestingBlockZone; //delete later
vector<vector<int>> TestingBlockZone2; //delete later
//vector<vector<int>> FlyHolderZone;
QLabel *MainCharPointer;
QLabel *BackgroundPointer;
QLabel *GroundPointer;
QLabel *WarpZonePointer;
QLabel *SpawnZonePointer;
QLabel *FlyCounterPointer;
QLabel *IconFlyPointer;
QLabel *HealthBarPointer;

//stageCounter

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //QMainWindow level1;
    ui->setupUi(this);
    //lvl1.setParent(this);

    //Sets window preferences
    setWindowTitle("Frog Quest");
    setFixedWidth(1280);
    setFixedHeight(720);



    //makes time
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateProgress);
    timer->start(50);

    QTimer *animtimer = new QTimer(this);
    connect(animtimer, &QTimer::timeout, this, &MainWindow::animationCaller);
    animtimer->start(150);

    QTimer *playerTimer = new QTimer(this);
    connect(playerTimer, &QTimer::timeout, this, &MainWindow::playerAnimator);
    playerTimer->start(250);




    //test label
    //ui->Change_text_label->setText("");
    LevelSetUp();



    //hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LevelSetUp(){


    //spawn player
    FindSpecificElements();
    FindMainCharacter();
    toSpawnPoint();
    SpawnZonePointer->setText("");



    //makes Main Character
    QString filename = "../Frog_Quest/Assets/Characters/Main/MC_Idel1.png";

    string printer = filename.toStdString();
    cout << printer;

    if (QString::compare(filename, QString()) != 0){
        QImage image;
        bool valid = image.load(filename);
        image = image.scaledToWidth(MainCharPointer->width(), Qt::SmoothTransformation);

        if(valid){
            MainCharPointer->setPixmap(QPixmap::fromImage(image));
        } else {
            //error handling
        }
    }

    Set_Ground();
    Set_BackGround();
    Generate_Semi_Background();
    Generate_Platforms();
    Generate_Blocked_Zones();
    Generate_Screen_UI();
    Count_All_Flies();
    Generate_Enemies();
    updateHealthBar();

    Generate_Walls();
    Generate_Blocked_Walls();

    Generate_Doors();
    Generate_Blocked_Doors();

    Generate_Warp();
}

void MainWindow::setUpStageLabels(){
    //make label and its name
    //move to labels position
    //set width and height
    vector<Asset*> currentLevelAssets = levelSelect(stageCounter);

    for(int i = 0; i<currentLevelAssets.size(); i++){
        QLabel *label = new QLabel(this);
        label->setGeometry(currentLevelAssets[i]->x,currentLevelAssets[i]->y,currentLevelAssets[i]->width,currentLevelAssets[i]->height);
        label->setObjectName(QString::fromStdString(currentLevelAssets[i]->name));
        label->show();
    }

}

void MainWindow::deleteAllLabels(){
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();
    //for loop that checks all labels in size.
    for(int i = 0; i < allLabels.size(); i++){

        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        string deleteTabsLevel = "Level_" + to_string(stageCounter-1);
        if ((nameOfLabel.toStdString()).find(deleteTabsLevel) != std::string::npos) {
            if ((nameOfLabel.toStdString()).find("fly_goal_") != std::string::npos) {
                //allLabels[i]->deleteLater();
                //allLabels[i]->move(allLabels[i]->x(), allLabels[i]->y() + 1000);
            }else if((nameOfLabel.toStdString()).find("trobbel_") != std::string::npos){
                //rofl
                allLabels[i]->move(allLabels[i]->x(), allLabels[i]->y() + 1000);
            }else if((nameOfLabel.toStdString()).find("spikey_") != std::string::npos){
                //rofl
                allLabels[i]->move(allLabels[i]->x(), allLabels[i]->y() + 1000);
            }else if((nameOfLabel.toStdString()).find("rat_hatter_") != std::string::npos){
                //rofl
                allLabels[i]->move(allLabels[i]->x(), allLabels[i]->y() + 1000);
            }else{
                allLabels[i]->deleteLater();
            }
        }
        //get the name of the current label
        //QString nameOfLabel = allLabels[i]->objectName();

    }
}

void MainWindow::clearAllArrays(){

    //flyHolder.clear();
    //flyHolder.removeAll("Level_1");
    BlockedZone.clear();
    WallBlockedZone.clear();
    DoorBlockedZone.clear();
    BlockedZone.empty();
    WallBlockedZone.empty();
    DoorBlockedZone.empty();

    //BlockedZone = new vector<vector<int>>;
}

void MainWindow::Pop_Up_Enteties(){
    //probably don't need this anymore
}

void MainWindow::updateProgress()
{
    //WORKS OF GRAVITY
    TrackCharacter();

    bool GravityTF = Check_Ground();
    bool GravityPlatformTF = Check_Platform();
    if(GravityTF == false){
        //Gravity();
    }else if(GravityPlatformTF == false){

    }
    else{
        Gravity();
    }



    //MOVING LEFT AND RIGHT REFINING
    MainCharPointer->move(MainCharPointer->x() + xSpeed,MainCharPointer->y());
    if(xSpeed != 0){
        Horizontal_Drag();
    }
    Push_Out_Of_Ground();
    Update_Fly_Count();

    Detect_Fly();
    Detect_Portal();

    //enemy movement
    MoveTrobbel();
    MoveSpikey();
    MoveRatHatter();

    //enemy collision
    Trobbel_Hit_Player();
    Spikey_Hit_Player();
    Rat_Hatter_Hit_Player();

}

void MainWindow::FindMainCharacter(){
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();
    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();

        if ((nameOfLabel.toStdString()).find("Main_Character") != std::string::npos) {
            MainCharPointer = allLabels[i];

        }
    }
}

void MainWindow::FindSpecificElements(){
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();
    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();

        if ((nameOfLabel.toStdString()).find("BackGround") != std::string::npos) {
            BackgroundPointer = allLabels[i];
        }
        if ((nameOfLabel.toStdString()).find("Ground") != std::string::npos) {
            GroundPointer = allLabels[i];
        }
        if ((nameOfLabel.toStdString()).find("warp_zone") != std::string::npos) {
            WarpZonePointer = allLabels[i];
        }
        if ((nameOfLabel.toStdString()).find("spawn_point") != std::string::npos) {
            SpawnZonePointer = allLabels[i];
        }
        if ((nameOfLabel.toStdString()).find("Icon_Fly") != std::string::npos) {
            IconFlyPointer = allLabels[i];
        }
        if ((nameOfLabel.toStdString()).find("Fly_Counter") != std::string::npos) {
            FlyCounterPointer = allLabels[i];
        }
        if ((nameOfLabel.toStdString()).find("Health_Bar") != std::string::npos) {
            HealthBarPointer = allLabels[i];
        }
    }



}

void MainWindow::playerAnimator(){
    //player animation========================================================================================================================
    //isLeftFacing = false;
    if(isLeftFacing == false){
        if(inAir){
            if(MainCharPointer->y() > MainCharPointer->y() + gravitySpeed){//if character is below the next position on going up
                int MCUpCount = 1;
                QString filename = "../Frog_Quest/Assets/Characters/Main/MC_JumpUp1.png";
                if (QString::compare(filename, QString()) != 0){
                    QImage image;
                    bool valid = image.load(filename);
                    image = image.scaledToWidth(MainCharPointer->width(), Qt::SmoothTransformation);
                    if(valid){
                        MainCharPointer->setPixmap(QPixmap::fromImage(image));
                    } else {
                        //error handling
                    }
                }
            }else if(MainCharPointer->y() <= MainCharPointer->y() + gravitySpeed){//going down
                int MCDownCount = 1;
                QString filename = "../Frog_Quest/Assets/Characters/Main/MC_JumpDown1.png";
                if (QString::compare(filename, QString()) != 0){
                    QImage image;
                    bool valid = image.load(filename);
                    image = image.scaledToWidth(MainCharPointer->width(), Qt::SmoothTransformation);
                    if(valid){
                        MainCharPointer->setPixmap(QPixmap::fromImage(image));
                    } else {
                        //error handling
                    }
                }
            }

        }else{
            if(xSpeed == 0){//if standing still
                int MCIdelCount = 4;
                if(MCIdelCurrentCount > MCIdelCount){
                    MCIdelCurrentCount = 1;
                }
                QString filename = "../Frog_Quest/Assets/Characters/Main/MC_Idel" + QString::fromStdString(to_string(MCIdelCurrentCount)) + ".png";
                MCIdelCurrentCount = MCIdelCurrentCount + 1;
                if (QString::compare(filename, QString()) != 0){
                    QImage image;
                    bool valid = image.load(filename);
                    image = image.scaledToWidth(MainCharPointer->width(), Qt::SmoothTransformation);
                    if(valid){
                        MainCharPointer->setPixmap(QPixmap::fromImage(image));
                    } else {
                        //error handling
                    }
                }

            }else if(xSpeed != 0){
                int MCMovingCount = 4;
                if(MCMovingCurrentCount > MCMovingCount){
                    MCMovingCurrentCount = 1;
                }
                QString filename = "../Frog_Quest/Assets/Characters/Main/MC_Run" + QString::fromStdString(to_string(MCMovingCurrentCount)) + ".png";
                MCMovingCurrentCount = MCMovingCurrentCount + 1;
                if (QString::compare(filename, QString()) != 0){
                    QImage image;
                    bool valid = image.load(filename);
                    image = image.scaledToWidth(MainCharPointer->width(), Qt::SmoothTransformation);
                    if(valid){
                        MainCharPointer->setPixmap(QPixmap::fromImage(image));
                    } else {
                        //error handling
                    }
                }

            }
        }
    }else if(isLeftFacing == true){
        if(inAir){
            if(MainCharPointer->y() > MainCharPointer->y() + gravitySpeed){//if character is below the next position on going up
                int MCUpCount = 1;
                QString filename = "../Frog_Quest/Assets/Characters/Main/MC_JumpUp1Left.png";
                if (QString::compare(filename, QString()) != 0){
                    QImage image;
                    bool valid = image.load(filename);
                    image = image.scaledToWidth(MainCharPointer->width(), Qt::SmoothTransformation);
                    if(valid){
                        MainCharPointer->setPixmap(QPixmap::fromImage(image));
                    } else {
                        //error handling
                    }
                }
            }else if(MainCharPointer->y() <= MainCharPointer->y() + gravitySpeed){//going down
                int MCDownCount = 1;
                QString filename = "../Frog_Quest/Assets/Characters/Main/MC_JumpDown1Left.png";
                if (QString::compare(filename, QString()) != 0){
                    QImage image;
                    bool valid = image.load(filename);
                    image = image.scaledToWidth(MainCharPointer->width(), Qt::SmoothTransformation);
                    if(valid){
                        MainCharPointer->setPixmap(QPixmap::fromImage(image));
                    } else {
                        //error handling
                    }
                }
            }

        }else{
            if(xSpeed == 0){//if standing still
                int MCIdelCount = 4;
                if(MCIdelCurrentCount > MCIdelCount){
                    MCIdelCurrentCount = 1;
                }
                QString filename = "../Frog_Quest/Assets/Characters/Main/MC_Idel" + QString::fromStdString(to_string(MCIdelCurrentCount)) + "Left.png";
                MCIdelCurrentCount = MCIdelCurrentCount + 1;
                if (QString::compare(filename, QString()) != 0){
                    QImage image;
                    bool valid = image.load(filename);
                    image = image.scaledToWidth(MainCharPointer->width(), Qt::SmoothTransformation);
                    if(valid){
                        MainCharPointer->setPixmap(QPixmap::fromImage(image));
                    } else {
                        //error handling
                    }
                }

            }else if(xSpeed != 0){
                int MCMovingCount = 4;
                if(MCMovingCurrentCount > MCMovingCount){
                    MCMovingCurrentCount = 1;
                }
                QString filename = "../Frog_Quest/Assets/Characters/Main/MC_Run" + QString::fromStdString(to_string(MCMovingCurrentCount)) + "Left.png";
                MCMovingCurrentCount = MCMovingCurrentCount + 1;
                if (QString::compare(filename, QString()) != 0){
                    QImage image;
                    bool valid = image.load(filename);
                    image = image.scaledToWidth(MainCharPointer->width(), Qt::SmoothTransformation);
                    if(valid){
                        MainCharPointer->setPixmap(QPixmap::fromImage(image));
                    } else {
                        //error handling
                    }
                }

            }
        }
    }

}

void MainWindow::updateHealthBar(){
    if(Hp == 5){
        QString filename = "../Frog_Quest/Assets/Characters/Main/UI/Heart_Number_" + QString::fromStdString(to_string(Hp)) + ".png";
        if (QString::compare(filename, QString()) != 0){
            QImage image;
            bool valid = image.load(filename);
            image = image.scaledToWidth(HealthBarPointer->width(), Qt::SmoothTransformation);
            if(valid){
                HealthBarPointer->setPixmap(QPixmap::fromImage(image));
            } else {
                //error handling
            }
        }
    }else if(Hp == 4){
        QString filename = "../Frog_Quest/Assets/Characters/Main/UI/Heart_Number_" + QString::fromStdString(to_string(Hp)) + ".png";
        if (QString::compare(filename, QString()) != 0){
            QImage image;
            bool valid = image.load(filename);
            image = image.scaledToWidth(HealthBarPointer->width(), Qt::SmoothTransformation);
            if(valid){
                HealthBarPointer->setPixmap(QPixmap::fromImage(image));
            } else {
                //error handling
            }
        }
    }else if(Hp == 3){
        QString filename = "../Frog_Quest/Assets/Characters/Main/UI/Heart_Number_" + QString::fromStdString(to_string(Hp)) + ".png";
        if (QString::compare(filename, QString()) != 0){
            QImage image;
            bool valid = image.load(filename);
            image = image.scaledToWidth(HealthBarPointer->width(), Qt::SmoothTransformation);
            if(valid){
                HealthBarPointer->setPixmap(QPixmap::fromImage(image));
            } else {
                //error handling
            }
        }
    }else if(Hp == 2){
        QString filename = "../Frog_Quest/Assets/Characters/Main/UI/Heart_Number_" + QString::fromStdString(to_string(Hp)) + ".png";
        if (QString::compare(filename, QString()) != 0){
            QImage image;
            bool valid = image.load(filename);
            image = image.scaledToWidth(HealthBarPointer->width(), Qt::SmoothTransformation);
            if(valid){
                HealthBarPointer->setPixmap(QPixmap::fromImage(image));
            } else {
                //error handling
            }
        }
    }else if(Hp == 1){
        QString filename = "../Frog_Quest/Assets/Characters/Main/UI/Heart_Number_" + QString::fromStdString(to_string(Hp)) + ".png";
        if (QString::compare(filename, QString()) != 0){
            QImage image;
            bool valid = image.load(filename);
            image = image.scaledToWidth(HealthBarPointer->width(), Qt::SmoothTransformation);
            if(valid){
                HealthBarPointer->setPixmap(QPixmap::fromImage(image));
            } else {
                //error handling
            }
        }
    }else if(Hp <= 0){
        toSpawnPoint();
        Hp = 5;
        updateHealthBar();
    }
}

void MainWindow::animationCaller()
{


    //fly animation============================================================================================================================
    int flyCount = 2;

    //QString filename = "../Frog_Quest/Assets/Characters/Fly/Fly_" + QString::fromStdString(to_string(flyCurrentCount)) + ".png";

    if(flyCurrentCount > flyCount){
        flyCurrentCount = 1;
    }
    QString filename = "../Frog_Quest/Assets/Characters/Fly/Fly_" + QString::fromStdString(to_string(flyCurrentCount)) + ".png";
    flyCurrentCount = flyCurrentCount + 1;

    QList<QLabel*> allLabels = this->findChildren<QLabel*>();
    //for loop that checks all labels in size.
    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        if ((nameOfLabel.toStdString()).find("fly_goal_") != std::string::npos) {
            //when in rome i guess (sets up fly skins)
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);
                //image = image.scaledToWidth(currentPlatformWidth, Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }

}


//void MainWindow::timeLoop(int incrementingTime){
    //this is useless
//}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_D) {
        //MainCharPointer->move(MainCharPointer->x() + 15,MainCharPointer->y());
        blockedMovingXp = Check_Wall_Positive();
        blockedMovingXp2 = Check_Door_Positive();
        if(blockedMovingXp == false && blockedMovingXp2 == false){
            xSpeed = baseSpeed;
        }
        isLeftFacing = false;

    }

    if (event->key() == Qt::Key_A) {
         //MainCharPointer->move(MainCharPointer->x() - 15,MainCharPointer->y());
        blockedMovingXn = Check_Wall_Negative();
        blockedMovingXn2 = Check_Door_Negative();
        if(blockedMovingXn == false && blockedMovingXn2 == false){
            xSpeed = -baseSpeed;
        }
        isLeftFacing = true;

    }

    if (event->key() == Qt::Key_W) {
        //MainCharPointer->move(MainCharPointer->x() ,MainCharPointer->y() - 15);
        if(inAir == false){
            inAir = true;
            gravitySpeed = -jumpSpeed;
            Gravity();
        }

        //Gravity();
    }

    if (event->key() == Qt::Key_Space) {
        //MainCharPointer->move(MainCharPointer->x() ,MainCharPointer->y() - 15);
        if(inAir == false){
            inAir = true;
            gravitySpeed = -jumpSpeed;
            Gravity();
        }

        //Gravity();
    }

    if (event->key() == Qt::Key_S) {
        //ui->openGLWidget->effectZero();
        ui->openGLWidget->Crouch(-0.5f);

         //removed becaues you don't really move through the ground
         //MainCharPointer->move(MainCharPointer->x(),MainCharPointer->y() + 15);
    }

}

void MainWindow::Gravity(){
    Gravity_Pull();
    if(MainCharPointer->y() + gravitySpeed <= GroundPointer->y() - (groundMultiplier*GroundPointer->height())){
        MainCharPointer->move(MainCharPointer->x(),MainCharPointer->y() + gravitySpeed);
    }else if(onPlatform == true){
        MainCharPointer->move(MainCharPointer->x(),platformYHolder);
    }else{
        MainCharPointer->move(MainCharPointer->x(),GroundPointer->y() - (groundMultiplier*GroundPointer->height()));
        inAir = false;
    }
}

void MainWindow::Set_BackGround(){
    QString filename = "../Frog_Quest/Assets/Characters/Main/TempBackground.jpg";

    string printer = filename.toStdString();
    cout << printer;

    if (QString::compare(filename, QString()) != 0){
        QImage image;
        bool valid = image.load(filename);
        image = image.scaledToWidth(BackgroundPointer->width(), Qt::SmoothTransformation);

        if(valid){
            BackgroundPointer->setPixmap(QPixmap::fromImage(image));
        } else {
            //error handling
        }
    }
}

void MainWindow::Set_Ground(){
    QString filename = "../Frog_Quest/Assets/Level/Grond/Dirt.jpg";

    string printer = filename.toStdString();
    cout << printer;

    if (QString::compare(filename, QString()) != 0){
        QImage image;
        bool valid = image.load(filename);
        image = image.scaledToWidth(GroundPointer->width(), Qt::SmoothTransformation);

        if(valid){
            GroundPointer->setPixmap(QPixmap::fromImage(image));
        } else {
            //error handling
        }
    }
}

void MainWindow::Generate_Platforms(){
    QString filename = "../Frog_Quest/Assets/Level/Platforms/Wooden_Platform1.png";

    string printer = filename.toStdString();
    cout << printer;

    //sets name of platforms
    string currentPlatform = "platform_1";
    QString labelExtension = "platform_1";
    //QLabel* label = ui->platform_1;
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();

    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        if ((nameOfLabel.toStdString()).find("platform_") != std::string::npos) {
            //replace images on i
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);
                //image = image.scaledToWidth(currentPlatformWidth, Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }
}



void MainWindow::Generate_Walls(){
    QString filename = "../Frog_Quest/Assets/Level/Walls/Wall_1.png";

    string printer = filename.toStdString();
    cout << printer;

    //sets name of platforms
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();

    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        if ((nameOfLabel.toStdString()).find("Wall_") != std::string::npos) {
            //replace images on i
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }
}

void MainWindow::Generate_Doors(){
    QString filename = "../Frog_Quest/Assets/Level/Doors/Door_1.png";

    string printer = filename.toStdString();
    cout << printer;

    //sets name of platforms
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();

    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        if ((nameOfLabel.toStdString()).find("Door_") != std::string::npos) {
            //replace images on i
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }
}

void MainWindow::Generate_Semi_Background(){
    QString filename = "../Frog_Quest/Assets/Level/Interior/Interior_Dirt.png";

    //sets name of platforms
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();

    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        if ((nameOfLabel.toStdString()).find("interior_") != std::string::npos) {
            //replace images on i
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }
}

void MainWindow::Generate_Warp(){
    QString filename = "../Frog_Quest/Assets/Level/Portals/portal_1.png";

    string printer = filename.toStdString();
    cout << printer;

    //sets name of platforms
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();

    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        if ((nameOfLabel.toStdString()).find("warp_zone") != std::string::npos) {
            //replace images on i
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }
}

void MainWindow::Generate_Enemies(){
    //Level_3_trobbel_1
    Generate_Trobbles();
    Generate_Spikeys();
    Generate_Rat_Hatters();
}

void MainWindow::Generate_Trobbles(){
    QString filename = "../Frog_Quest/Assets/Characters/Enemies/Trobbles/TPlaceholder2.png";
    //sets name of platforms
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();

    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        string trobStringTemp = "Level_" + to_string(stageCounter) + "_trobbel";
        if ((nameOfLabel.toStdString()).find(trobStringTemp) != std::string::npos) {
            trobbelHolder.append(allLabels[i]);
            //replace images on i
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }
}

void MainWindow::Generate_Spikeys(){
    QString filename = "../Frog_Quest/Assets/Characters/Enemies/Spikeys/Spikey1.png";
    //sets name of platforms
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();

    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        string spikStringTemp = "Level_" + to_string(stageCounter) + "_spikey";
        if ((nameOfLabel.toStdString()).find(spikStringTemp) != std::string::npos) {
            spikeyHolder.append(allLabels[i]);
            //replace images on i
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }
}

void MainWindow::Generate_Rat_Hatters(){
    QString filename = "../Frog_Quest/Assets/Characters/Enemies/Rat_Hatters/Rat_Hatter1.png";
    //sets name of platforms
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();

    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        string rhStringTemp = "Level_" + to_string(stageCounter) + "_rat_hatter";
        if ((nameOfLabel.toStdString()).find(rhStringTemp) != std::string::npos) {
            ratHatterHolder.append(allLabels[i]);
            //replace images on i
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }
}

void MainWindow::Trobbel_Hit_Player(){
    int MC_Ypos = MainCharPointer->y();//top
    int MC_Ypos2 = MainCharPointer->y()+MainCharPointer->height();//bottom
    int MC_Xpos = MainCharPointer->x();//left
    int MC_Xpos2 = MainCharPointer->x() + MainCharPointer->width();//right
    for(int i = 0; i < trobbelHolder.size(); i++){
        //flyHolder[i]->move(flyHolder[i]->x(), flyHolder[i]->y() + 1);
        if(trobbelHolder[i]->x()+20 > MC_Xpos && trobbelHolder[i]->x()+28 < MC_Xpos2){
            if(trobbelHolder[i]->y() > MC_Ypos && trobbelHolder[i]->y() < MC_Ypos2){
                MainCharPointer->move(MainCharPointer->x(),MainCharPointer->y()-80);
                gravitySpeed = -30;
                Hp = Hp - 1;
                updateHealthBar();
            }
        }
    }
}

void MainWindow::Spikey_Hit_Player(){
    int MC_Ypos = MainCharPointer->y();//top
    int MC_Ypos2 = MainCharPointer->y()+MainCharPointer->height();//bottom
    int MC_Xpos = MainCharPointer->x();//left
    int MC_Xpos2 = MainCharPointer->x() + MainCharPointer->width();//right
    for(int i = 0; i < spikeyHolder.size(); i++){
        //flyHolder[i]->move(flyHolder[i]->x(), flyHolder[i]->y() + 1);
        if(spikeyHolder[i]->x()+20 > MC_Xpos && spikeyHolder[i]->x()+28 < MC_Xpos2){
            if(spikeyHolder[i]->y() > MC_Ypos && spikeyHolder[i]->y() < MC_Ypos2){
                MainCharPointer->move(MainCharPointer->x(),MainCharPointer->y()-80);
                gravitySpeed = -30;
                Hp = Hp - 1;
                updateHealthBar();
            }
        }
    }
}

void MainWindow::Rat_Hatter_Hit_Player(){
    int MC_Ypos = MainCharPointer->y();//top
    int MC_Ypos2 = MainCharPointer->y()+MainCharPointer->height();//bottom
    int MC_Xpos = MainCharPointer->x();//left
    int MC_Xpos2 = MainCharPointer->x() + MainCharPointer->width();//right
    for(int i = 0; i < ratHatterHolder.size(); i++){
        //flyHolder[i]->move(flyHolder[i]->x(), flyHolder[i]->y() + 1);
        if(ratHatterHolder[i]->x()+20 > MC_Xpos && ratHatterHolder[i]->x()+28 < MC_Xpos2){
            if(ratHatterHolder[i]->y() > MC_Ypos && ratHatterHolder[i]->y() < MC_Ypos2){
                MainCharPointer->move(MainCharPointer->x(),MainCharPointer->y()-80);
                gravitySpeed = -30;
                Hp = Hp - 1;
                updateHealthBar();
            }
        }
    }
}

void MainWindow::MoveTrobbel(){
    int trobbelMovementMax = 25;

    if(trobbelMoverCounter == trobbelMovementMax){
        trobbelMoverCounter = 0;
        if(trobbelLeft == true){
            trobbelLeft = false;
        }else{
            trobbelLeft = true;
        }
    }

    trobbelMoverCounter = trobbelMoverCounter + 1;
    for(int i = 0; i < trobbelHolder.size(); i++){
        if(trobbelLeft == true){
            trobbelHolder[i]->move(trobbelHolder[i]->x()-5,trobbelHolder[i]->y());
        }else{
            trobbelHolder[i]->move(trobbelHolder[i]->x()+5,trobbelHolder[i]->y());
        }
    }

}

void MainWindow::MoveSpikey(){

    /*
    int spikeyMovementMax = 25;

    if(spikeyMoverCounter == spikeyMovementMax){
        spikeyMoverCounter = 0;
        if(spikeyLeft == true){
            spikeyLeft = false;
        }else{
            spikeyLeft = true;
        }
    }

    spikeyMoverCounter = spikeyMoverCounter + 1;
    for(int i = 0; i < spikeyHolder.size(); i++){
        if(spikeyLeft == true){
            spikeyHolder[i]->move(spikeyHolder[i]->x()-5,spikeyHolder[i]->y());
        }else{
            spikeyHolder[i]->move(spikeyHolder[i]->x()+5,spikeyHolder[i]->y());
        }
    }

    */
}

void MainWindow::MoveRatHatter(){
    int ratHatterMovementMax = 50;

    if(ratHatterMoverCounter == ratHatterMovementMax){
        ratHatterMoverCounter = 0;
        ratHatterUp = false;
        if(ratHatterLeft == true){
            ratHatterLeft = false;
        }else{
            ratHatterLeft = true;
        }
    }
    if(ratHatterMoverCounter == ratHatterMovementMax/2){
        ratHatterUp = true;
    }
    int RHSlope = ratHatterMoverCounter % 25;
    //RHSlope = 25/ratHatterMoverCounter;

    ratHatterMoverCounter = ratHatterMoverCounter + 1;
    for(int i = 0; i < ratHatterHolder.size(); i++){
        if(ratHatterLeft == true){
            ratHatterHolder[i]->move(ratHatterHolder[i]->x()-5,ratHatterHolder[i]->y());
        }else{
            ratHatterHolder[i]->move(ratHatterHolder[i]->x()+5,ratHatterHolder[i]->y());
        }
        if(ratHatterUp == true){
            ratHatterHolder[i]->move(ratHatterHolder[i]->x(),ratHatterHolder[i]->y()-25/(25-RHSlope));
        }else{
            ratHatterHolder[i]->move(ratHatterHolder[i]->x(),ratHatterHolder[i]->y()+(25/(RHSlope+1)));
        }
    }

}

bool MainWindow::Check_Ground(){
    int MC_Ypos = MainCharPointer->y();
    int Ground_Ypos = GroundPointer->y();
    if(MC_Ypos <= Ground_Ypos - ((groundMultiplier+.1)*GroundPointer->height())){
        return true;
    }
    return false;
}

bool MainWindow::Check_Platform(){
    int MC_Ypos = MainCharPointer->y();//top
    int MC_Ypos2 = MainCharPointer->y()+MainCharPointer->height();//bottom
    int MC_Xpos = MainCharPointer->x();//left
    int MC_Xpos2 = MainCharPointer->x() + MainCharPointer->width();//right
    //if the player is within the two x values of 0 and 1, and is

    //loops through BlockedZone vector
    for(int i = 0; i < BlockedZone.size(); i += 4){
        //checks to see if player will be inbetween the two
        if(MC_Xpos2 < BlockedZone[i+1][0] && MC_Xpos > BlockedZone[i][0]){
            //if on next turn, the platform will be inside player, stop the player above platform
            if(BlockedZone[i][1]-185 > MC_Ypos && BlockedZone[i][1] < MC_Ypos2 + gravitySpeed + 20){
                platformYHolder = BlockedZone[i][1]-200;
                onPlatform = true;
                gravitySpeed = 0;
                //MainCharPointer->move(MainCharPointer->x(),BlockedZone[i][1]-210);
                inAir = false;
                return false;
            }
        }

    }
    onPlatform = false;
    return true;
}

bool MainWindow::Check_Wall_Positive(){

    for(int i = 0; i< WallBlockedZone.size(); i += 4){
        if(MainCharPointer->y() < WallBlockedZone[i][1]-100 && MainCharPointer->y() > WallBlockedZone[i+2][1]-100){
            if(MainCharPointer->x() + 100 < WallBlockedZone[i][0] && MainCharPointer->x() + xSpeed + 130 >= WallBlockedZone[i][0]){
                return true;
            }
        }
    }
    return false;
}


bool MainWindow::Check_Wall_Negative(){

    for(int i = 0; i< WallBlockedZone.size(); i += 4){
        if(MainCharPointer->y() < WallBlockedZone[i][1]-100 && MainCharPointer->y() > WallBlockedZone[i+2][1]-100){
            if(MainCharPointer->x() + 35 > WallBlockedZone[i][0] && MainCharPointer->x() + xSpeed + 0 <= WallBlockedZone[i][0]){
                return true;
            }
        }
    }
    return false;
}

bool MainWindow::Check_Door_Positive(){

    for(int i = 0; i< DoorBlockedZone.size(); i += 4){
        if(MainCharPointer->y() < DoorBlockedZone[i][1]-100 && MainCharPointer->y() > DoorBlockedZone[i+2][1]-100){
            if(MainCharPointer->x() + 100 < DoorBlockedZone[i][0] && MainCharPointer->x() + xSpeed + 130 >= DoorBlockedZone[i][0]){
                return true;
            }
        }
    }
    return false;
}


bool MainWindow::Check_Door_Negative(){

    for(int i = 0; i< DoorBlockedZone.size(); i += 4){
        if(MainCharPointer->y() < DoorBlockedZone[i][1]-100 && MainCharPointer->y() > DoorBlockedZone[i+2][1]-100){
            if(MainCharPointer->x() + 35 > DoorBlockedZone[i][0] && MainCharPointer->x() + xSpeed + 0 <= DoorBlockedZone[i][0]){
                return true;
            }
        }
    }
    return false;
}

void MainWindow::Detect_Fly(){
    int MC_Ypos = MainCharPointer->y();//top
    int MC_Ypos2 = MainCharPointer->y()+MainCharPointer->height();//bottom
    int MC_Xpos = MainCharPointer->x();//left
    int MC_Xpos2 = MainCharPointer->x() + MainCharPointer->width();//right
    for(int i = 0; i < flyHolder.size(); i++){
        //flyHolder[i]->move(flyHolder[i]->x(), flyHolder[i]->y() + 1);
        if(flyHolder[i]->x() > MC_Xpos && flyHolder[i]->x()+8 < MC_Xpos2){
            if(flyHolder[i]->y() > MC_Ypos && flyHolder[i]->y() < MC_Ypos2){
                //MainCharPointer->move(MainCharPointer->x(),MainCharPointer->y() - 15);
                flyHolder[i]->move(flyHolder[i]->x(), flyHolder[i]->y() - 1000);
                fliesCollected = fliesCollected + 1;
                Door_Lock();
            }
        }
    }
}

void MainWindow::Detect_Portal(){
    int MC_Ypos = MainCharPointer->y();//top
    int MC_Ypos2 = MainCharPointer->y()+MainCharPointer->height();//bottom
    int MC_Xpos = MainCharPointer->x();//left
    int MC_Xpos2 = MainCharPointer->x() + MainCharPointer->width();//right
    QLabel* portalHold = WarpZonePointer;
        if(portalHold->x() > MC_Xpos-7 && portalHold->x()+10 < MC_Xpos2){
            if(portalHold->y() > MC_Ypos-7 && portalHold->y()+7 < MC_Ypos2){
                whenWarped();
            }
        }

}

void MainWindow::Door_Lock(){
    if(fliesCollected == numberOfFlies){
        //unlocks the door
        QList<QLabel*> allLabels = this->findChildren<QLabel*>();

        for(int i = 0; i < allLabels.size(); i++){
            //get the name of the current label
            QString nameOfLabel = allLabels[i]->objectName();
            //check if name has Door_ in it
            if ((nameOfLabel.toStdString()).find("Door_") != std::string::npos) {
                allLabels[i]->move(allLabels[i]->x(), allLabels[i]->y() + 1000);
            }
        }

        for(int i = 0; i < DoorBlockedZone.size(); i++){
            //DoorBlockedZone[i][0] = DoorBlockedZone[i][0] + 1000;
            DoorBlockedZone[i][1] = DoorBlockedZone[i][1] + 1000;
        }
    }

}

void MainWindow::Push_Out_Of_Ground(){
    int Ground_Ypos = GroundPointer->y();
    Ground_Ypos = Ground_Ypos - (groundMultiplier*GroundPointer->height());
    if(MainCharPointer->y() > Ground_Ypos){
        float pushOutSpeed = 3;
        MainCharPointer->move(MainCharPointer->x(),MainCharPointer->y() - pushOutSpeed);
    }
}

void MainWindow::Horizontal_Drag(){
    xSpeed = xSpeed * .6;
    if(xSpeed < .5 && xSpeed > -.5){
        xSpeed = 0;
    }

}

void MainWindow::Gravity_Pull(){
    if(gravitySpeed < 100){
        int gravityModifier = abs(gravitySpeed)/8;
        gravitySpeed = gravitySpeed + gravityModifier + 1;
    } else {
        gravitySpeed = 100;
    }

}

void MainWindow::Generate_Blocked_Zones(){
    //insert 4 values at a time. Each of these values will make a square. These squares will make a zone that the player cannot go through.

    //gets all the labels in the scene.
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();
    //for loop that checks all labels in size.
    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        string platformStringTemp = "Level_" + to_string(stageCounter) + "_platform_";
        if ((nameOfLabel.toStdString()).find(platformStringTemp) != std::string::npos) {
            //top left, position 0
            vector<int> pushVectorData = {allLabels[i]->x()-platformXModifier,allLabels[i]->y()+allLabels[i]->height()+10};
            BlockedZone.push_back(pushVectorData);
            //top right, position 1
            pushVectorData = {allLabels[i]->x()+allLabels[i]->width()+platformXModifier,allLabels[i]->y()+allLabels[i]->height()+10};
            BlockedZone.push_back(pushVectorData);
            //bottom right, position 2
            pushVectorData = {allLabels[i]->x()+allLabels[i]->width(),allLabels[i]->y()-(platformYModifierU*2)};
            BlockedZone.push_back(pushVectorData);
            //bottom left, position 3
            pushVectorData = {allLabels[i]->x(),allLabels[i]->y()-(platformYModifierU*2)};
            BlockedZone.push_back(pushVectorData);
        }
    }
}

void MainWindow::Generate_Blocked_Walls(){
    //insert 4 values at a time. Each of these values will make a square. These squares will make a zone that the player cannot go through.

    //gets all the labels in the scene.
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();
    //for loop that checks all labels in size.
    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has Wall_ in it

        string wallStringTemp = "Level_" + to_string(stageCounter) + "_Wall_";
        if ((nameOfLabel.toStdString()).find(wallStringTemp) != std::string::npos) {
            //top left, position 0
            vector<int> pushVectorData = {allLabels[i]->x()-wallXModifier,allLabels[i]->y()+allLabels[i]->height()+10};
            WallBlockedZone.push_back(pushVectorData);
            //top right, position 1
            pushVectorData = {allLabels[i]->x()+allLabels[i]->width()+wallXModifier,allLabels[i]->y()+allLabels[i]->height()+10};
            WallBlockedZone.push_back(pushVectorData);
            //bottom right, position 2
            pushVectorData = {allLabels[i]->x()+allLabels[i]->width(),allLabels[i]->y()-(wallYModifier*2)};
            WallBlockedZone.push_back(pushVectorData);
            //bottom left, position 3
            pushVectorData = {allLabels[i]->x(),allLabels[i]->y()-(wallYModifier*2)};
            WallBlockedZone.push_back(pushVectorData);
        }
    }

}

void MainWindow::Generate_Blocked_Doors(){
    //insert 4 values at a time. Each of these values will make a square. These squares will make a zone that the player cannot go through.
    //strangely enough, you don't need to search for specific door placement, since door isn't technically in the way after because collision is sent into sky

    //gets all the labels in the scene.
    QList<QLabel*> allLabels = this->findChildren<QLabel*>();
    //for loop that checks all labels in size.
    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has Door_ in it
        if ((nameOfLabel.toStdString()).find("Door_") != std::string::npos) {
            //top left, position 0
            vector<int> pushVectorData = {allLabels[i]->x()-wallXModifier,allLabels[i]->y()+allLabels[i]->height()+10};
            DoorBlockedZone.push_back(pushVectorData);
            //top right, position 1
            pushVectorData = {allLabels[i]->x()+allLabels[i]->width()+wallXModifier,allLabels[i]->y()+allLabels[i]->height()+10};//Same dimensions as a wall, so it is using same modifier
            DoorBlockedZone.push_back(pushVectorData);
            //bottom right, position 2
            pushVectorData = {allLabels[i]->x()+allLabels[i]->width(),allLabels[i]->y()-(wallYModifier*2)};
            DoorBlockedZone.push_back(pushVectorData);
            //bottom left, position 3
            pushVectorData = {allLabels[i]->x(),allLabels[i]->y()-(wallYModifier*2)};
            DoorBlockedZone.push_back(pushVectorData);
        }
    }

}


void MainWindow::Generate_Screen_UI(){
    //Fly icons
    QString filename = "../Frog_Quest/Assets/Characters/Fly/Fly_2.png";

    string printer = filename.toStdString();
    cout << printer;

    if (QString::compare(filename, QString()) != 0){
        QImage image;
        bool valid = image.load(filename);
        image = image.scaledToWidth(IconFlyPointer->width(), Qt::SmoothTransformation);

        if(valid){
            IconFlyPointer->setPixmap(QPixmap::fromImage(image));
        } else {
            //error handling
        }
    }

}

void MainWindow::Update_Fly_Count(){
    QFont font = FlyCounterPointer->font();
    font.setPointSize(26);
    font.setBold(true);
    FlyCounterPointer->setFont(font);

    //fliesCollected
    string flyPrinter = to_string(fliesCollected) + "/" + to_string(numberOfFlies);
    QString flyPrinter2 = QString::fromStdString(flyPrinter);
    FlyCounterPointer->setText(flyPrinter2);
    //FlyCounterPointer->setFont(25);
}

void MainWindow::Count_All_Flies(){

    QString filename = "../Frog_Quest/Assets/Characters/Fly/Fly_1.png";

    string printer = filename.toStdString();
    cout << printer;

    QList<QLabel*> allLabels = this->findChildren<QLabel*>();
    //for loop that checks all labels in size.
    flyHolder.clear();
    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        string flyStringTemp = "Level_" + to_string(stageCounter) + "_fly_goal";
        if ((nameOfLabel.toStdString()).find(flyStringTemp) != std::string::npos) {
            flyHolder.append(allLabels[i]);
            numberOfFlies = numberOfFlies + 1;
            //when in rome i guess (sets up fly skins)
            if (QString::compare(filename, QString()) != 0){
                QImage image;
                bool valid = image.load(filename);
                image = image.scaledToWidth(allLabels[i]->width(), Qt::SmoothTransformation);
                //image = image.scaledToWidth(currentPlatformWidth, Qt::SmoothTransformation);

                if(valid){
                    allLabels[i]->setPixmap(QPixmap::fromImage(image));
                } else {
                    //error handling
                }
            }
        }
    }


}

void MainWindow::toSpawnPoint(){
    MainCharPointer->move(SpawnZonePointer->x(),SpawnZonePointer->y());
}

void MainWindow::whenWarped(){
    //toSpawnPoint();
    //uic.load("../Frog_Quest/Scene1.ui",self);
    //ui->setupUI(this);
    //hide();
    //lvl1.show();
    stageCounter = stageCounter + 1;
    fliesCollected = 0;
    numberOfFlies = 0;
    Pop_Up_Enteties();
    deleteAllLabels();
    clearAllArrays();
    setUpStageLabels();
    //deleteAllLabels();
    LevelSetUp();

    //deleteAllLabels();
    //setUpStageLabels();
    //LevelSetUp();

}

void MainWindow::PlayMusic(){
    //QMediaPlayer *player = new QMediaPlayer;
    //player->setMedia(QUrl::fromLocalFile("/path"));
    //player->setVolume(50);
    //player->play();
}



//Testing area
void MainWindow::TrackCharacter(){
    string tester;
    string actual;
    if(TestingBlockZone.size() == 0){
        tester = "empty";
    }else{
        tester = "full";
    }
    vector<int> trash = {1,2};
    vector<int> trash2 = {3,4};
    vector<int> trash3 = {5,6};
    TestingBlockZone2.push_back(trash);
    TestingBlockZone2.push_back(trash2);
    TestingBlockZone2.push_back(trash3);
    TestingBlockZone2.clear();
    if(TestingBlockZone2.size() == 0){
        actual = "empty";
    }else{
        actual = "full";
    }
    string PositioningOfPlayer = "x = " + to_string(MainCharPointer->x()) + ".y = " + to_string(MainCharPointer->y()) +".number of flies = " + to_string(numberOfFlies) + ".tester = " + tester + ". Actual = " + actual;
    ui->YoyoLabel->setText(QString::fromStdString(PositioningOfPlayer));
}


//junk code =====================================

//QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif"));

//Makes image
//QPixmap pic("link.png");
//pic = pic.scaledToWidth(ui->label->width(), Qt::SmoothTransformation);
//ui->label->setPixmap(pic);

//char cwd[PATH_MAX];
//strcat(cwd, "/Assets/Characters/Main/link3.jpg");
//QString filename = cwd;
//QString filename = "\Assets\Characters\Main\link3.jpg";

//ui->openGLWidget->sinkDown();
//QTimer *timer = new QTimer(this);
//connect(timer, SIGNAL(timeout()), this, SLOT(ui->openGLWidget->sinkDown();));
//timer->start(1000);

//int milliSeconds = 5*1000;
//while(1){
    //ui->openGLWidget->sinkDown();
    //Sleep(milliSeconds);
//}
//printf("crazy");
//int incrementingTime = 0;
//timeLoop(incrementingTime);

//this was in time loop==
//printf("crazy");
//incrementingTime = incrementingTime + 1;
//if(incrementingTime == TIMESPACER){
    //incrementingTime = 0;
  //  printf("crazy");
//}
//Sleep(TIMESPACER);
//timeLoop(incrementingTime);

//bool ground;
//ground = ui->openGLWidget->checkGround();
//if(ground == true){
    //ui->openGLWidget->sinkDown();
//}
//ui->openGLWidget->sinkDown();
//progressBar->setValue(progressBar->value()+1);
//QList<QPushButton*> btnList = qFindChildren<QPushButton*> ( this );
//QLabel* label = new QLabel("ui->platform_1");
//string currentPlatformPixelmap = "ui->platform_"+i+"->setPixmap(QPixmap::fromImage(image));";

//label->setObjectName(QString::fromStdString("Level_2_platform_1"));
//label->setAccessibleName("Level_2_platform_1");
//label->sizePolicy(Preferred,Preferred,0,0);
//label->setEnabled(true);
//label->setText(QString::fromStdString("BOOOOOGABOOOOGA"));
//QMainWindow->addWidget(label);
//layout->addWidget(label);
//setLayout(layout);

//QString::fromStdString(str);

//int xPoster = ui->YoyoLabel->x();
//int yPoster = ui->YoyoLabel->y();

//QHBoxLayout *layout = new QHBoxLayout();

/*
QLabel *label4 = new QLabel(this);
label4->setGeometry(-40,0,1411,731);
label4->setObjectName("Level_2_BackGround");
label4->show();

QLabel *label = new QLabel(this);
label->setGeometry(310,400,221,31);
label->setObjectName("Level_2_platform_1");
label->show();

QLabel *label2 = new QLabel(this);
label2->setGeometry(1150,250,21,251);
label2->setObjectName("Level_2_wall_1");
label2->show();

QLabel *label3 = new QLabel(this);
label3->setGeometry(40,140,151,191);
label3->setObjectName("Level_2_Main_Character");
label3->setObjectName(QString::fromStdString("Level_2_Main_Character"));
label3->show();

QLabel *label5 = new QLabel(this);
label5->setGeometry(50,0,61,41);
label5->setObjectName("Level_2_Fly_Counter");
label5->show();

QLabel *label6 = new QLabel(this);
label6->setGeometry(0,0,51,51);
label6->setObjectName("Level_2_Icon_Fly");
label6->show();

QLabel *label7 = new QLabel(this);
label7->setGeometry(540,80,31,31);
label7->setObjectName("Level_2_fly_goal_1");
label7->show();

QLabel *label8 = new QLabel(this);
label8->setGeometry(50,510,49,51);
label8->setObjectName("Level_2_spawn_point");
label8->show();

QLabel *label9 = new QLabel(this);
label9->setGeometry(-10,660,1441,61);
label9->setObjectName("Level_2_Ground");
label9->show();

QLabel *label10 = new QLabel(this);
label10->setGeometry(1150,450,21,251);
label10->setObjectName("Level_2_Door_1");
label10->show();

QLabel *label11 = new QLabel(this);
label11->setGeometry(1210,510,81,141);
label11->setObjectName("Level_2_warp_zone");
label11->show();
*/
