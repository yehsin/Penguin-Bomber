#include"penguin.h"
#include<iostream>
#include<random>
std::random_device rda;
std::mt19937 gena = std::mt19937(rda());
std::uniform_int_distribution<int> directa(0,3);

 penguin::penguin(float posx,float posy):x(0),y(0){

    x = posx;
    y = posy;
    Rectangle = new rectangle(x,y,45,49);

 }

 penguin::~penguin(){
    al_destroy_bitmap(Penguin);
 }

 void penguin::change(){
    Penguin = al_load_bitmap("./penguin/penguin1/IMG00000-.png");
    health = 15;
 }
 void penguin::Move(){
     if(x>800){
        x-=speed;
        dir = directa(gena);
        Rectangle->x = x;
     }
     else if(y>600){
        y-=speed;
        dir = directa(gena);
        Rectangle->y = y;
     }
     else if(x<0){
        x+=speed;
        dir = directa(gena);
        Rectangle->x = x;
     }
     else if(y<0){
        y+=speed;
        dir = directa(gena);
        Rectangle->y = y;
     }


    switch(dir){
        case 0 :
            y += speed;
            Rectangle->y = y;
            break;
        case 1 :
            x += speed;
            Rectangle->x = x;
            break;
        case 2 :
            y -= speed;
            Rectangle->y = y;
            break;
        case 3 :
            x -= speed;
            Rectangle->x = x;
            break;
    }

 }

 void penguin::Draw(){
    trans = (trans+1) %  frequency;
    if(!trans){
            status = true;
            change();
    }
    if(status){
        //std::cout<<"LL";
        char buffer[50];
        if(anispeed == 0){
            sprintf(buffer,"./penguin/penguin1/IMG0000%d-.png",animation);
            Penguin = al_load_bitmap(buffer);
            animation++;
            if(animation == 9)animation = 0;
        }
        anispeed ++;
        if(anispeed == 5) anispeed =0;
    }
    else{
        Penguin = al_load_bitmap("./penguin/egg2.png");
    }
    al_draw_bitmap(Penguin,x,y,0);
    //al_flip_display();

 }

 bool penguin::SubstractHealth(int a)
{
    health-=a;
    if(health == 0) return true;
    return false;

}

void penguin::setdir(int a){
        dir = a;

}





