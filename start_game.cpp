#include "start_game.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


void Start_Game::draw(SDL_Renderer* gRenderer, SDL_Texture* assets){
    SDL_RenderCopy(gRenderer, assets, &srcRect, &moverRect);
    if (come_back){
        moverRect.x-=10;
        come_back=false; 
    }
}
void Start_Game::animate(){
    come_back=true;
    moverRect.x+=10;
}

Start_Game::Start_Game(){
    srcRect = {116,218,267,92};
    moverRect = {40, 250, 275, 120};
}