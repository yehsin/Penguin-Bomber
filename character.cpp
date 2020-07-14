#include"character.h"

player::player(){
    play = al_load_bitmap("./Character/Down.png");
    Rectangle = new rectangle(x,y,30,40);
}

void player::Move(int direct)
{
    switch(direct){
    case Down:{
            y +=speed;
            play = al_load_bitmap("./Character/Down.png");
            Rectangle->y = y;
            break;
        }
    case Left:{
            x-=speed;
            play = al_load_bitmap("./Character/Left.png");
            Rectangle->x = x;
            break;
        }
    case Up:{
            y-=speed;
            play = al_load_bitmap("./Character/Up.png");
            Rectangle->y = y;
            break;
        }
    case Right:{
            x+=speed;
            play = al_load_bitmap("./Character/Right.png");
            Rectangle-> x = x;
            break;
        }
    }

}

void player::Draw()
{
    al_draw_bitmap(play,x,y,0);

}


