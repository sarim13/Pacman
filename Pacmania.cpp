#include<iostream> 
#include "Pacmania.hpp"
#include "game.hpp"

bool Pacmania::checkCollision(Ghost* ghost, Pacman& p){
    return SDL_HasIntersection(ghost->getMover(),p.getMover());
}

void Pacmania::drawObjects(){
    p1->draw(gRenderer, assets);
    p2->draw(gRenderer, assets);
    
}
void Pacmania::drawPacman(int count){
    p -> draw(gRenderer, assets);
    p->total_food = count;
}
void Pacmania::addGhosts(){
    for(int i =0;i<4;i++){
        Ghost* ghost = new Ghost(i, grid, grid_w, grid_h);
        ghosts.push_back(ghost);
    }
}
void Pacmania::drawGhosts(){
    int a;
    for(Ghost* ghost: ghosts){
        a = p->etime();
        if (a>9){
            p->power = false;
        }
        if(ghost->changeDirection != false){
            char arr[4]={'u','d','l','r'};
            int random_no = rand() % 4;
            ghost->direction2 = arr[random_no];
            ghost->changeDirection = false;
        }
        if((checkCollision(ghost,*p)==false)){
            if (p->power == false){
                moveGhost(ghost);
            }
        }
        else{
            p->moverRect.x = 50;
            p->moverRect.y = 100;
            p->lives --;
        }
        ghost->draw(gRenderer, assets);
    }
}

void Pacmania::moveGhost(Ghost* ghost){
        switch(ghost->direction2){
            case 'u':
                if(ghost->check_move_up()==true){
                    ghost->moverRect.y-=25;
                }
                else{
                    ghost->changeDirection = true;
                }
                break;
            case 'd':
                if(ghost->check_move_down()==true)ghost->moverRect.y+=25;
                else{
                    ghost->changeDirection = true;
                }
                break;
            case 'l':
                if(ghost->check_move_left()==true)ghost->moverRect.x-=25;
                else{
                    ghost->changeDirection = true;
                }
                break;
            case 'r':
                if(ghost->check_move_right()==true)ghost->moverRect.x+=25;
                else{
                    ghost->changeDirection = true;
                }
                break;
    }
    
    
}
bool Pacmania::can_move_right(){   //redirects these functions to the pacman class
    p->check_move_right(); 
}
bool Pacmania::can_move_left(){
    p->check_move_left();
}
bool Pacmania::can_move_up(){
    p->check_move_up();
}
bool Pacmania::can_move_down(){
    p->check_move_down();
}

SDL_Rect Pacmania :: move_right(){
    SDL_Rect rect = p->move_pac_right();
    return rect;
}
SDL_Rect Pacmania :: move_left(){
    SDL_Rect rect = p->move_pac_left();
    return rect;
}
SDL_Rect Pacmania :: move_up(){
    SDL_Rect rect = p->move_pac_up();
    return rect;
}
SDL_Rect Pacmania :: move_down(){
    SDL_Rect rect = p->move_pac_down();
    return rect;
}



void Pacmania::createObject(int x, int y){      
    if (x>40 && x<315 && y>250 && y<370){
        p1->animate();
    }
    if (x>675 && x<950 && y>250 && y<370){
        p2->animate();
        g.close();
        
    }
    
}

Pacmania::Pacmania(SDL_Renderer *renderer, SDL_Texture *asst, char* grid_, const int grid_width, const int grid_height):gRenderer(renderer), assets(asst){
    grid_w = grid_width;
    grid_h = grid_height;
    grid = grid_;
    //p = new Pacman(grid_, grid_width, grid_height);
    p = p->get_instance(grid_, grid_width, grid_height) ;
    addGhosts();
    cout<<ghosts.size()<<endl;  
}
