//File: DrawFishingPole.cpp
//Author:   John Miner
//Created:  09/06/11
//Modified: 09/06/11
//Purpose:  Experiment with drawing a pole.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <SDL/SDL.h>
#include <cmath>
#include "../Header/Point.hpp"
#include "../Header/Math.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const Point polePoint = { 400, 300 };
SDL_Surface *initSDL();
void createSurfaces(SDL_Surface **pole);
void freeSurfaces(SDL_Surface *screen, SDL_Surface *pole);
void handleInput(bool &quit, Point &hookPoint);
void drawPole(SDL_Surface *screen, SDL_Surface **pole, const Point &polePoint,
    const Point &hookPoint);
double howBowed(const Point &polePoint, const Point &hookPoint);
double calculateQuadratic(double a, double b, double c);
double greater(double number1, double number2);
double lesser(double number1, double number2);
void drawGame(SDL_Surface **screen, SDL_Surface **pole,
    const Point &polePoint, const Point &hookPoint);
void clearSurfaces(SDL_Surface **screen, SDL_Surface **pole);

int main(int argc, char **argv)
{
    Point hookPoint = { 400, 450 };
    SDL_Surface *screen = initSDL();
    SDL_Surface *pole = NULL;
    bool quit = false;

    createSurfaces(&pole);
    
    while( quit == false)
    {
        drawGame(&screen, &pole, polePoint, hookPoint);
        handleInput(quit, hookPoint);
    }

    freeSurfaces(screen, pole);

    return EXIT_SUCCESS;
}

SDL_Surface *initSDL()
{
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    return SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
        SDL_HWSURFACE);
}

void createSurfaces(SDL_Surface **pole)
{
    //SDL_Surface *tmp
    *pole = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA,
        SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0, 0, 0, 0);
    //*pole = SDL_DisplayFormatAlpha(tmp);
    //SDL_FreeSurface(tmp);
}

void freeSurfaces(SDL_Surface *screen, SDL_Surface *pole)
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(pole);
}

void handleInput(bool &quit, Point &hookPoint)
{
    int x = 0;
    int y = 0;
    SDL_Event event;
    while( SDL_PollEvent(&event) )
    {
        switch(event.type)
        {
        case SDL_KEYUP:
            if( event.key.keysym.sym == SDLK_ESCAPE )
            {
                quit = true;
                break;
            }
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            hookPoint.x = x;
            hookPoint.y = y;
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
}

void drawPole(SDL_Surface **screen, SDL_Surface **pole, const Point &polePoint,
    const Point &hookPoint)
{
    const int POLE_WIDTH = 1;
    const int POLE_HEIGHT = 1;
    const Uint32 MAROON = SDL_MapRGB((*screen)->format, 180, 0x00, 0x00);
    SDL_Rect currentRectangle = { polePoint.x, polePoint.y, POLE_WIDTH,
        POLE_HEIGHT };
    double curX = polePoint.x;
    double curY = polePoint.y;
    double nextX = polePoint.x;
    double nextY = polePoint.y;
    //double a = -.007;
    double a = howBowed(polePoint, hookPoint);
    //double b = -.01;
    double b = 0.0;
    double c = 0.0;
    bool firstIteration = true;
    double offsetY = calculateQuadratic(a, b, c) - 
        calculateQuadratic(a, b, polePoint.x - 10.0);
    double startingX = polePoint.x - offsetY;
    offsetY = calculateQuadratic(a, b, c) -
        calculateQuadratic(a, b, startingX - 10.0);

    while(curX > 10.0 )
    {
        curX = nextX;
        curY = nextY;
        --nextX;
        c = startingX - curX;
        nextY = offsetY + polePoint.y + calculateQuadratic(a, b, c);
        currentRectangle.x = lesser(nextX, curX);
        currentRectangle.y = lesser(nextY, curY);
        currentRectangle.w = ceil(greater(nextX, curX) - lesser(nextX, curX));
        currentRectangle.h = ceil(greater(nextY, curY) - lesser(nextY, curY));
        if( currentRectangle.w < 1.0)
            currentRectangle.w = 1.0;
        if( currentRectangle.h < 1.0)
            currentRectangle.h = 1.0;
        if( !firstIteration )
            SDL_FillRect(*pole, &currentRectangle, MAROON);
        else
            firstIteration = false;
    }
}

double howBowed(const Point &polePoint, const Point &hookPoint)
{
    double hookPointFromPolePoint = hookPoint.x - polePoint.x;

    //if( hookPointFromPolePoint < 1.0 )
    //    hookPointFromPolePoint = 1.0;

    return -(1.0 / hookPointFromPolePoint);
    //return -(Math::absoluteValue(hookPoint.x - polePoint.x) / 400);
    //Also tried -(Math::absoluteValue(hookPoint.x - polePoint.x) / 400) and
    //got inverse results
}

double calculateQuadratic(double a, double b, double c)
{
    return (-b  + sqrt((pow(b, 2.0) - 4.0 * a * c))) / (2.0 * a);
}

double lesser(double number1, double number2)
{
    if( number1 < number2)
        return number1;

    return number2;
}

double greater(double number1, double number2)
{
    if( number1 > number2 )
        return number1;

    return number2;
}

void drawGame(SDL_Surface **screen, SDL_Surface **pole, const Point &polePoint,
    const Point &hookPoint)
{
    clearSurfaces(screen, pole);
    drawPole(screen, pole, polePoint, hookPoint);
    SDL_BlitSurface(*pole, NULL, *screen, NULL);
    SDL_Flip(*screen);
}

void clearSurfaces(SDL_Surface **screen, SDL_Surface **pole)
{
    const Uint32 BLACK = SDL_MapRGB((*screen)->format, 0x00, 0x00, 0x00);
    SDL_FillRect(*screen, NULL, BLACK);
    SDL_FillRect(*pole, NULL, BLACK);
}

