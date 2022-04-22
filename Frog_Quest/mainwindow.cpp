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

using namespace std;

//top left, position 0 | top right, position 1 | bottom left, position 2 | bottom right, position 3
vector<vector<int>> BlockedZone;
QList<QLabel*> flyHolder;
vector<vector<int>> WallBlockedZone;
vector<vector<int>> DoorBlockedZone;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //lvl1.setParent(this);

    //Sets window preferences
    setWindowTitle("Frog Quest");
    setFixedWidth(1280);
    setFixedHeight(720);

    //spawn player
    toSpawnPoint();
    ui->spawn_point->setText("");

    //makes time
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateProgress);
    timer->start(50);

    QTimer *animtimer = new QTimer(this);
    connect(animtimer, &QTimer::timeout, this, &MainWindow::animationCaller);
    animtimer->start(150);


    //makes Main Character
    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Characters/Main/MC_Idel1.png";

    string printer = filename.toStdString();
    cout << printer;

    if (QString::compare(filename, QString()) != 0){
        QImage image;
        bool valid = image.load(filename);
        image = image.scaledToWidth(ui->Main_Character->width(), Qt::SmoothTransformation);

        if(valid){
            ui->Main_Character->setPixmap(QPixmap::fromImage(image));
        } else {
            //error handling
        }
    }

    //test label
    ui->Change_text_label->setText("");

    Set_Ground();
    Set_BackGround();
    Generate_Platforms();
    Generate_Blocked_Zones();
    Generate_Screen_UI();
    Count_All_Flies();

    Generate_Walls();
    Generate_Blocked_Walls();

    Generate_Doors();
    Generate_Blocked_Doors();

    Generate_Warp();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateProgress()
{
    //WORKS OF GRAVITY
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
    ui->Main_Character->move(ui->Main_Character->x() + xSpeed,ui->Main_Character->y());
    if(xSpeed != 0){
        Horizontal_Drag();
    }
    Push_Out_Of_Ground();
    Update_Fly_Count();

    Detect_Fly();
    Detect_Portal();

}

void MainWindow::animationCaller()
{
    //fly animation
    int flyCount = 2;

    //QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Characters/Fly/Fly_" + QString::fromStdString(to_string(flyCurrentCount)) + ".png";

    if(flyCurrentCount > flyCount){
        flyCurrentCount = 1;
    }
    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Characters/Fly/Fly_" + QString::fromStdString(to_string(flyCurrentCount)) + ".png";
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


void MainWindow::timeLoop(int incrementingTime){
    //this is useless
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_D) {
        //ui->Main_Character->move(ui->Main_Character->x() + 15,ui->Main_Character->y());
        blockedMovingXp = Check_Wall_Positive();
        blockedMovingXp2 = Check_Door_Positive();
        if(blockedMovingXp == false && blockedMovingXp2 == false){
            xSpeed = baseSpeed;
        }

    }

    if (event->key() == Qt::Key_A) {
         //ui->Main_Character->move(ui->Main_Character->x() - 15,ui->Main_Character->y());
        blockedMovingXn = Check_Wall_Negative();
        blockedMovingXn2 = Check_Door_Negative();
        if(blockedMovingXn == false && blockedMovingXn2 == false){
            xSpeed = -baseSpeed;
        }

    }

    if (event->key() == Qt::Key_W) {
        //ui->Main_Character->move(ui->Main_Character->x() ,ui->Main_Character->y() - 15);
        if(inAir == false){
            inAir = true;
            gravitySpeed = -jumpSpeed;
            Gravity();
        }

        //Gravity();
    }

    if (event->key() == Qt::Key_Space) {
        //ui->Main_Character->move(ui->Main_Character->x() ,ui->Main_Character->y() - 15);
        if(inAir == false){
            inAir = true;
            gravitySpeed = -jumpSpeed;
            Gravity();
        }

        //Gravity();
    }

    if (event->key() == Qt::Key_S) {
        //ui->openGLWidget->effectZero();
        //ui->openGLWidget->Crouch(-0.5f);

         //removed becaues you don't really move through the ground
         //ui->Main_Character->move(ui->Main_Character->x(),ui->Main_Character->y() + 15);
    }

}

