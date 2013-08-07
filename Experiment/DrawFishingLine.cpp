//File: DrawFishingLine.cpp
//Author:   John Miner
//Created:  08/12/11
//Modified: 08/12/11
//Purpose:  Experiment with drawing a line.
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
#include "../Header/Point.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const Point polePoint = { 400, 300 };
SDL_Surface *initSDL();
void createSurfaces(SDL_Surface **line);
void freeSurfaces(SDL_Surface *screen, SDL_Surface *line);
void handleInput(bool &quit, Point &hookPoint);
double calculateSlope(const Point &p1, const Point &p2);
double calculateRise(const Point &p1, const Point &p2);
double calculateRun(const Point &p1, const Point &p2);
void drawLine(SDL_Surface *screen, SDL_Surface **line, const Point &polePoint,
    const Point &hookPoint);
double greater(double number1, double number2);
double lesser(double number1, double number2);
void drawGame(SDL_Surface **screen, SDL_Surface **line,
    const Point &polePoint, const Point &hookPoint);
void clearSurfaces(SDL_Surface **screen, SDL_Surface **line);

int main(int argc, char **argv)
{
    Point hookPoint = { 400, 450 };
    SDL_Surface *screen = initSDL();
    SDL_Surface *line = NULL;
    bool quit = false;

    createSurfaces(&line);
    
    while( quit == false)
    {
        drawGame(&screen, &line, polePoint, hookPoint);
        handleInput(quit, hookPoint);
    }

    freeSurfaces(screen, line);

    return EXIT_SUCCESS;
}

SDL_Surface *initSDL()
{
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    return SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
        SDL_HWSURFACE);
}

void createSurfaces(SDL_Surface **line)
{
    //SDL_Surface *tmp
    *line = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA,
        SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0, 0, 0, 0);
    //*line = SDL_DisplayFormatAlpha(tmp);
    //SDL_FreeSurface(tmp);
}

void freeSurfaces(SDL_Surface *screen, SDL_Surface *line)
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(line);
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

void drawLine(SDL_Surface **screen, SDL_Surface **line, const Point &polePoint,
    const Point &hookPoint, double OceanSurfaceY)
{
    const int LINE_SEGMENT_WIDTH = 1;
    const int LINE_SEGMENT_HEIGHT = 1;
    //Consider not hardcoding colors
    const Uint32 WHITE = SDL_MapRGBA((*line)->format, 0xFF, 0xFF, 0xFF, 0xFF);
    const Uint32 BLUE = SDL_MapRGBA((*line)->format,  0X73, 0XD0, 0xFF, 0xFF);
    SDL_Rect currentRectangle = { polePoint.x, polePoint.y,
        LINE_SEGMENT_WIDTH, LINE_SEGMENT_HEIGHT };

    Point p1;
    Point p2;

    if(polePoint.x < hookPoint.x)
    {
        p1 = polePoint;
        p2 = hookPoint;
    }
    else
    {
        p1 = hookPoint;
        p2 = polePoint;
    }

    double rise = calculateRise(p1, p2);
    double run = calculateRun(p1, p2);
    double greaterCalculation = 
        greater(greater(p2.x, p2.y), greater(p1.x,p1.y));
    double condition1 = (p2.x - p1.x) / (run / greaterCalculation);
    double condition2 = (p2.y - p1.y ) / (rise / greaterCalculation);
    double calculation1Part = (run / greaterCalculation);
    double calculation2Part = (rise / greaterCalculation);

    for(double curX = p1.x, i = 0, curY = p1.y;
        i < condition1 ||
        i < condition2;
        curX = p1.x + i * calculation1Part,
        curY = p1.y + i * calculation2Part,
        ++i)
    {
        currentRectangle.x = curX;
        currentRectangle.y = curY;
        if(currentRectangle.y < OceanSurfaceY)
            SDL_FillRect(*line, &currentRectangle, WHITE);
        else
            SDL_FillRect(*line, &currentRectangle, BLUE);
    }
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

double calculateSlope(const Point &p1, const Point &p2)
{
    return calculateRise(p1, p2) / calculateRun(p1, p2);
}

double calculateRise(const Point &p1, const Point &p2)
{
    return p2.y - p1.y;
}

double calculateRun(const Point &p1, const Point &p2)
{
    return p2.x - p1.x;
}

void drawGame(SDL_Surface **screen, SDL_Surface **line, const Point &polePoint,
    const Point &hookPoint)
{
    clearSurfaces(screen, line);
    drawLine(screen, line, polePoint, hookPoint, 400); //Consider not hardcoding
    SDL_BlitSurface(*line, NULL, *screen, NULL);
    SDL_Flip(*screen);
}

void clearSurfaces(SDL_Surface **screen, SDL_Surface **line)
{
    const Uint32 BLACK = SDL_MapRGB((*screen)->format, 0x00, 0x00, 0x00);
    SDL_FillRect(*screen, NULL, BLACK);
    SDL_FillRect(*line, NULL, BLACK);
}

