#include "button.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


void Button::draw(SDL_Renderer* gRenderer, SDL_Texture* assets){
    SDL_RenderCopy(gRenderer, assets, &srcRect, &moverRect);
    if (come_back){
        moverRect.x-=10;
        come_back=false; 
    }
}
void Button::animate(){
    come_back=true;
    moverRect.x+=10;
}

Button::Button(){
    // srcRect = {7,28,782,291};
    // moverRect = {40, 250, 275, 120};
}