#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED
using namespace std;

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <vector>
#include "character.h"
#include "global.h"
#include "BomBBall.h"
#include "penguin.h"
#include "PenguinKing.h"
#include <queue>

#define font_size 12
#define grid_width 40
#define grid_height 40
#define window_width 800
#define window_height 600

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7
#define GAME_OVER 8

const float FPS = 60;
class GameWindow{;
    public:
        GameWindow();

        void game_init();
        void game_reset();
        void game_play();
        void game_begin();
        //void game_update();

        int game_run();
        int game_update();

        void show_err_msg(int msg);
        void game_destroy();
        void game_over();

        void draw_running_map();

        int process_event();

        bool mouse_hover(int ,int ,int ,int);

    private:
        int sccene = 0;
        ALLEGRO_BITMAP *icon;
        ALLEGRO_BITMAP *background = NULL;
        ALLEGRO_BITMAP *gameover = NULL;
        ALLEGRO_BITMAP *title;
        ALLEGRO_BITMAP *startt;
        ALLEGRO_BITMAP *setting;
        ALLEGRO_BITMAP *ex;

        ALLEGRO_DISPLAY* display = NULL;
        ALLEGRO_FONT *font = NULL;
        ALLEGRO_FONT *Medium_font = NULL;
        ALLEGRO_FONT *Large_font = NULL;

        ALLEGRO_KEYBOARD_STATE keystate ;

        ALLEGRO_SAMPLE *sample = NULL;
        ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
        ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
        ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
        ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
        ALLEGRO_SAMPLE_INSTANCE *button = NULL;

        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
        ALLEGRO_EVENT event;
        ALLEGRO_TIMER *timer = NULL;
        ALLEGRO_TIMER *monster_pro = NULL;


        bool redraw = false;
        bool mute = false;
        bool pause = false;
        bool OpenVolume = false;
        int getpenguinspeed = 300;
        int monsterCount = 0;
        int mouse_x, mouse_y;
        bool mousehover(int ,int ,int ,int );

        player *play = nullptr;

        queue<BomBBall*> bombBuffer;
        vector<penguin*> Penguin;
        PenguinKing *penguinking;
        int scene = 0;
        int Y = 600;
};





#endif // MAINWINDOW_H_INCLUDED
