#ifndef PREPAIR_H
#define PREPAIR_H
#include<SDL.h>
#include<iostream>
#include<cstring>
#include<SDL_image.h>
#include<SDL_ttf.h>

//mau sao
const SDL_Color CYAN = {0,255,255};
const SDL_Color BLUE = {0,0,255};
const SDL_Color ORANGE = {255,165,0};
const SDL_Color YELLOW = {255,255,0};
const SDL_Color LIME = {0,255,0};
const SDL_Color PURPLE = {128,0,128};
const SDL_Color RED = {255,0,0};
const SDL_Color WHITE = {255,255,255};
const SDL_Color BLACK = {0,0,0};
const SDL_Color GREEN = {0,128,0};






using namespace std;


void waitUntilKeyPressed();

void quitSDL(SDL_Window* &windown, SDL_Renderer* &renderer);

void initSDL(SDL_Window* &windown, SDL_Renderer* &renderer);

void loadMapLeft(int x,int y, int number, SDL_Renderer * &renderer);

void loadMapRight(int x,int y,SDL_Renderer * &renderer);

void loadIMG( string path, int x,int y, int w, int h ,SDL_Renderer* &renderer);

void loadBackgrond(SDL_Renderer * &renderer);

void loadMenu(SDL_Renderer * &renderer,SDL_Rect *& rectstart, SDL_Rect* &rectexit);

bool chooseMenu(SDL_Renderer *&renderer,int &mouseX,int &mouseY,SDL_Rect *&rect);

int HighestScore();

void saveScore(const int score);

string IntToString(int number);

#endif // PREPAIR_H
