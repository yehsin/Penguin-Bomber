#include "GameWindow.h"
#include<iostream>

int main(int argc, char *argv[])
{
    //std::cout<<"OO";
    GameWindow *TowerGame= new GameWindow;
    //std::cout<<"LL";
    TowerGame->game_play();

    delete TowerGame;
    return 0;
}
