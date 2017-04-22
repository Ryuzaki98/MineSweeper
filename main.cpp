#include <iostream>
#include<SDL.h>
#include"prepair.h"
#include<SDL_image.h>
#include<time.h>
#include "loadgame.h"
#include<conio.h>
#include<fstream>
#include<SDL_ttf.h>

SDL_Window * windown;
SDL_Renderer * renderer;


using namespace std;

int main(int argc, char * argv[])
{
    if (startgame(renderer,windown)== true)
        while (runninggame(renderer,windown));
    quitSDL(windown,renderer);
    return 0;
}
