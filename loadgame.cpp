#include "loadgame.h"
#include <iostream>
#include<SDL.h>
#include"prepair.h"
#include<SDL_image.h>
#include<time.h>
#include<conio.h>
#include<fstream>
#include<SDL_ttf.h>


TTF_Font *font              = nullptr;
SDL_Surface * dominSurface  = nullptr;
SDL_Texture * dominTexture  =nullptr;
SDL_Rect * dominRect        = new SDL_Rect;
SDL_Surface * levelSurface  = nullptr;
SDL_Texture * levelTexture  =nullptr;
SDL_Rect * levelRect        = new SDL_Rect;
SDL_Surface * highSurface   = nullptr;
SDL_Texture * highTexture   =nullptr;
SDL_Rect * highRect         = new SDL_Rect;
SDL_Surface * mineSurface   = nullptr;
SDL_Texture * mineTexture   =nullptr;
SDL_Rect * mineRect         = new SDL_Rect;
SDL_Rect * rectstart        = new SDL_Rect;
SDL_Rect* rectexit          = new SDL_Rect;


static int row              =9;
static int column           =9;
static int numberMine;
int a[100][100]             ={0};
int Op[100][100]            ={0};
int d                       =0;




void AlphaBuild(  int &row,int &column, int &numberMine)
{
	int couting = 0 ;
	srand( time (0)) ;
	while ( couting < numberMine)
	{
		couting ++ ;
		int randomx = rand() % column +1  ;
		int randomy = rand() % row +1 ;
		if ( a[randomx] [randomy] != -1 ) a[randomx][randomy] = -1 ;
		else couting -- ;
	}
}
void BetaBuild(int &row, int &column)
{
	int couting = 0 ;
	// check [1][1]
	if ( a[1][1] == 0 )
	{
		if (a[1][2]            == -1 ) couting+=1;
		if (a[2][2]            == -1 ) couting+=1;
		if (a[2][1]            == -1 ) couting+=1;
		a[1][1]                = couting ;
		couting                = 0;
	}
	// check [1][Column]
	if ( a[1][column] == 0 )
	{
		if (a[1][column-1]      == -1 ) couting+=1;
		if (a[2][column]        == -1 ) couting+=1;
		if (a[2][column - 1]    == -1 ) couting+=1;
		a[1][column]            = couting ;
		couting                 = 0;
	}
	//check [row][1]
	if ( a[row][1] == 0 )
	{
		if (a[row][2]           == -1 ) couting+=1;
		if (a[row-1][2]         == -1 ) couting+=1;
		if (a[row-1][1]         == -1 ) couting+=1;
		a[row][1]               = couting ;
		couting                 = 0;
	}
	// check [row][column]
	if ( a[row][column] == 0 )
	{
		if (a[row][column -1]   == -1 ) couting+=1;
		if (a[row -1][column -1]== -1 ) couting+=1;
		if (a[row -1][column]   == -1 ) couting+=1;
		a[row][column]          = couting ;
		couting                 = 0;
	}
	// check [1][2]-> a[1][column -1]  && [row][2] -> [row][column-1]
	for ( int i = 2 ; i < column ; i ++ )
	{
		if ( a[1][i] == 0 )
		{
			couting = 0;
			if (a[1][i-1]       == -1 ) couting+=1;
			if (a[1][i + 1]     == -1 ) couting+=1;
			if (a[2][i-1]       == -1 ) couting+=1;
			if (a[2][i]         == -1 ) couting+=1;
			if (a[2][i+1]       == -1 ) couting+=1;
			a[1][i]             = couting ;
		}
		if ( a[row][i] == 0 )
		{
			couting = 0;
			if (a[row][i-1]     == -1 ) couting+=1;
			if (a[row][i + 1]   == -1 ) couting+=1;
			if (a[row -1][i-1]  == -1 ) couting+=1;
			if (a[row -1][i]    == -1 ) couting+=1;
			if (a[row-1][i+1]   == -1 ) couting+=1;
			a[row][i]           = couting ;
		}
	}
	// check hang doc cot 1 va column
	for ( int i = 2 ; i < row ; i ++ )
	{
		if ( a[i][1] == 0 )
		{
			couting = 0;
			if (a[i-1][1]       == -1 ) couting+=1;
			if (a[i+1][1]       == -1 ) couting+=1;
			if (a[i-1][2]       == -1 ) couting+=1;
			if (a[i][2]         == -1 ) couting+=1;
			if (a[i+1][2]       == -1 ) couting+=1;
			a[i][1]             = couting ;
		}
		if ( a[i][column] == 0 )
		{
			couting = 0;
			if (a[i-1][column]  == -1 ) couting+=1;
			if (a[i+1][column]  == -1 ) couting+=1;
			if (a[i-1][column-1]== -1 ) couting+=1;
			if (a[i][column-1]  == -1 ) couting+=1;
			if (a[i+1][column-1]== -1 ) couting+=1;
			a[i][column]        = couting ;
		}
	}
	// check o con lai
	for (int i = 2; i< row ; i++)
	for (int j = 2 ; j < column ; j++)
	if (a[i][j] != -1)
	{
		couting = 0 ;
		if ( a[i-1][j]          == -1) couting ++;
		if ( a[i-1][j-1]        == -1) couting ++;
		if ( a[i-1][j+1]        == -1) couting ++;
		if ( a[i][j-1]          == -1) couting ++;
		if ( a[i][j+1]          == -1) couting ++;
		if ( a[i+1][j-1]        == -1) couting ++;
		if ( a[i+1][j]          == -1) couting ++;
		if ( a[i+1][j+1]        == -1) couting ++;
		a[i][j]= couting ;
	}
}
// loang
void Washy(int x, int y ,int row , int column)
{
	Op[x][y] = 1;
	d=d+1;
	if (a[x+1][y] > 0 && x + 1 <= row && y <= column && Op[x+1][y]== 0 )
	{
		Op[x+1][y] = 1;
		d=d+1;
	}
	if (a[x+1][y-1] >0  && x + 1 <= row && y-1 >=1  && Op[x+1][y-1]== 0)
	{
		Op[x+1][y-1] = 1;
		d=d+1;
	}
	if (a[x+1][y+1] >0 && x + 1 <= row && y + 1 <= column  && Op[x+1][y+1]== 0)
	{
		Op[x+1][y+1] = 1;
		d=d+1;
	}
	if (a[x][y+1] >0 && x <= row && y +1 <= column  && Op[x][y+1]== 0)
	{
		Op[x][y+1] = 1;
		d=d+1;
	}
	if (a[x][y-1] >0 && x  <= row && y -1 >=1  && Op[x][y-1]== 0)
	{
		Op[x][y-1] = 1;
		d=d+1;
	}
	if (a[x-1][y-1] >0 && x - 1 >=1 && y-1 >=1  && Op[x-1][y-1]== 0)
	{
		Op[x-1][y-1] = 1;
		d=d+1;
	}
	if (a[x-1][y] >0 && x - 1 >=1 && y <= column  && Op[x-1][y]== 0)
	{
		Op[x-1][y] = 1;
		d=d+1;
	}
	if (a[x-1][y+1] >0 && x - 1 >=1  && y +1 <= column  && Op[x-1][y+1]== 0)
	{
		Op[x-1][y+1] = 1;
		d=d+1;
	}

	if (a[x+1][y] == 0  && x + 1 <= row && y <= column && Op[x+1][y]== 0) Washy(x+1 , y ,row , column  );
	if (a[x+1][y+1] == 0  && x + 1 <= row && y + 1 <= column && Op[x+1][y+1]== 0) Washy(x+1 , y+1 ,row , column  );
	if (a[x+1][y-1] == 0  && x + 1 <= row && y-1 >= 1 && Op[x+1][y-1]== 0)  Washy(x+1 , y-1 ,row , column  );
	if (a[x][y-1] == 0  && x  <= row && y -1  >= 1 && Op[x][y-1]== 0) Washy(x , y-1 ,row , column);
	if (a[x][y+1] == 0  && x  <= row && y + 1<= column && Op[x][y+1]== 0) Washy(x , y+1 ,row , column  );
	if (a[x-1][y-1] == 0  && x-1 >=1  && y -1 >= 1  && Op[x-1][y-1]== 0) Washy(x-1 , y-1 ,row , column  );
	if (a[x-1][y] == 0  && x -1 >=1 && y <= column && Op[x-1][y]== 0) Washy(x-1 , y ,row , column  );
	if (a[x-1][y+1] == 0  && x -1 >= 1 && y +1 <= column && Op[x-1][y+1]== 0) Washy(x-1 , y+1 ,row , column  );
}

