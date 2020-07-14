#ifndef BOMBBALL_H_INCLUDED
#define BOMBBALL_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "penguin.h"
#include "PenguinKing.h"
#include "rectangle.h"
#include "character.h"
class BomBBall
{
    private:
        bool Fired = false;
        bool explotion = false;
        int frequency = 60;
        int status = false; //ball or fire
        int timeout = 0;
        int power = 100;
        int fire_width = 30;
        float pos_x;
        float pos_y;
        ALLEGRO_BITMAP *bomb = nullptr;
        ALLEGRO_BITMAP *firepower_height;
        ALLEGRO_BITMAP *firepower_width;

        rectangle *rectangle_len;
        rectangle *rectangle_hei;
    public:
        rectangle *Rectangle;
        BomBBall(float ,float,int);
        ~BomBBall();
        void Draw();
        void fireAnimation();
        float getpos_x(){
            return pos_x;
        }
        float getpos_y(){
            return pos_y;
        }
        bool isFire(){
            if(status){
                return true;
            }
            return false;
        }

        bool DetectExplotion(){
            if(explotion)return true;
            return false;
        }
        bool fireAttack(penguin*a);
        bool fireAttack(player *a);
        bool fireAttack(PenguinKing *a);
        int gettimeout(){return timeout;}
        void isKing(PenguinKing *a){
            if(Rectangle->isOverlap(Rectangle,a->Rectangle)) status = true;
        }
        void ispenguin(penguin *a,int b){
            if(Rectangle->isOverlap(Rectangle,a->Rectangle)) a->setdir(b);
        }

};


#endif // BOMBBALL_H_INCLUDED
