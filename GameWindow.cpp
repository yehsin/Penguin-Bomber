#include "GameWindow.h"
#include <iostream>
#include<functional>
#include<algorithm>
#include<random>
#include<iterator>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)

std::random_device rd;
std::mt19937 gen = std::mt19937(rd());
std::uniform_real_distribution<> dis_x(0,800);
std::uniform_real_distribution<> dis_y(0,600);
std::uniform_int_distribution<int> dis(0,3);

bool compare(BomBBall*a, BomBBall*b)
{
    return a->getpos_x()<b->getpos_x();

}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    mouse_x = event.mouse.x;
    mouse_y = event.mouse.y;
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}


void GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

void GameWindow:: game_init(){
    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./StartBackground.jpg");
    title= al_load_bitmap("./StartScene/title.png");
    startt= al_load_bitmap("./StartScene/start.png");
    setting=al_load_bitmap("./StartScene/setting.png");
    ex= al_load_bitmap("./StartScene/exit.png");


    al_set_display_icon(display, icon);
    ALLEGRO_BITMAP *start;
    ALLEGRO_BITMAP *penguin;
    ALLEGRO_BITMAP *ball;
    ALLEGRO_BITMAP *man;
    ALLEGRO_BITMAP *PenguinKing;

    start = al_load_bitmap("./StartScene/Background.png");
    penguin = al_load_bitmap("./StartScene/penguin(5).png");
    ball = al_load_bitmap("./StartScene/ball2.png");
    man = al_load_bitmap("./StartScene/man1.png");
    PenguinKing = al_load_bitmap("./StartScene/PenguinKing3.png");

    al_draw_bitmap(start,0,0,0);
    al_draw_bitmap(ball,0,0,0);
    al_draw_bitmap(PenguinKing,150,65,0);
    al_draw_bitmap(man,0,315,0);
    al_draw_bitmap(penguin,15,80,0);
    al_draw_scaled_bitmap(title,0,20, 400, 400, 215, 55,525, 550, 0);
    al_draw_scaled_bitmap(startt,0, 20, 400, 400, 215, 550, 300, 300,0);
    al_draw_scaled_bitmap(setting,0, 20, 400, 400, 400, 538, 300, 300,0);
    al_draw_scaled_bitmap(ex,0, 20, 400, 400, 550, 538, 300, 300,0);
    al_flip_display();


    al_wait_for_event(event_queue, &event);
    bool getContinue = false;

    while(!getContinue){
        if(event.type == ALLEGRO_EVENT_KEY_UP){
            if(event.keyboard.keycode == ALLEGRO_KEY_R){
                getContinue = true ;
            }
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //Ãöµøµ¡
            game_destroy();
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { //滑鼠
            if(event.mouse.button == 1) {
                if(mouse_hover(267,558,102, 20))
                   {
                    getContinue = true;
                   }
                if(mouse_hover(620,554,82,22))
                {
                    game_destroy();
                }

            }
        }

        al_wait_for_event(event_queue,&event);
    }


}

void GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;

    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }
    game_over();
    show_err_msg(msg);
}

void GameWindow::game_reset()
{
    //al_stop_sample_instance(backgroundSound);
    //al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    //al_stop_timer(monster_pro);

}

void GameWindow::game_begin()
{
    play = new player;
    penguinking = new PenguinKing(100,100);
    draw_running_map();
    al_start_timer(timer);
}

int GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");
    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();



    timer = al_create_timer(1.0 / FPS);
    monster_pro = al_create_timer(1.0 / FPS);

    if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    game_init();
}

