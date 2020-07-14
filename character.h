#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include "rectangle.h"
#include <allegro5/allegro.h>
#include "rectangle.h"

enum direction {Down=0,Left,Right,Up};

class player
{
    public:
        player();
        ~player();
        void Draw();
        void Move(int direct);
        void setBomb();
        float getx(){
            return x;
        }
        float gety(){
            return y;
        }
        int getpower(){
            return firePower;
        }
        void gameover(){
            play = al_load_bitmap("./death/death1.png");
            al_draw_bitmap(play,x,y,0);
        }
        void getstronger(){stronger = true;}
        bool strong(){return stronger;}
        rectangle *Rectangle;
    private:
        ALLEGRO_BITMAP *play = nullptr;
        int BombNumbers = 5;
        int speed = 5;
        int firePower = 100;
        float x = 0;
        float y = 0;
        bool stronger = false;
        //vector<BombBall> Bomb;

};






#endif // CHARACTER_H_INCLUDED