void MainWindow::Gravity(){
    Gravity_Pull();
    if(ui->Main_Character->y() + gravitySpeed <= ui->Ground->y() - (groundMultiplier*ui->Ground->height())){
        ui->Main_Character->move(ui->Main_Character->x(),ui->Main_Character->y() + gravitySpeed);
    }else if(onPlatform == true){
        ui->Main_Character->move(ui->Main_Character->x(),platformYHolder);
    }else{
        ui->Main_Character->move(ui->Main_Character->x(),ui->Ground->y() - (groundMultiplier*ui->Ground->height()));
        inAir = false;
    }
}

void MainWindow::Set_BackGround(){
    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Characters/Main/TempBackground.jpg";

    string printer = filename.toStdString();
    cout << printer;

    if (QString::compare(filename, QString()) != 0){
        QImage image;
        bool valid = image.load(filename);
        image = image.scaledToWidth(ui->BackGround->width(), Qt::SmoothTransformation);

        if(valid){
            ui->BackGround->setPixmap(QPixmap::fromImage(image));
        } else {
            //error handling
        }
    }
}

void MainWindow::Set_Ground(){
    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Level/Grond/Dirt.jpg";

    string printer = filename.toStdString();
    cout << printer;

    if (QString::compare(filename, QString()) != 0){
        QImage image;
        bool valid = image.load(filename);
        image = image.scaledToWidth(ui->Ground->width(), Qt::SmoothTransformation);

        if(valid){
            ui->Ground->setPixmap(QPixmap::fromImage(image));
        } else {
            //error handling
        }
    }
}

