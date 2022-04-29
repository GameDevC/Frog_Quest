#include <iostream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void fillLevel1();
void fillLevel2();
void fillLevel3();
void fillLevel4();
void fillLevel5();

class Asset{
public:
    int x;
    int y;
    int width;
    int height;
    string name;

    Asset(int xtran, int ytran, int widthtran, int heighttran, string nametran){
        x = xtran;
        y = ytran;
        width = widthtran;
        height = heighttran;
        name = nametran;
    }
};

vector<Asset*> level1Labels;
vector<Asset*> level2Labels;
vector<Asset*> level3Labels;
vector<Asset*> level4Labels;
vector<Asset*> level5Labels;

vector<Asset*> levelSelect(int currentLevel){


    switch(currentLevel){
    currentLevel = currentLevel - 1;

        case 1://i don't think this gets called for some reason. (starts at case 2 for level 1)
            //fillLevel1();
            //return level1Labels;
            //break;
        case 2:
            fillLevel1();
            return level1Labels;
            break;
        case 3:
            fillLevel2();
            return level2Labels;
            break;
        case 4:
            fillLevel3();
            return level3Labels;
            break;
        case 5:
            fillLevel4();
            return level4Labels;
            break;
        case 6:
            fillLevel5();
            return level5Labels;
            break;

    }

}

void fillLevel1(){

    //Base Stage Items(except maybe ground)
    level1Labels.push_back(new Asset(-40,0,1411,731, "Level_2_BackGround"));
    level1Labels.push_back(new Asset(550,210,1200,600, "Level_2_interior_1"));
    level1Labels.push_back(new Asset(50,0,200,41, "Level_2_Fly_Counter"));
    level1Labels.push_back(new Asset(0,0,51,51, "Level_2_Icon_Fly"));
    level1Labels.push_back(new Asset(40,140,151,191, "Level_2_Main_Character"));
    level1Labels.push_back(new Asset(-10,660,1441,61, "Level_2_Ground"));





    //Stage singular interactables(except maybe door)
    level1Labels.push_back(new Asset(50,510,49,51, "Level_2_spawn_point"));
    level1Labels.push_back(new Asset(1150,0,21,251, "Level_2_Door_1"));
    level1Labels.push_back(new Asset(1210,65,81,141, "Level_2_warp_zone"));

    //stage multiples interactables(except you might always need 1)
    level1Labels.push_back(new Asset(310,400,221,31, "Level_2_platform_1"));
    level1Labels.push_back(new Asset(310,200,221,31, "Level_2_platform_2"));
    level1Labels.push_back(new Asset(510,200,221,31, "Level_2_platform_3"));
    level1Labels.push_back(new Asset(710,200,221,31, "Level_2_platform_4"));
    level1Labels.push_back(new Asset(910,200,221,31, "Level_2_platform_5"));
    level1Labels.push_back(new Asset(1110,200,221,31, "Level_2_platform_6"));
    level1Labels.push_back(new Asset(550,450,21,251, "Level_2_Wall_1"));
    level1Labels.push_back(new Asset(550,250,21,251, "Level_2_Wall_2"));
    level1Labels.push_back(new Asset(550,200,21,251, "Level_2_Wall_3"));
    level1Labels.push_back(new Asset(1150,-200,21,251, "Level_2_Wall_4"));
    level1Labels.push_back(new Asset(540,80,31,31, "Level_2_fly_goal_1"));
    level1Labels.push_back(new Asset(350,350,31,31, "Level_2_fly_goal_2"));

    //User Interface
    level1Labels.push_back(new Asset(1100,0,171,41, "Level_2_Health_Bar"));
}

