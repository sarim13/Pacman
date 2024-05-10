#include "game.hpp"
#include "Pacmania.hpp"
#include "map.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void Game::PopulateGrid(){           //reads the map text file and stores all the characters in an array
	grid = new char[grid_w*grid_h];
	//map ns;
	//ns.genMap();
	srand(time(0));
	num = rand() % 3;
	cout << num;
	if (num == 0) {
		ifstream fin("map.txt", std::ios::in);
		path = "map.txt";
	}
	else if (num == 1) {
		ifstream fin("map1.txt", std::ios::in);
		path = "map1.txt";
	}
	else {
		ifstream fin("map2.txt", std::ios::in);
		path = "map2.txt";
	}
	// Open the file and check if successful
	file.open(path.c_str(), std::ios::in);

	string line;
	int x = 0;
	while (getline(file, line)) {
		vector<char> chars(line.begin(), line.end());
		for (unsigned int y = 0; y < chars.size(); y++){
			grid[x] = chars[y];
			x++;
		}
	}
	file.close();
}


void Game::blit(){                                 // goes through the array and displays the map
		screen = SDL_GetWindowSurface(gWindow);
		SDL_Surface* wallImage = NULL;
		SDL_Surface* pwup = NULL;
	    SDL_Surface* foodImage = NULL;
		wallImage = SDL_LoadBMP( "wall.bmp" );
		pwup = SDL_LoadBMP("powerup.bmp");
        foodImage = SDL_LoadBMP( "point.bmp" );
		SDL_Rect srect= {0,0,25,25};
		SDL_Rect drect = wallImage->clip_rect;
		int x = 0;
		char c;
		count = 0;
		for(int i = 0; i < grid_h; i++){
		    for(int j = 0; j<grid_w; j++){
				c = *(grid+i*grid_w + j);
				switch (c)
					{
						case 'x':
							SDL_BlitSurface(wallImage, NULL, screen, &drect );
							break;
						case '.':
							SDL_BlitSurface(foodImage, NULL, screen, &drect );
							count += 1;
							break;	
						case ',':
							SDL_BlitSurface(pwup, NULL, screen, &drect);
							count += 1;
							break;
					}
				drect.x+=25;
			}
			drect.x=0;
			drect.y+=25;
		}
			blit_called = true;
			gTexture = SDL_CreateTextureFromSurface( gRenderer, screen);
			SDL_FreeSurface( screen );	
}

bool Game::init()
{
	PopulateGrid();   //populates our map grid
	//Initialization flag
	bool success = true;
	blit_called = false;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		
		gWindow = SDL_CreateWindow( "Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		


		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	bool success = true;
	assets = loadTexture("assets.png");
    gTexture = loadTexture("start.png");
	if(assets==NULL || gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	gMusic = Mix_LoadMUS( "bg_music.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
	
	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_FreeMusic( gMusic );
    gMusic = NULL;
	Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}


void Game::run( )
{
	bool quit=false;
	SDL_Event e;
	char direction = 's';
	char direction2 = 's';
	Pacmania pacmania(gRenderer, assets, grid, grid_w, grid_h);
	Mix_PlayMusic(gMusic, -1);
	while( !quit )
	{	
		if(pacmania.p->lives==0){
			// for(Ghost* g: pacmania.ghosts)delete g;
			gTexture = loadTexture("end.png");
			
		}
		else if(pacmania.p->isRunning==false){
			// for(Ghost* g: pacmania.ghosts)delete g;
			gTexture = loadTexture("gamewin.png");
			
		}
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			if(e.type == SDL_MOUSEBUTTONDOWN){
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse,&yMouse);
				pacmania.createObject(xMouse, yMouse);
				if (xMouse>40 && xMouse<315 && yMouse>250 && yMouse<370) blit();
			}
			else if (e.type = SDL_KEYDOWN){
				if (e.key.keysym.sym== SDLK_RIGHT){
					direction = 'r';
				}
				else if (e.key.keysym.sym== SDLK_LEFT){
					direction = 'l';
				}
				else if (e.key.keysym.sym== SDLK_UP){
					direction = 'u';
				}
				else if (e.key.keysym.sym== SDLK_DOWN){
					direction = 'd';
				}
			}
		}

		
		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
		//***********************draw the objects here********************
		if(blit_called ==false) pacmania.drawObjects();
		else if (pacmania.p->lives>0 && pacmania.p->isRunning==true){
			// cout<<pacmania.p->lives<<endl;
			pacmania.drawGhosts();
			pacmania.drawPacman(count);
			
			switch (direction){
			case 'r':
				if(pacmania.can_move_right()==true){
					SDL_Surface* wallImage = NULL;
					wallImage = IMG_Load("black.png");
					SDL_Rect rects = {0,0,25,25};
					SDL_Rect rect=pacmania.move_right();
					rect.x-=25;
					SDL_BlitSurface(wallImage, &rects, screen, &rect );
					gTexture = SDL_CreateTextureFromSurface( gRenderer, screen);
					SDL_FreeSurface( screen );
				}
				break;
			case 'l':
				if(pacmania.can_move_left()==true){
					SDL_Surface* wallImage = NULL;
					wallImage = IMG_Load("black.png");
					SDL_Rect rects = {0,0,25,25};
					SDL_Rect rect=pacmania.move_left();
					rect.x+=25;
					SDL_BlitSurface(wallImage, &rects, screen, &rect );
					gTexture = SDL_CreateTextureFromSurface( gRenderer, screen);
					SDL_FreeSurface( screen );
				}
				break;
			case 'u':
				if(pacmania.can_move_up()==true){
					SDL_Surface* wallImage = NULL;
					wallImage = IMG_Load("black.png");
					SDL_Rect rects = {0,0,25,25};
					SDL_Rect rect=pacmania.move_up();
					rect.y+=25;
					SDL_BlitSurface(wallImage, &rects, screen, &rect );
					gTexture = SDL_CreateTextureFromSurface( gRenderer, screen);
					SDL_FreeSurface( screen );
				}
				break;
			case 'd':
				if(pacmania.can_move_down()==true){
					SDL_Surface* wallImage = NULL;
					wallImage = IMG_Load("black.png");
					SDL_Rect rects = {0,0,25,25};
					SDL_Rect rect=pacmania.move_down();
					rect.y-=25;
					SDL_BlitSurface(wallImage, &rects, screen, &rect );
					gTexture = SDL_CreateTextureFromSurface( gRenderer, screen);
					SDL_FreeSurface( screen );
				}
				break;}
		}
		
		SDL_RenderPresent(gRenderer);

		//****************************************************************
    	 //displays the updated renderer

	    SDL_Delay(120);	//causes sdl engine to delay for specified miliseconds
	}
			
}

SDL_Texture* Game::get_gTexture(){
	return gTexture;
}
