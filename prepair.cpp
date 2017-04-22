#include "prepair.h"
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<fstream>
#include<sstream>

using namespace std;



void initSDL(SDL_Window* &windown, SDL_Renderer* &renderer)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    windown = SDL_CreateWindow(" __RYUZAKI__TOBIICHI__ORIGAMI__",SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, 600 , 600, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(windown, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_RenderSetLogicalSize(renderer, 600, 600);
}

void quitSDL(SDL_Window* &windown, SDL_Renderer* &renderer)
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(windown);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 && ( e.type == SDL_QUIT) )
            return ;

    }
}

void loadIMG(std :: string path, int x,int y, int w, int h ,SDL_Renderer* &renderer)
{
    SDL_Rect *rect = nullptr;
    rect = new SDL_Rect ;
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    SDL_Texture * img= nullptr;
    img     =  IMG_LoadTexture(renderer,path.c_str());
    SDL_RenderCopy(renderer, img, NULL, rect);


}

void loadMapLeft(int x,int y, int number, SDL_Renderer * &renderer)
{
    switch (number)
    {
        case -1 : loadIMG("data/img_bom.png",x,y,20,20,renderer); break;
        case  -2 : loadIMG("data/img_cell.png",x,y,20,20,renderer); break;
        case  0 : loadIMG("data/img_poit9.png",x,y,20,20,renderer); break;
        case  1 : loadIMG("data/img_poit1.png",x,y,20,20,renderer); break;
        case  2 : loadIMG("data/img_poit2.png",x,y,20,20,renderer); break;
        case  3 : loadIMG("data/img_poit3.png",x,y,20,20,renderer); break;
        case  4 : loadIMG("data/img_poit4.png",x,y,20,20,renderer); break;
        case  5 : loadIMG("data/img_poit5.png",x,y,20,20,renderer); break;
        case  6 : loadIMG("data/img_poit6.png",x,y,20,20,renderer); break;
        case  7 : loadIMG("data/img_poit7.png",x,y,20,20,renderer); break;
        case  8 : loadIMG("data/img_poit8.png",x,y,20,20,renderer); break;
    }

}
void loadMapRight(int x,int y,SDL_Renderer * &renderer)
{
    loadIMG("data/co.png",x,y,20,20,renderer);
}
void loadBackgrond(SDL_Renderer *& renderer)
{
    SDL_Rect * rect = nullptr;
    rect= new SDL_Rect;
    rect->x= 0;
    rect->y=0;
    rect->h=600;
    rect->w=600;
    SDL_Texture * imagebg = nullptr;
    imagebg= IMG_LoadTexture(renderer,"data/bgr.png");
    SDL_RenderCopy(renderer,imagebg,NULL,rect);
}
void loadMenu(SDL_Renderer * &renderer,SDL_Rect *& rectstart, SDL_Rect* &rectexit)
{
    SDL_Texture * images = nullptr;
    images= IMG_LoadTexture(renderer,"data/start.png");
    SDL_RenderCopy(renderer,images,NULL,rectstart);
    SDL_Texture * imagee = nullptr;
    imagee= IMG_LoadTexture(renderer,"data/exit.png");
    SDL_RenderCopy(renderer,imagee,NULL,rectexit);
}

bool chooseMenu(SDL_Renderer *&renderer,int &mouseX,int &mouseY,SDL_Rect *&rect)
{
    if ((mouseX<rect->x) || (mouseX >rect->x+rect->w)) return false;
    if ((mouseY<rect->y) || (mouseY >rect->y+rect->h)) return false;
    return true;
}


int HighestScore()
{
    int highestScore;
    ifstream infile("data/score.txt");
    if (infile.is_open())
    {
        infile >> highestScore;
    }
    else cout << "Unable to open data file" << endl;
    return highestScore;
}

void saveScore(const int score)
{
    ofstream oufile("data/score.txt");
    if (oufile.is_open())
    {
        oufile << score;
    }
    else cout << "Unable to open data file" << endl;
}
string IntToString(int number)
{
    stringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}
