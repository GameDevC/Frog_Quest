#include <iostream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void fillLevel1();
void fillLevel2();

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
            return level1Labels;
            break;

    }

}

void fillLevel1(){

    //Base Stage Items(except maybe ground)
    level1Labels.push_back(new Asset(-40,0,1411,731, "Level_2_BackGround"));
    level1Labels.push_back(new Asset(50,0,61,41, "Level_2_Fly_Counter"));
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
}

void fillLevel2(){
    //Base Stage Items (except maybe ground)
    level1Labels.push_back(new Asset(-40,0,1411,731, "Level_3_BackGround"));
    level1Labels.push_back(new Asset(50,0,61,41, "Level_3_Fly_Counter"));
    level1Labels.push_back(new Asset(0,0,51,51, "Level_3_Icon_Fly"));
    level1Labels.push_back(new Asset(40,140,151,191, "Level_3_Main_Character"));
    level1Labels.push_back(new Asset(-10,660,1441,61, "Level_3_Ground"));

    //Stage singular interactables(except maybe door)
    level1Labels.push_back(new Asset(50,510,49,51, "Level_3_spawn_point"));
    level1Labels.push_back(new Asset(1150,450,21,251, "Level_3_Door_1"));
    level1Labels.push_back(new Asset(1210,510,81,141, "Level_3_warp_zone"));

    //stage multiples interactables(except you might always need 1)
    level1Labels.push_back(new Asset(310,400,221,31, "Level_3_platform_1"));
    level1Labels.push_back(new Asset(1150,250,21,251, "Level_3_wall_1"));
    level1Labels.push_back(new Asset(540,80,31,31, "Level_3_fly_goal_1"));
}
