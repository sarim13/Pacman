#include<SDL.h>
#include<list>
using namespace std;
#include "start_game.hpp"
#include "exit_game.hpp"
#include "game.hpp"
#include "pacman.hpp"
#include "ghosts.hpp"
#pragma once

class Pacmania{
    protected:
        SDL_Renderer *gRenderer;
        SDL_Texture *assets;
        Button* p1 = new Start_Game;
        Button* p2 = new Exit_Game;
        Game g;
        int grid_w;
        int grid_h;
        char* grid;

    public:
    list<Ghost*> ghosts;  
    Pacman *p;
    Pacmania(SDL_Renderer *, SDL_Texture *, char* grid_, const int grid_width, const int grid_height);
    void drawObjects(); 
    void createObject(int, int);
    SDL_Rect move_right();
    SDL_Rect move_left();
    SDL_Rect move_up();
    SDL_Rect move_down();
    void addGhosts();
    void drawPacman(int count);
    void drawGhosts();
    bool can_move_right();
    bool can_move_left();
    bool can_move_up();
    bool can_move_down();
    void moveGhost(Ghost* ghost);
    bool checkCollision(Ghost* ghost, Pacman& p);
};