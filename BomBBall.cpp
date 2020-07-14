#include"BomBBall.h"
#include<iostream>
BomBBall::BomBBall(float x,float y,int Power)
{
    pos_x = x;
    pos_y = y;
    power = Power;
    Rectangle = new rectangle(x,y,50,50);
    rectangle_hei = new rectangle(pos_x,pos_y-power,50,power*2+50);
    rectangle_len = new rectangle(pos_x-power,pos_y,power*2+50,50);

}
void BomBBall::Draw()
{
    static int animatCounts;
    timeout = (timeout+1)%frequency;
    char buffer[50];
    sprintf(buffer,"./Bomb/hellBomb/IMG00%d.png",animatCounts);
    if(timeout == 0){
            status = true;
    }
    if(status){

        fireAnimation();
    }
    else{
        bomb = al_load_bitmap(buffer);
        if(animatCounts == 7) animatCounts =0;
        animatCounts++;
        al_draw_bitmap(bomb,pos_x,pos_y,0);

    }


}

void BomBBall::fireAnimation(){
    bomb = al_load_bitmap("./fire/bomb1.png");
    al_draw_bitmap(bomb,pos_x,pos_y,0);
    for(int i =40;i<power  ;i+=50){
        firepower_height = al_load_bitmap("./fire/fire_down1.png");
        al_draw_bitmap(firepower_height,pos_x,pos_y+i,0);
    }
    for(int j = 40;j<power ;j+=50){
        firepower_width = al_load_bitmap("./fire/fire_right1.png");
        al_draw_bitmap(firepower_width,pos_x+j,pos_y,0);
    }
    for(int i =40;i<power ;i+=50){
        firepower_height = al_load_bitmap("./fire/fire_up1.png");
        al_draw_bitmap(firepower_height,pos_x,pos_y-i,0);
    }
    for(int j = 40;j<power ;j+=50){
        firepower_width = al_load_bitmap("./fire/fire_left1.png");
        al_draw_bitmap(firepower_width,pos_x-j,pos_y,0);
    }
    timeout = (timeout+10)%frequency;
    if(timeout == 0)explotion = true;

}

BomBBall::~BomBBall(){
    al_destroy_bitmap(firepower_height);
    al_destroy_bitmap(firepower_width);
    al_destroy_bitmap(bomb);
    firepower_height = nullptr;
    firepower_width = nullptr;
    bomb = nullptr;
}

bool BomBBall::fireAttack(penguin* a){
    bool death = true;
    if(rectangle_len->isOverlap(rectangle_len,a->Rectangle)){if(a->SubstractHealth(1)){return death;std::cout<<"d";}}
    if(rectangle_hei->isOverlap(rectangle_hei,a->Rectangle)){if(a->SubstractHealth(1)){return death;std::cout<<"d";}}
    return false;
}

bool BomBBall::fireAttack(player *a){
    if(rectangle_len->isOverlap(rectangle_len,a->Rectangle))return true;
    if(rectangle_hei->isOverlap(rectangle_hei,a->Rectangle))return true;
    return false;
}

bool BomBBall::fireAttack(PenguinKing *a)
{
    bool death = true;

    if(rectangle_len->isOverlap(rectangle_len,a->Rectangle)){
            if(!Fired){
                if(a->SubstractHealth(1)){
                    return death;
                }
                else Fired = true;
            }

    }
    if(rectangle_hei->isOverlap(rectangle_hei,a->Rectangle)){
            if(!Fired){
                if(a->SubstractHealth(1)){
                    return death;
                }
                else Fired = true;
            }

    }

    /*if(a->getx()+a->w<pos_x+fire_width && a->getx()+a->w>pos_x-fire_width && a->gety()+a->h<pos_y+power && a->gety()+a->h>pos_y-power){
        std::cout<<"D"<<std::endl;
        if(a->SubstractHealth(1)){return death;}
    }

    else if(a->getx()+a->w<pos_x+power && a->getx()+a->w>pos_x-power && a->gety()+a->h<pos_y+fire_width && a->gety()+a->h>pos_y-fire_width){
        std::cout<<"D"<<std::endl;
        if(a->SubstractHealth(1)){return death;}

    }*/

    return false;

}

