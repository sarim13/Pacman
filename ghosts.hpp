#include<SDL.h>
#include <string>
#include <vector>
#include <fstream>
#pragma once

class Ghost{
bool come_back=false;
bool flag = false;
bool canMove = false;
char* grid;
int grid_w;
int grid_h;
public:
    ~Ghost();
    SDL_Rect srcRect, moverRect;
    void draw(SDL_Renderer*, SDL_Texture* assets);
    char direction2 = 's';
    bool changeDirection = true;
    Ghost(int i, char* grid_, int gridw, int gridh);
    void move_pac_right();
    void move_pac_left();
    void move_pac_up();
    void move_pac_down();
    bool check_move_right();
    bool check_move_left();
    bool check_move_down();
    bool check_move_up();
    SDL_Rect* getMover();
};