int GameWindow::game_update()
{
    queue<BomBBall*>tmp;
    int a = bombBuffer.size();
    for(unsigned int i =0;i<a;i++){
        BomBBall*cur = bombBuffer.front();
        bombBuffer.pop();
        cur->isKing(penguinking);
        for(auto i:Penguin){
            cur->ispenguin(i,dis(gen));
        }
        if(cur->isFire()){
            if(cur->fireAttack(play)){
                if(!play->strong()){
                   play->gameover();
                    scene = 1;
                    return GAME_EXIT;
                }
            }
            for(unsigned int j = 0;j<Penguin.size();j++){
                if(cur->fireAttack(Penguin[j])){
                    penguin *m = Penguin[j];
                    Penguin.erase(Penguin.begin()+j);
                    delete m;
                    j--;
                }
                if(cur->fireAttack(penguinking)){
                        scene = 2;
                        return GAME_EXIT;
                }
            }
        }
        if(cur->DetectExplotion()){
            delete cur;
        }
        else {
            tmp.push(cur);
        }
    }
    int b = tmp.size();
    for(unsigned int i =0;i<b;i++){
        bombBuffer.push(tmp.front());
        tmp.pop();
    }
    for(auto i:Penguin){
        i->Move();
        rectangle *tmp = play->Rectangle;
        if(tmp->isOverlap(tmp,i->Rectangle)){
            if(!play->strong()){
                scene = 1;
                return GAME_EXIT;
            }
        }
    }

    if(penguinking->isstatus()) penguinking->angryStatus();
    penguinking->Move();
    rectangle* tmp1 = penguinking->Rectangle;
    if(tmp1->isOverlap(tmp1,play->Rectangle)){
            if(!play->strong()){
                scene =1;
                return GAME_EXIT;
            }
    }
    return GAME_CONTINUE;
}

void GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);
}

void GameWindow::draw_running_map()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);


    play->Draw();
    if(!bombBuffer.empty()){
        //
        for(unsigned int i = 0;i<bombBuffer.size();i++){
            bombBuffer.front()->Draw();
            BomBBall* tmp = bombBuffer.front();

            bombBuffer.push(tmp);
            bombBuffer.pop();
        }
    }
    if(!Penguin.empty()){
        for(auto i :Penguin){
            i->Draw();
        }
    }
    penguinking->Draw();
    al_flip_display();




}

int GameWindow::process_event()
{

    int instruction = GAME_CONTINUE;
    redraw = false;



    al_wait_for_event(event_queue, &event);
    if(event.type == ALLEGRO_EVENT_TIMER){
            al_get_keyboard_state(&keystate);
            if(al_key_down(&keystate,ALLEGRO_KEY_DOWN))
                play->Move(0);
            else if(al_key_down(&keystate,ALLEGRO_KEY_UP))
                play->Move(3);
            else if(al_key_down(&keystate,ALLEGRO_KEY_RIGHT))
                play->Move(2);
            else if(al_key_down(&keystate,ALLEGRO_KEY_LEFT))
                play->Move(1);
            redraw = true;
            if(monsterCount == 0){
                penguin *newone = new penguin(dis_x(gen),dis_y(gen));
                Penguin.push_back(newone);
            }
            monsterCount = (monsterCount+1)%getpenguinspeed;

    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){instruction = GAME_EXIT;}
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        if(event.keyboard.keycode == ALLEGRO_KEY_SPACE){
            if(bombBuffer.size()<3){
                BomBBall *newbomb = new BomBBall(play->getx(),play->gety(),play->getpower());
                bombBuffer.push(newbomb);
                redraw = true;
            }

        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_F){
            play->getstronger();
        }
    }

    if(redraw){
        instruction = game_update();
        draw_running_map();
        redraw = false;
    }
    return instruction;

}

void GameWindow::game_over(){
    if(scene == 1){
            al_wait_for_event(event_queue,&event);
            while(event.type != ALLEGRO_EVENT_KEY_DOWN){
            gameover = al_load_bitmap("./gameover/gameover.png");
            background = al_load_bitmap("./gameover/gameoverbackground1.jpg");
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(gameover,250,150,0);
            al_flip_display();
            al_wait_for_event(event_queue,&event);
            al_flip_display();
            al_wait_for_event(event_queue,&event);
        }
    }
    else{
            al_wait_for_event(event_queue,&event);
            while(event.type != ALLEGRO_EVENT_KEY_DOWN){
                gameover = al_load_bitmap("./gameover/win1.png");
                background = al_load_bitmap("./gameover/2.jpg");
                al_draw_bitmap(background, 0, 0, 0);
                al_draw_bitmap(gameover,250,150,0);
                al_flip_display();
                al_wait_for_event(event_queue,&event);
                al_flip_display();
                al_wait_for_event(event_queue,&event);
            }
        }
}


