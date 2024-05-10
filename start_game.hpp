#include<SDL.h>
#include <string>
#include <vector>
#include <fstream>
#include "button.hpp"
#pragma once

class Start_Game : public Button{
//SDL_Rect srcRect, moverRect;
//bool come_back=false;
public:
    void draw(SDL_Renderer*, SDL_Texture* assets);
    void animate();
    Start_Game(); // may add other overloaded constructors here... 
};
