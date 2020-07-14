#ifndef PENGUIN_H_INCLUDED
#define PENGUIN_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "rectangle.h"


class penguin
{
    private:
        float x,y;
        bool status = false; //egg or penguin
        int health =5 ;
        int speed = 2;
        int frequency = 120;
        int trans  = 0;
        int dir = 0;
        int animation = 0;
        int anispeed = 0;
        ALLEGRO_BITMAP *Penguin = nullptr;

    public:
        penguin(float x,float y);
        ~penguin();
        void Draw();
        void Move();
        void LoadMove();
        void detect();
        void change(); //egg convert to penguin
        float getx(){return x;}
        float gety(){return y;}
        bool SubstractHealth(int);
        void setdir(int a);
        rectangle *Rectangle;

};


#endif // PENGUIN_H_INCLUDED
