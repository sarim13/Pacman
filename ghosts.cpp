#include "ghosts.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

SDL_Rect* Ghost:: getMover(){
    return &moverRect;
}

Ghost::~Ghost(){
    
}
void Ghost::draw(SDL_Renderer* gRenderer, SDL_Texture* assets){
    SDL_RenderCopy(gRenderer, assets, &srcRect, &moverRect);
}
bool Ghost::check_move_right(){
    bool canMove = true;
    int x = moverRect.x+25;
    int y = moverRect.y;
    char c;
    for(int i = 0; i < grid_h; i++){
		for(int j = 0; j<grid_w; j++){
            c = *(grid+i*grid_w + j);  
            if(i==y/25 & j==x/25 & c=='x'){
                return canMove=false;
                break;
            }
        }
    }
    return canMove;
}
bool Ghost::check_move_left(){
    bool canMove = true;
    int x = moverRect.x-25;
    int y = moverRect.y;
    char c;
    for(int i = 0; i < grid_h; i++){
		for(int j = 0; j<grid_w; j++){
            c = *(grid+i*grid_w + j);  
            if(i==y/25 & j==x/25 & c=='x'){
                return canMove=false;
                break;
            }
        }
    }
    return canMove;
}
bool Ghost::check_move_down(){
    bool canMove = true;
    int x = moverRect.x;
    int y = moverRect.y+25;
    char c;
    for(int i = 0; i < grid_h; i++){
		for(int j = 0; j<grid_w; j++){
            c = *(grid+i*grid_w + j);  
            if(i==y/25 & j==x/25 & c=='x'){
                return canMove=false;
                break;
            }
        }
    }
    return canMove;
} 

bool Ghost::check_move_up(){
    bool canMove = true;
    int x = moverRect.x;
    int y = moverRect.y-25;
    char c;
    for(int i = 0; i < grid_h; i++){
		for(int j = 0; j<grid_w; j++){
            c = *(grid+i*grid_w + j);  
            if(i==y/25 & j==x/25 & c=='x'){
                return canMove=false;
                break;
            }
        }
    }
    return canMove;
} 

void Ghost :: move_pac_right(){
    moverRect.x += 25;
}

void Ghost :: move_pac_left(){
    moverRect.x -= 25;
}

void Ghost :: move_pac_up(){
    moverRect.y -= 25; 
}

void Ghost :: move_pac_down(){
    moverRect.y += 25;
}


Ghost::Ghost(int i, char* grid_, int gridw, int gridh){
    srcRect = {485,66,105,98};
    moverRect = {100, 50, 25, 25};
    moverRect.x+=(25*i);
    grid = grid_;
    grid_w = gridw;
    grid_h = gridh;
    srcRect.x+=25;
}




