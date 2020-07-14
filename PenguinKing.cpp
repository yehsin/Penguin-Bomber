#include"PenguinKing.h"
#include <random>
#include<iostream>

std::random_device rds;
std::mt19937 gens = std::mt19937(rds());
std::uniform_int_distribution<int> direct(0,3);

PenguinKing::PenguinKing(float x,float y)
{
    pos_x = x;
    pos_y = y;
    Rectangle = new rectangle(x,y,250,260);
}

PenguinKing::~PenguinKing()
{
    al_destroy_bitmap(penguinking);
}

void PenguinKing::Move(){
    if(pos_y+275>600){
        pos_y-=speed;
        dir = (dir+1)%4;
    }
    else if(pos_x+266>800){
        pos_x -=speed;
        dir = (dir+1)%4;
    }
    else if(pos_y<0){
        pos_y+=speed;
        dir = (dir+1)%4;
    }
    else if(pos_x<0){
        pos_x +=speed;
        dir = (dir+1)%4;
    }
    //std::cout<<dir<<std::endl;
    switch(dir){
        case 0 :
            pos_y += speed;
            Rectangle->y = pos_y;
            break;
        case 1 :
            pos_x += speed;
            Rectangle->x = pos_x;
            break;
        case 2 :
            pos_y -= speed;
            Rectangle->y = pos_y;
            break;
        case 3 :
            pos_x -= speed;
            Rectangle->x = pos_x;
            break;
    }

}

void PenguinKing::Draw()
{
    if(status)
    {
        ALLEGRO_BITMAP *penguinking = al_load_bitmap("./PenguinKing/00001.png");
        if(penguinking == nullptr) penguinking = al_load_bitmap("./PenguinKing/00002.png");

        al_draw_bitmap(penguinking,pos_x,pos_y,0);
    }
    else{
        ALLEGRO_BITMAP *penguinking = al_load_bitmap("./PenguinKing/00000.png");
        if(penguinking == nullptr) penguinking = al_load_bitmap("./PenguinKing/00002.png");
        al_draw_bitmap(penguinking,pos_x,pos_y,0);
    }

}

bool PenguinKing::SubstractHealth(int a)
{
    health-=a;
    if(health<5) status = true;
    if(health == 0) return true;
    return false;


}

void PenguinKing::angryStatus()
{
    if(frequency == 0){

        dir = direct(gens);
    }
    frequency = (frequency+1)%300;

}






