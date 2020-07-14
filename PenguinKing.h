#ifndef PENGUINKING_H_INCLUDED
#define PENGUINKING_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "rectangle.h"
class PenguinKing
{
    private:
        float pos_x,pos_y;
        int health = 10;
        int speed = 3;
        int frequency =0;
        int dir = 0;
        bool status = false; //normal or angry;


        ALLEGRO_BITMAP *penguinking = nullptr;
    public:
        PenguinKing(float,float);
        ~PenguinKing();
        bool normalStatus();
        void angryStatus();
        bool isstatus()
        {
            return status;
        }
        void Draw();
        void deadAnimation();
        void Move();
        void LoadMove();
        int getx(){return pos_x;}
        int gety() {return pos_y;}
        bool SubstractHealth(int a);
        int w,h;
        rectangle *Rectangle;

};


#endif // PENGUINKING_H_INCLUDED
