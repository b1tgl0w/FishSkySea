//File: DrawFishingPole.cpp
//Author:   John Miner
//Created:  09/06/11
//Modified: 09/06/11
//Purpose:  Experiment with drawing a pole.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/

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
    double shiftX = hookPoint.x;
    bool firstIteration = true;

    double height = 0;
    double firstY = 400 - sqrt(pow(polePoint.x - hookPoint.x, 2.0) / 300 * (
            polePoint.x - curX));
    while( shiftX > 10.0 )
    {
        --shiftX;
        curX = nextX;
        curY = nextY;
        --nextX;
        nextY = 200 - sqrt(pow(polePoint.x - hookPoint.x, 2.0) / 300 * (
            polePoint.x - curX));
        height = firstY - curY ;
    }

    curX = polePoint.x;
    curY = polePoint.y;
    nextX = polePoint.x;
    nextY = polePoint.y;
    shiftX = hookPoint.x;

    while(shiftX > 10.0 )
    {
        --shiftX;
        curX = nextX;
        curY = nextY;
        --nextX;
        nextY = 200 - sqrt(pow(polePoint.x - hookPoint.x, 2.0) / 300 * (
            polePoint.x - curX));
        currentRectangle.x = shiftX;
        currentRectangle.y = lesser(nextY, curY) + height;
        currentRectangle.w = curX - nextX;
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

