/*
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <MMsystem.h>
//#include <mciapi.h>
//#include <QtMultimedia/QMediaPlayer>
//#include <QMediaPlayer>

//#include <iostream>
#include <Windows.h>
#include <ctime>

//#pragma comment(lib, "Winmm.lib")

using namespace std;

//PlaySound(string, string, string);

void PlayMusic(){

    //PlaySound(TEXT("C:\\Users\\fefse.wav"), NULL, SND_ASYNC);
    //QMediaPlayer *player = new QMediaPlayer;
    //player->setMedia(QUrl::fromLocalFile("/path"));
    //player->setVolume(50);
    //player->play();


    player = new QMediaPlayer;
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    player->setVolume(50);
    player->play();

}
*/
