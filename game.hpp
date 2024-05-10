
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <SDL_mixer.h>
#include <fstream>
#include <string>
#pragma once
using namespace std;



class Game{
    protected:
    //Screen dimension constants
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    Mix_Music *gMusic = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;
    SDL_Surface *screen = NULL;

    char* grid;
    int num;
    string path;
    std::fstream file;
    const int grid_w = 40;
    const int grid_h = 24;
    
    

public:
    bool blit_called;
    int count;
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path);
    SDL_Texture* get_gTexture();
    SDL_Rect* getMover();
    void run();
    void blit();
    void PopulateGrid();
};

