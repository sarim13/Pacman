#include "pacman.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;
// pigeon implementation will go here.


void Pacman::draw(SDL_Renderer* gRenderer, SDL_Texture* assets){

    SDL_RenderCopy(gRenderer, assets, &srcRect, &moverRect);
  
    }
bool Pacman::check_move_right(){
    if(counter==total_food){
        isRunning = false;
    }
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
            else if(i==y/25 & j==x/25 & c=='.'){
                canMove=true;
                *(grid+i*grid_w + j) = ' ';  //replaced
                counter++;
                break;
            }
            else if(i==y/25 & j==x/25 & c==','){
                canMove=true;
                power = true;
                time(&begin);
                *(grid+i*grid_w + j) = ' ';//replaced
                counter++;
                break;
            }
            else if(i==y/25 & j==x/25 & c==' '){
                canMove=true;
                break;
            }
        }
    }
    return canMove;
}

bool Pacman::check_move_left(){
    if(counter==total_food){
        isRunning = false;
    }
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
            else if(i==y/25 & j==x/25 & c=='.'){
                canMove=true;
                *(grid+i*grid_w + j) = ' ';//replaced
                counter++;
                break;
            }
            else if(i==y/25 & j==x/25 & c==','){
                canMove=true;
                power = true;
                time(&begin);
                *(grid+i*grid_w + j) = ' ';//replaced
                counter++;
                break;
            }
            else if(i==y/25 & j==x/25 & c==' '){
                canMove=true;
                break;
            }
        }
    }
    
    return canMove;
}
bool Pacman::check_move_down(){
    if(counter==total_food){
        isRunning = false;
    }
    if(lives==0){
        isRunning2 = false;
    }
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
            else if(i==y/25 & j==x/25 & c=='.'){
                canMove=true;
                *(grid+i*grid_w + j) = ' ';   //replaced
                counter++;
                break;
            }
            else if(i==y/25 & j==x/25 & c==','){
                canMove=true;
                power = true;
                time(&begin);
                *(grid+i*grid_w + j) = ' ';//replaced
                counter++;
                break;
            }
            else if(i==y/25 & j==x/25 & c==' '){
                canMove=true;
                break;
            }
        }
    }
    
    return canMove;
} 
int Pacman::etime(){
    time(&en);
    //std::cout<<en<<"/"<<begin<<endl;
    int e = en - begin;
    return e;
}
bool Pacman::check_move_up(){
    if(counter==total_food){
        isRunning = false;
    }
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
            else if(i==y/25 & j==x/25 & c=='.'){
                canMove=true;
                *(grid+i*grid_w + j) = ' ';//replaced
                counter++;
                break;
            }
            else if(i==y/25 & j==x/25 & c==','){
                canMove=true;
                power = true;
                time(&begin);
                *(grid+i*grid_w + j) = ' ';//replaced
                counter++;
                break;
            }
            else if(i==y/25 & j==x/25 & c==' '){
                canMove=true;
                break;
            }
        }
    }
    
    return canMove;
} 

void Pacman::animate(){
   
    come_back=true;
    moverRect.x+=10;
}

SDL_Rect Pacman :: move_pac_right(){    //changes the image of pacman depending on its direction
    srcRect = {125,338,52,54};
    moverRect.x += 25;
    return moverRect;
}

SDL_Rect Pacman :: move_pac_left(){
    srcRect = {199,337,50,55};
    moverRect.x -= 25;
    return moverRect;
}

SDL_Rect Pacman :: move_pac_up(){
    srcRect = {279,338,56,54};
    moverRect.y -= 25;
    return moverRect;
    
    
}

SDL_Rect Pacman :: move_pac_down(){
    srcRect = {361,338,58,52};
    moverRect.y += 25;
    return moverRect;
}

SDL_Rect* Pacman:: getMover(){
    return &moverRect;
}

/*Pacman::Pacman(char* grid_, int gridw, int gridh) {
    srcRect = {279,67,99,106};
    grid = grid_;
    grid_w = gridw;
    grid_h = gridh;
    moverRect = {50, 100, 25, 25};
    
}*/
Pacman::Pacman(char* grid_, int gridw, int gridh){
    srcRect = { 279,67,99,106 };
    grid = grid_;
    grid_w = gridw;
    grid_h = gridh;
    moverRect = { 50, 100, 25, 25 };
}
Pacman::Pacman(const Pacman& ob){}
Pacman* Pacman::get_instance(char* grid_, int gridw, int gridh) {
    static Pacman* instance = new Pacman(grid_, gridw, gridh);
    return instance;
}