void MainWindow::Generate_Platforms(){
    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Level/Platforms/Wooden_Platform1.png";

    string printer = filename.toStdString();
    cout << printer;

    //sets name of platforms
    string currentPlatform = "platform_1";
    QString labelExtension = "platform_1";
    QLabel* label = ui->platform_1;
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
    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Level/Walls/Wall_1.png";

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
    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Level/Doors/Door_1.png";

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

void MainWindow::Generate_Warp(){
    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Level/Portals/portal_1.png";

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

bool MainWindow::Check_Ground(){
    int MC_Ypos = ui->Main_Character->y();
    int Ground_Ypos = ui->Ground->y();
    if(MC_Ypos <= Ground_Ypos - ((groundMultiplier+.1)*ui->Ground->height())){
        return true;
    }
    return false;
}

bool MainWindow::Check_Platform(){
    int MC_Ypos = ui->Main_Character->y();//top
    int MC_Ypos2 = ui->Main_Character->y()+ui->Main_Character->height();//bottom
    int MC_Xpos = ui->Main_Character->x();//left
    int MC_Xpos2 = ui->Main_Character->x() + ui->Main_Character->width();//right
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
                //ui->Main_Character->move(ui->Main_Character->x(),BlockedZone[i][1]-210);
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
        if(ui->Main_Character->y() < WallBlockedZone[i][1]-100 && ui->Main_Character->y() > WallBlockedZone[i+2][1]-100){
            if(ui->Main_Character->x() + 100 < WallBlockedZone[i][0] && ui->Main_Character->x() + xSpeed + 130 >= WallBlockedZone[i][0]){
                return true;
            }
        }
    }
    return false;
}


bool MainWindow::Check_Wall_Negative(){

    for(int i = 0; i< WallBlockedZone.size(); i += 4){
        if(ui->Main_Character->y() < WallBlockedZone[i][1]-100 && ui->Main_Character->y() > WallBlockedZone[i+2][1]-100){
            if(ui->Main_Character->x() + 35 > WallBlockedZone[i][0] && ui->Main_Character->x() + xSpeed + 0 <= WallBlockedZone[i][0]){
                return true;
            }
        }
    }
    return false;
}

bool MainWindow::Check_Door_Positive(){

    for(int i = 0; i< DoorBlockedZone.size(); i += 4){
        if(ui->Main_Character->y() < DoorBlockedZone[i][1]-100 && ui->Main_Character->y() > DoorBlockedZone[i+2][1]-100){
            if(ui->Main_Character->x() + 100 < DoorBlockedZone[i][0] && ui->Main_Character->x() + xSpeed + 130 >= DoorBlockedZone[i][0]){
                return true;
            }
        }
    }
    return false;
}


bool MainWindow::Check_Door_Negative(){

    for(int i = 0; i< DoorBlockedZone.size(); i += 4){
        if(ui->Main_Character->y() < DoorBlockedZone[i][1]-100 && ui->Main_Character->y() > DoorBlockedZone[i+2][1]-100){
            if(ui->Main_Character->x() + 35 > DoorBlockedZone[i][0] && ui->Main_Character->x() + xSpeed + 0 <= DoorBlockedZone[i][0]){
                return true;
            }
        }
    }
    return false;
}

void MainWindow::Detect_Fly(){
    int MC_Ypos = ui->Main_Character->y();//top
    int MC_Ypos2 = ui->Main_Character->y()+ui->Main_Character->height();//bottom
    int MC_Xpos = ui->Main_Character->x();//left
    int MC_Xpos2 = ui->Main_Character->x() + ui->Main_Character->width();//right
    for(int i = 0; i < flyHolder.size(); i++){
        //flyHolder[i]->move(flyHolder[i]->x(), flyHolder[i]->y() + 1);
        if(flyHolder[i]->x() > MC_Xpos && flyHolder[i]->x()+8 < MC_Xpos2){
            if(flyHolder[i]->y() > MC_Ypos && flyHolder[i]->y() < MC_Ypos2){
                //ui->Main_Character->move(ui->Main_Character->x(),ui->Main_Character->y() - 15);
                flyHolder[i]->move(flyHolder[i]->x(), flyHolder[i]->y() - 1000);
                fliesCollected = fliesCollected + 1;
                Door_Lock();
            }
        }
    }
}

void MainWindow::Detect_Portal(){
    int MC_Ypos = ui->Main_Character->y();//top
    int MC_Ypos2 = ui->Main_Character->y()+ui->Main_Character->height();//bottom
    int MC_Xpos = ui->Main_Character->x();//left
    int MC_Xpos2 = ui->Main_Character->x() + ui->Main_Character->width();//right
    QLabel* portalHold = ui->warp_zone;
        if(portalHold->x() > MC_Xpos-7 && portalHold->x()+10 < MC_Xpos2){
            if(portalHold->y() > MC_Ypos-7 && portalHold->y()+7 < MC_Ypos2){
                //toSpawnPoint();
                //uic.load("C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Scene1.ui",self);
                //ui->setupUI(this);
                //hide();
                //lvl1.show();
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
    int Ground_Ypos = ui->Ground->y();
    Ground_Ypos = Ground_Ypos - (groundMultiplier*ui->Ground->height());
    if(ui->Main_Character->y() > Ground_Ypos){
        float pushOutSpeed = 3;
        ui->Main_Character->move(ui->Main_Character->x(),ui->Main_Character->y() - pushOutSpeed);
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
        if ((nameOfLabel.toStdString()).find("platform_") != std::string::npos) {
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
        if ((nameOfLabel.toStdString()).find("Wall_") != std::string::npos) {
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
    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Characters/Fly/Fly_2.png";

    string printer = filename.toStdString();
    cout << printer;

    if (QString::compare(filename, QString()) != 0){
        QImage image;
        bool valid = image.load(filename);
        image = image.scaledToWidth(ui->Icon_Fly->width(), Qt::SmoothTransformation);

        if(valid){
            ui->Icon_Fly->setPixmap(QPixmap::fromImage(image));
        } else {
            //error handling
        }
    }

}

void MainWindow::Update_Fly_Count(){


    //fliesCollected
    string flyPrinter = to_string(fliesCollected) + "/" + to_string(numberOfFlies);
    QString flyPrinter2 = QString::fromStdString(flyPrinter);
    ui->Fly_Counter->setText(flyPrinter2);
}

void MainWindow::Count_All_Flies(){

    QString filename = "C:/Users/nacde/OneDrive/Documents/SchoolCode/CSE165/Project/Frog_Quest/Assets/Characters/Fly/Fly_1.png";

    string printer = filename.toStdString();
    cout << printer;

    QList<QLabel*> allLabels = this->findChildren<QLabel*>();
    //for loop that checks all labels in size.
    for(int i = 0; i < allLabels.size(); i++){
        //get the name of the current label
        QString nameOfLabel = allLabels[i]->objectName();
        //check if name has platform_ in it
        if ((nameOfLabel.toStdString()).find("fly_goal_") != std::string::npos) {
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
    ui->Main_Character->move(ui->spawn_point->x(),ui->spawn_point->y());
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
