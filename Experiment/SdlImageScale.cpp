//File: SdlImageFlip.cpp
//Author:   John Miner
//Created:  10/06/11
//Modified: 10/06/11 
//Purpose:  Experiment with flipping/mirroring an image
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
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "../Header/Point.hpp"

const int FISH_WIDTH = 76;
const int FISH_HEIGHT = 26;
const Point FISH_POSITION = { 0, 0 }; //400.0, 300.0 };
void initializeSdl();
void initializeScreen(SDL_Surface **screen);
SDL_Surface *loadImage(std::string imagePath);
SDL_Surface *optimizeImage(SDL_Surface *unoptimizedImage);
void drawGame(SDL_Surface *screen, SDL_Surface *image, SDL_Surface *image2);
void handleInputQuit(bool &quit, Point &mouse);
void freeImages(SDL_Surface *screen, std::vector<SDL_Surface *> images);
void scaleImagePixels(SDL_Surface **image, double newWidth, double newHeight);
void scaleImagePercent(SDL_Surface **image, double howMuchW, double howMuchH);
void scaleImage(SDL_Surface *image, SDL_Surface *scaled, double howMuchW,
    double howMuchH);

int main(int argc, char **argv)
{
    SDL_Surface *screen = NULL;
    bool quit = false;
    Point mouse = { 0, 0 };
    initializeSdl();
    initializeScreen(&screen);
    SDL_Surface *fishImage = optimizeImage(loadImage("../../../../Media/SharkPlaceHolder.png"));
    SDL_Surface *fishImage2 = optimizeImage(loadImage("../../../../Media/SharkPlaceHolder.png"));

    while(quit == false)
    {
        handleInputQuit(quit, mouse);
        scaleImagePercent(&fishImage, .3, .3);
        drawGame(screen, fishImage, fishImage2);
        SDL_FreeSurface(fishImage);
        fishImage = SDL_DisplayFormatAlpha(fishImage2);
    }

    SDL_FreeSurface(fishImage);
    SDL_FreeSurface(fishImage2);
    SDL_FreeSurface(screen);

    return EXIT_SUCCESS;
}

void initializeSdl()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    atexit(SDL_Quit);
    atexit(IMG_Quit);
}

void initializeScreen(SDL_Surface **screen)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int SCREEN_BPP = 32;
    const Uint32 FLAGS = SDL_HWSURFACE | SDL_DOUBLEBUF;

    *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, FLAGS);

    if(!screen)
        std::cout << "SDL_SetVideoMode:" << SDL_GetError() << std::endl;
}

SDL_Surface *loadImage(std::string imagePath)
{
    SDL_Surface *image = IMG_Load(imagePath.c_str());

    if( !image )
        std::cout << "SDL_LoadImage:" << SDL_GetError() << std::endl;

    return image;
}

SDL_Surface *optimizeImage(SDL_Surface *unoptimizedImage)
{
    SDL_Surface *optimizedImage = SDL_DisplayFormatAlpha(unoptimizedImage);

    if( !optimizedImage )
        std::cout << "SDL_DisplayFormatAlpha:" << SDL_GetError() << std::endl;

    SDL_FreeSurface(unoptimizedImage);

    return optimizedImage;
}
        
void drawGame(SDL_Surface *screen, SDL_Surface *image, SDL_Surface *image2)
{
    SDL_Rect destinationRectangle = { FISH_POSITION.x, FISH_POSITION.y, 
        800, 600 };
    SDL_Rect destinationRectangle2 = { FISH_POSITION.x, FISH_POSITION.y +
        image->h + 3, 
        800, 600 };
    SDL_Rect screenRectangle = { 0, 0, 800, 600 };
    Uint32 WHITE = 0xFFFFFF;
    SDL_FillRect(screen, &screenRectangle, WHITE);

    SDL_BlitSurface(image, NULL, screen, &destinationRectangle);
    //SDL_BlitSurface(image2, NULL, screen, &destinationRectangle2);
    SDL_Flip(screen);
}

void handleInputQuit(bool &quit, Point &mouse)
{
    SDL_Event e;
    int x = 0;
    int y = 0;

    while( SDL_PollEvent(&e) )
    {
        switch(e.type)
        {
            case SDL_KEYUP:
                if( e.key.keysym.sym == SDLK_ESCAPE ) 
                    quit = true;
                break;
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);
                if( x <= 0 )
                    x = 1;
                if( y <= 0 )
                    y = 1;
                if( x >= 799 )
                    x = 798;
                if( y >= 599 )
                    y = 598;
                mouse.x = x;
                mouse.y = y;
                break;
        }
    }
}

void scaleImagePixels(SDL_Surface **image, double width, double height)
{
    scaleImagePercent(image, width / (*image)->w, height / (*image)->h);
}

void scaleImagePercent(SDL_Surface **image, double howMuchW, double howMuchH)
{
    SDL_Surface *scaled = SDL_CreateRGBSurface((*image)->flags,
        ceil(((double) (*image)->w) * howMuchW), ceil(((double)(*image)->h)
        * howMuchH), (*image)->format->BitsPerPixel, (*image)->format->Rmask,
        (*image)->format->Gmask, (*image)->format->Bmask, (*image)->format->Amask);

    scaleImage(*image, scaled, howMuchW, howMuchH);
    SDL_FreeSurface(*image);
    *image = scaled;
}

//Uses Uint32 instead of template T for possible performance improvements
void scaleImage(SDL_Surface *image, SDL_Surface *scaled, double howMuchW,
    double howMuchH)
{
    int i = 0;
    double i2 = 0.0;
    int j = 0;
    double j2 = 0.0;
    int k = 0;
    int l = 0;
    int imageW = image->w;
    int imageH = image->h;
    int scaledBothW = scaled->w;
    int scaledBothH = scaled->h;
    int lastI2 = -1;
    int lastJ2 = -1;
    SDL_Rect scaledPortion = { 0, 0, ceil(howMuchW), ceil(howMuchH) };
    
    SDL_LockSurface(image);

    for( i = 0, i2 = 0.0; i < imageH && i2 < scaledBothH;
        ++i, i2 += howMuchH)
    {
        if( lastI2 == (int) i2 )
            continue;

        lastI2 = (int) i2;

        for ( j = 0, j2 = 0.0; j < imageW && j2 < scaledBothW;
            ++j, j2 += howMuchW)
        {
            if( lastJ2 == (int) j2 )
                continue;

            lastJ2 = (int) j2;
            scaledPortion.x = j2;
            scaledPortion.y = i2;
            SDL_FillRect(scaled, &scaledPortion, 
                ((Uint32 *) image->pixels)[(int) round(imageW * i + j)]);
        }

        lastJ2 = -1;
    }

    SDL_UnlockSurface(image);
}