void fillLevel2(){
    //Base Stage Items (except maybe ground)
    level2Labels.push_back(new Asset(-40,0,1411,731, "Level_3_BackGround"));
    level2Labels.push_back(new Asset(50,0,200,41, "Level_3_Fly_Counter"));
    level2Labels.push_back(new Asset(0,0,51,51, "Level_3_Icon_Fly"));
    level2Labels.push_back(new Asset(40,140,151,191, "Level_3_Main_Character"));
    level2Labels.push_back(new Asset(-10,660,1441,61, "Level_3_Ground"));

    //Stage singular interactables(except maybe door)
    level2Labels.push_back(new Asset(50,510,49,51, "Level_3_spawn_point"));
    level2Labels.push_back(new Asset(1150,1450,21,251, "Level_3_Door_1"));
    level2Labels.push_back(new Asset(1210,510,81,141, "Level_3_warp_zone"));

    //stage multiples interactables(except you might always need 1)
    level2Labels.push_back(new Asset(260,400,221,31, "Level_3_platform_1"));
    level2Labels.push_back(new Asset(860,400,221,31, "Level_3_platform_2"));
    level2Labels.push_back(new Asset(1150,250,21,251, "Level_3_wall_1"));
    level2Labels.push_back(new Asset(310,300,31,31, "Level_3_fly_goal_1"));
    level2Labels.push_back(new Asset(610,500,31,31, "Level_3_fly_goal_2"));
    level2Labels.push_back(new Asset(910,300,31,31, "Level_3_fly_goal_3"));

    //enemy
    level2Labels.push_back(new Asset(610,600,80,80, "Level_3_trobbel_1"));

    //User Interace
    level2Labels.push_back(new Asset(1100,0,171,41, "Level_3_Health_Bar"));
}

void fillLevel3(){
    //Base Stage Items(except maybe ground)
    level3Labels.push_back(new Asset(-40,0,1411,731, "Level_4_BackGround"));
    level3Labels.push_back(new Asset(0,210,1600,800, "Level_4_interior_1"));
    level3Labels.push_back(new Asset(50,0,200,41, "Level_4_Fly_Counter"));
    level3Labels.push_back(new Asset(0,0,51,51, "Level_4_Icon_Fly"));
    level3Labels.push_back(new Asset(40,140,151,191, "Level_4_Main_Character"));
    level3Labels.push_back(new Asset(-10,660,1441,61, "Level_4_Ground"));

    //Stage singular interactables(except maybe door)
    level3Labels.push_back(new Asset(50,50,49,51, "Level_4_spawn_point"));
    level3Labels.push_back(new Asset(1150,0,21,251, "Level_4_Door_1"));
    level3Labels.push_back(new Asset(1210,65,81,141, "Level_4_warp_zone"));

    //stage multiples interactables(except you might always need 1)
    level3Labels.push_back(new Asset(310,200,221,31, "Level_4_platform_1"));
    level3Labels.push_back(new Asset(510,200,221,31, "Level_4_platform_2"));
    level3Labels.push_back(new Asset(610,200,221,31, "Level_4_platform_3"));
    level3Labels.push_back(new Asset(1010,200,221,31, "Level_4_platform_4"));
    level3Labels.push_back(new Asset(1110,200,221,31, "Level_4_platform_6"));
    level3Labels.push_back(new Asset(110,200,221,31, "Level_4_platform_5"));
    level3Labels.push_back(new Asset(0,200,221,31, "Level_4_platform_7"));
    level3Labels.push_back(new Asset(510,500,221,31, "Level_4_platform_8"));
    level3Labels.push_back(new Asset(710,350,221,31, "Level_4_platform_9"));
    level3Labels.push_back(new Asset(100,450,21,251, "Level_4_Wall_1"));
    level3Labels.push_back(new Asset(100,250,21,251, "Level_4_Wall_2"));
    level3Labels.push_back(new Asset(100,200,21,251, "Level_4_Wall_3"));
    level3Labels.push_back(new Asset(1150,-200,21,251, "Level_4_Wall_4"));
    level3Labels.push_back(new Asset(1150,450,21,251, "Level_4_Wall_5"));
    level3Labels.push_back(new Asset(1150,250,21,251, "Level_4_Wall_6"));
    level3Labels.push_back(new Asset(1150,200,21,251, "Level_4_Wall_7"));
    level3Labels.push_back(new Asset(540,80,31,31, "Level_4_fly_goal_1"));
    level3Labels.push_back(new Asset(720,260,31,31, "Level_4_fly_goal_2"));
    level3Labels.push_back(new Asset(250,480,31,31, "Level_4_fly_goal_3"));

    //enemy
    level3Labels.push_back(new Asset(770,270,80,80, "Level_4_trobbel_1"));
    level3Labels.push_back(new Asset(310,580,80,80, "Level_4_trobbel_2"));

    //User Interface
    level3Labels.push_back(new Asset(1100,0,171,41, "Level_4_Health_Bar"));

}

