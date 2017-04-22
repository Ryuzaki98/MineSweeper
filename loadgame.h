#ifndef LOADGAME_H
#define LOADGAME_H

#include <iostream>
#include<SDL.h>
#include"prepair.h"
#include<SDL_image.h>
#include<time.h>
#include<conio.h>
#include<fstream>
#include<SDL_ttf.h>

using namespace std;




void Washy(int x, int y ,int row ,int column);

void AlphaBuild( int &row, int &column, int &numberMine);

void BetaBuild(int &row, int &column);

bool runninggame( SDL_Renderer *&renderer,SDL_Window * & windown);

bool startgame(SDL_Renderer *&renderer, SDL_Window *&windown);

#endif // LOADGAME_H
