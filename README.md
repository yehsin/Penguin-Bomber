# CSI2P II Final Project

[Toc]

## Penguin Bomber

#### 遊戲首頁
![](https://i.imgur.com/hEnDWG9.jpg)

#### 遊戲畫面
![](https://i.imgur.com/8n6jtnN.png)

#### 企鵝王
![](https://i.imgur.com/At3xvWh.png)

#### 企鵝王生氣
![](https://i.imgur.com/2In3i4M.png)

#### 死亡畫面
![](https://i.imgur.com/uYNQ5RQ.png)

#### 小企鵝（蛋）
![](https://i.imgur.com/7TKXGdy.png)

#### 贏得遊戲
![](https://i.imgur.com/foZG9aR.png)

## Program Datail

### Language
* C++ language
* Allegro Library
>> Allegro is a library which is using to make a game.
>> We will use it to write a game

### GameManager
* Control everything include player dead and penguin's dead.
* Write in **GameWindow.h** and **Gamewindow.cpp**
>> 1. game initail
>> 2. game begin
>> 3. game play
>> 4. game run
>> 5. process event
>> 6. game reset
>> 7. game over
>> 8. game destroy
>> 9. mouse hover
>> 10. draw map

### Character Move
* Write in **GameWindow.cpp**
* Using the event "Allegro event time" that when we triggered the keyboard, it will generate an event to entry the if-else.

```cpp
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
```

#### Character moving handle
* Write in **Character.h** and **Character.cpp**
* When the keyboard event occurs in GameWindow.cpp，it will call the **player.move()** in Character.cpp. It will control how many distance the player moving.

```cpp=
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
```
### Monster Move
* Write in **game update**
* Range restrict in the game window

#### Penguin moving Handle
```cpp=
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
```
```cpp=
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
```
#### Penguin Life Handle
```cpp=
bool PenguinKing::SubstractHealth(int a)
{
    health-=a;
    if(health<5) status = true;
    if(health == 0) return true;
    return false;


}
```
* Status for Penguin's mood (normal or angry)

### Bomb Ball
* Control in game update and exercise in **BombBall.cpp**
#### Bomb power
```cpp=
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
```

#### Fire in 1 seconds
```cpp=
timeout = (timeout+10)%frequency;
    if(timeout == 0)explotion = true;
```
#### Bomb fire will attack Penguin
```cpp=
bool BomBBall::fireAttack(penguin* a){
    bool death = true;
    if(rectangle_len->isOverlap(rectangle_len,a->Rectangle)){if(a->SubstractHealth(1)){return death;std::cout<<"d";}}
    if(rectangle_hei->isOverlap(rectangle_hei,a->Rectangle)){if(a->SubstractHealth(1)){return death;std::cout<<"d";}}
    return false;
}
```

#### Bimb fire will attack player, too
```cpp=
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
    return false;
```