bool runninggame( SDL_Renderer *&renderer,SDL_Window * & windown)
{

    levelSurface=new SDL_Surface;
    levelRect->x=30;
    levelRect->y=60;
    levelRect->h= 100;
    levelRect->w=200;
    highSurface=new SDL_Surface;
    highRect->x=30;
    highRect->y=0;
    highRect->h= 100;
    highRect->w=200;
    mineSurface=new SDL_Surface;
    mineRect->x=300;
    mineRect->y=0;
    mineRect->h= 100;
    mineRect->w=200;

    while (true)
    {
        SDL_RenderClear(renderer);
        loadBackgrond(renderer);
        string levelht= "Level : "+ IntToString(9-row+1);
        levelSurface=TTF_RenderText_Solid(font,levelht.c_str(),BLUE);
        levelTexture=SDL_CreateTextureFromSurface(renderer,levelSurface);
        SDL_RenderCopy(renderer,levelTexture,NULL,levelRect);
        string highht= "HIGHSCORE : "+ IntToString(HighestScore());
        highSurface=TTF_RenderText_Solid(font,highht.c_str(),RED);
        highTexture= SDL_CreateTextureFromSurface(renderer,highSurface);
        SDL_RenderCopy(renderer,highTexture,NULL,highRect);

        row --;
        column --;
        numberMine =row;
        string mine ="NumberMine : " + IntToString(numberMine);
        mineSurface= TTF_RenderText_Solid(font,mine.c_str(),YELLOW);
        mineTexture= SDL_CreateTextureFromSurface(renderer,mineSurface);
        SDL_RenderCopy(renderer,mineTexture,NULL,mineRect);
        int i=0,j=0,safe = row * column- numberMine;
        for ( i=1;i<=row; i++)
            for (j=1;j<=column;j++)
            {
                a[i][j]=0;
                Op[i][j]=0;
            }
        AlphaBuild(row,column,numberMine);
        BetaBuild(row,column);
        for (i=1;i<=row;i++)
            for (j=1;j<=column;j++) loadMapLeft(210+21*i,210+21*j,-2,renderer);
        SDL_RenderPresent(renderer);
            // lay chuot va xu li =.=

        SDL_Event event;
        while (true)
        {
            SDL_WaitEvent(&event);
            if (event.type == SDL_QUIT || ( safe<=0)) return false;
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX = event.button.x-210;
                int mouseY = event.button.y-210;
                if (mouseX <= 21+column*20 && mouseX>=21 && mouseY <=21+row*20 && mouseY>=21 && Op[mouseY/21][mouseX/21]==0)
                {
                    while (mouseX% 21 != 0) mouseX-- ;
                    while (mouseY % 21 != 0) mouseY-- ;
                    if (event.button.button == SDL_BUTTON_RIGHT) loadMapRight(mouseX+210,mouseY+210,renderer);
                    if (event.button.button == SDL_BUTTON_LEFT )
                    {

                        if (a[(int) (mouseY/21)][(int) (mouseX/21)]==0)
                        {
                            d=0;
                            Washy(mouseY/21,mouseX/21,row,column);
                            safe=safe -d ;
                            if (safe==0) return true;
                            for (i=1;i<=row;i++)
                                for (j=1;j<=column;j++)
                                    if (Op[i][j]==1) loadMapLeft(21*j+210,21*i+210,a[i][j],renderer);
                        }
                        else if (a[(int) (mouseY/21)][(int) (mouseX/21)] == -1)
                        {

                            for (i=1;i<=row;i++)
                                for (j=1;j<=column;j++)
                                    loadMapLeft(21*j+210,210+21*i,a[i][j],renderer);
                                    SDL_RenderPresent(renderer);

                                    if (8-row+1> HighestScore()) saveScore(8-row+1);
                                    SDL_Delay(3000);
                                    loadIMG("data/gameover.png",0,0,600,600,renderer);
                                    SDL_RenderPresent(renderer);
                                    SDL_Delay(2000);
                                    delete(mineRect);
                                    delete(mineSurface);
                                    delete(highRect);
                                    delete(highSurface);
                                    delete(levelRect);
                                    delete(levelSurface);
                                    return false;
                        }
                        else
                        {
                            loadMapLeft(mouseX+210,mouseY+210,a[(int) (mouseY/21)][(int) (mouseX/21)],renderer);
                            Op[(int) (mouseY/21)][(int) (mouseX/21)]=1;
                            safe--;
                            if (row==1)
                            {
                                //load pha dao
                                SDL_Rect * phadao=new SDL_Rect;
                                phadao->x=phadao->y=0;
                                phadao->w=phadao->h=600;
                                SDL_Texture* phadaotexture= nullptr;
                                phadaotexture= IMG_LoadTexture(renderer,"data/genius.jgp");
                                SDL_RenderCopy(renderer,phadaotexture,NULL,phadao);
                                SDL_RenderPresent(renderer);
                                if (8-row+1> HighestScore()) saveScore(8-row+1);
                                delete(mineRect);
                                delete(mineSurface);
                                delete(highRect);
                                delete(highSurface);
                                delete(levelRect);
                                delete(levelSurface);
                                delete(phadao);
                                return false;
                            }

                            if (safe==0)
                            {
                                if (8-row+1> HighestScore()) saveScore(8-row+1);
                                return true;
                            }
                        }
                    }
                    SDL_RenderPresent(renderer);

                }
            }


        }
    }

}