void fillLevel4(){
    //Base Stage Items(except maybe ground)
    level4Labels.push_back(new Asset(-40,0,1411,731, "Level_5_BackGround"));
    level4Labels.push_back(new Asset(50,0,200,41, "Level_5_Fly_Counter"));
    level4Labels.push_back(new Asset(0,0,51,51, "Level_5_Icon_Fly"));
    level4Labels.push_back(new Asset(40,140,151,191, "Level_5_Main_Character"));
    level4Labels.push_back(new Asset(-10,660,1441,61, "Level_5_Ground"));


    //Stage singular interactables(except maybe door)
    level4Labels.push_back(new Asset(50,400,49,51, "Level_5_spawn_point"));
    level4Labels.push_back(new Asset(1150,1000,21,251, "Level_5_Door_1"));
    level4Labels.push_back(new Asset(1210,400,81,141, "Level_5_warp_zone"));

    //stage multiples interactables(except you might always need 1)
    level4Labels.push_back(new Asset(0,550,221,31, "Level_5_platform_1"));
    level4Labels.push_back(new Asset(1000,550,221,31, "Level_5_platform_2"));
    level4Labels.push_back(new Asset(1200,550,221,31, "Level_5_platform_3"));
    level4Labels.push_back(new Asset(700,400,221,31, "Level_5_platform_4"));
    level4Labels.push_back(new Asset(300,400,221,31, "Level_5_platform_5"));
    level4Labels.push_back(new Asset(200,550,21,251, "Level_5_Wall_1"));
    level4Labels.push_back(new Asset(1000,550,21,251, "Level_5_Wall_2"));
    level4Labels.push_back(new Asset(600,120,31,31, "Level_5_fly_goal_1"));


    //enemy
    level4Labels.push_back(new Asset(770,1270,80,80, "Level_5_trobbel_1"));
    level4Labels.push_back(new Asset(220,600,80,80, "Level_5_spikey_1"));
    level4Labels.push_back(new Asset(300,600,80,80, "Level_5_spikey_2"));
    level4Labels.push_back(new Asset(380,600,80,80, "Level_5_spikey_3"));
    level4Labels.push_back(new Asset(460,600,80,80, "Level_5_spikey_4"));
    level4Labels.push_back(new Asset(540,600,80,80, "Level_5_spikey_5"));
    level4Labels.push_back(new Asset(620,600,80,80, "Level_5_spikey_6"));
    level4Labels.push_back(new Asset(700,600,80,80, "Level_5_spikey_7"));
    level4Labels.push_back(new Asset(780,600,80,80, "Level_5_spikey_8"));
    level4Labels.push_back(new Asset(860,600,80,80, "Level_5_spikey_9"));
    level4Labels.push_back(new Asset(940,600,80,80, "Level_5_spikey_10"));
    level4Labels.push_back(new Asset(650,270,80,80, "Level_5_rat_hatter_1"));

    //User interface
    level4Labels.push_back(new Asset(1100,0,171,41, "Level_5_Health_Bar"));

}

