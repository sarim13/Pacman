#include<SDL.h>
#include"button.hpp"

class Exit_Game : public Button{
// SDL_Rect srcRect, moverRect;
// bool come_back = false;
public:
    void draw(SDL_Renderer*, SDL_Texture* assets);
    void animate();
    Exit_Game(); // may add other overloaded constructors here... 
};