bool startgame(SDL_Renderer *&renderer, SDL_Window *&windown)
{
    initSDL(windown,renderer);
    //khoi tao man hinh start
    loadBackgrond(renderer);

    rectstart->x=150;
    rectstart->y =200;
    rectstart->w=300;
    rectstart->h=100;
    rectexit->x=150;
    rectexit->y =350;
    rectexit->w=300;
    rectexit->h=100;
    loadMenu(renderer,rectstart,rectexit);
    dominRect->x=150;
    dominRect->y=60;
    dominRect->h= 100;
    dominRect->w=300;
    TTF_Init();

    font = TTF_OpenFont("data/fontchu.TTF", 20);
    dominSurface=new SDL_Surface;
    dominSurface=TTF_RenderText_Solid(font,"NewMineSweeper",RED);
    dominTexture=SDL_CreateTextureFromSurface(renderer,dominSurface);
    SDL_RenderCopy(renderer,dominTexture,NULL,dominRect);

    SDL_RenderPresent(renderer);

    while (true)
    {

        SDL_Event eventst;
        SDL_WaitEvent(&eventst);
        if (eventst.type== SDL_QUIT)
        {
            delete(rectexit);
            delete(rectstart);
            delete(dominSurface);
            //delete(dominTexture);
            delete(dominRect);
            quitSDL(windown,renderer);
            return false;
        }
        else if (eventst.type== SDL_MOUSEBUTTONDOWN)
        {
            int mouseX = eventst.button.x;
            int mouseY  = eventst.button.y;
            if (chooseMenu(renderer,mouseX,mouseY,rectexit)== true)
            {
                delete(rectexit);
                delete(rectstart);
                delete(dominSurface);
                //delete(dominTexture);
                delete(dominRect);
                quitSDL(windown,renderer);
                return false;
            }
            if (chooseMenu(renderer,mouseX,mouseY,rectstart)== true)

            {
                delete(rectexit);
                delete(rectstart);
                delete(dominSurface);
                //delete(dominTexture);
                delete(dominRect);
                return true;
            }

        }

    }
}
