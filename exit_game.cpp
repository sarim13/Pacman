#include "exit_game.hpp"

void Exit_Game::draw(SDL_Renderer* gRenderer, SDL_Texture* assets){
    
        SDL_RenderCopy(gRenderer, assets, &srcRect, &moverRect);
    if (come_back){
        moverRect.x-=10;
        come_back=false; 
    }
}

void Exit_Game::animate(){
    come_back=true;
    moverRect.x+=10;
}

Exit_Game::Exit_Game(){
    srcRect = {499,218,275,97};
    moverRect = {675, 250, 275, 120};
}