void fillLevel5(){
    //Base Stage Items(except maybe ground)
    level5Labels.push_back(new Asset(-40,0,1411,731, "Level_6_BackGround"));
    level5Labels.push_back(new Asset(50,0,200,41, "Level_6_Fly_Counter"));
    level5Labels.push_back(new Asset(0,0,51,51, "Level_6_Icon_Fly"));
    level5Labels.push_back(new Asset(40,140,151,191, "Level_6_Main_Character"));
    level5Labels.push_back(new Asset(-10,660,1441,61, "Level_6_Ground"));


    //Stage singular interactables(except maybe door)
    level5Labels.push_back(new Asset(50,400,49,51, "Level_6_spawn_point"));
    level5Labels.push_back(new Asset(1150,450,21,251, "Level_6_Door_1"));
    level5Labels.push_back(new Asset(1210,500,81,141, "Level_6_warp_zone"));

    //stage multiples interactables(except you might always need 1)
    level5Labels.push_back(new Asset(0,300,221,31, "Level_6_platform_1"));
    level5Labels.push_back(new Asset(800,300,221,31, "Level_6_platform_2"));
    level5Labels.push_back(new Asset(600,300,221,31, "Level_6_platform_3"));
    level5Labels.push_back(new Asset(400,300,221,31, "Level_6_platform_4"));
    level5Labels.push_back(new Asset(200,300,221,31, "Level_6_platform_5"));
    level5Labels.push_back(new Asset(1050,450,221,31, "Level_6_platform_6"));
    level5Labels.push_back(new Asset(1150,250,21,251, "Level_6_Wall_1"));
    level5Labels.push_back(new Asset(1150,50,21,251, "Level_6_Wall_2"));
    level5Labels.push_back(new Asset(1150,-50,21,251, "Level_6_Wall_3"));
    level5Labels.push_back(new Asset(100,180,31,31, "Level_6_fly_goal_1"));


    //enemy
    level5Labels.push_back(new Asset(770,1270,80,80, "Level_6_trobbel_1"));
    level5Labels.push_back(new Asset(0,380,80,80, "Level_6_spikey_1"));
    level5Labels.push_back(new Asset(80,380,80,80, "Level_6_spikey_2"));
    level5Labels.push_back(new Asset(160,380,80,80, "Level_6_spikey_3"));
    level5Labels.push_back(new Asset(240,380,80,80, "Level_6_spikey_4"));
    level5Labels.push_back(new Asset(320,380,80,80, "Level_6_spikey_5"));
    level5Labels.push_back(new Asset(400,380,80,80, "Level_6_spikey_6"));
    level5Labels.push_back(new Asset(480,380,80,80, "Level_6_spikey_7"));
    level5Labels.push_back(new Asset(560,380,80,80, "Level_6_spikey_8"));
    level5Labels.push_back(new Asset(640,380,80,80, "Level_6_spikey_9"));
    level5Labels.push_back(new Asset(720,380,80,80, "Level_6_spikey_10"));
     level5Labels.push_back(new Asset(800,380,80,80, "Level_6_spikey_11"));
     level5Labels.push_back(new Asset(0,10,80,80, "Level_6_spikey_12"));
     level5Labels.push_back(new Asset(80,10,80,80, "Level_6_spikey_13"));
     level5Labels.push_back(new Asset(160,10,80,80, "Level_6_spikey_14"));
     level5Labels.push_back(new Asset(240,10,80,80, "Level_6_spikey_15"));
     level5Labels.push_back(new Asset(320,10,80,80, "Level_6_spikey_16"));
     level5Labels.push_back(new Asset(400,10,80,80, "Level_6_spikey_17"));
     level5Labels.push_back(new Asset(480,10,80,80, "Level_6_spikey_18"));
     level5Labels.push_back(new Asset(560,10,80,80, "Level_6_spikey_19"));
     level5Labels.push_back(new Asset(640,10,80,80, "Level_6_spikey_20"));
     level5Labels.push_back(new Asset(720,10,80,80, "Level_6_spikey_21"));
      level5Labels.push_back(new Asset(800,10,80,80, "Level_6_spikey_22"));
    //level5Labels.push_back(new Asset(380,600,80,80, "Level_6_spikey_3"));
    //level5Labels.push_back(new Asset(460,600,80,80, "Level_6_spikey_4"));
    //level5Labels.push_back(new Asset(540,600,80,80, "Level_6_spikey_5"));
    //level5Labels.push_back(new Asset(620,600,80,80, "Level_6_spikey_6"));
    //level5Labels.push_back(new Asset(700,600,80,80, "Level_6_spikey_7"));
    //level5Labels.push_back(new Asset(780,600,80,80, "Level_6_spikey_8"));
    //level5Labels.push_back(new Asset(860,600,80,80, "Level_6_spikey_9"));
    //level5Labels.push_back(new Asset(940,600,80,80, "Level_6_spikey_10"));
    level5Labels.push_back(new Asset(670,90,80,80, "Level_6_rat_hatter_1"));
    level5Labels.push_back(new Asset(670,460,80,80, "Level_6_rat_hatter_2"));
    level5Labels.push_back(new Asset(370,90,80,80, "Level_6_rat_hatter_3"));
    level5Labels.push_back(new Asset(370,460,80,80, "Level_6_rat_hatter_4"));

    //User interface
    level5Labels.push_back(new Asset(1100,0,171,41, "Level_6_Health_Bar"));
}





