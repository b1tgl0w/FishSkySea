//File: SdlClipShape.cpp
//Author:   John Miner
//Created:  10/06/11
//Modified: 10/06/11 
//Purpose:  Experiment with flipping/mirroring an image
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include "../Header/Point.hpp"

const int FISH_WIDTH = 76;
const int FISH_HEIGHT = 26;
const int RECTANGLE_WIDTH = 253;
const int RECTANGLE_HEIGHT = 52;
const Point FISH_POSITION = { 400.0, 300.0 };
void initializeSdl();
void initializeScreen(SDL_Surface **screen);
SDL_Surface *loadImage(std::string imagePath);
SDL_Surface *optimizeImage(SDL_Surface *unoptimizedImage);
void drawGame(SDL_Surface *screen, SDL_Surface *image);
void handleInputQuit(bool &quit);
void freeImages(SDL_Surface *screen, SDL_Surface *image, SDL_Surface *
    filledRectangle);
void inverseClipShape(SDL_Surface *source, SDL_Surface *destination);

int main(int argc, char **argv)
{
    SDL_Surface *screen = NULL;
    SDL_Surface *fishImage;
    SDL_Surface *filledRectangle;
    SDL_Surface *glow;
    bool quit = false;
    initializeSdl();
    initializeScreen(&screen);
    fishImage = optimizeImage(loadImage("../../Media/Fish.png"));
    /*filledRectangle = SDL_CreateRGBSurface(screen->flags | SDL_SRCALPHA, 
        RECTANGLE_WIDTH, RECTANGLE_HEIGHT, screen->format->BitsPerPixel,
        screen->format->Rmask, screen->format->Gmask, screen->format->Bmask,
        0x00);
    SDL_SetAlpha(filledRectangle, filledRectangle->flags, 0xFF);*/
    filledRectangle = optimizeImage(loadImage("../../Media/SharkPlaceHolder.png"));
    glow = optimizeImage(loadImage("../../Media/SharkPlaceHolder.png"));

     Uint32 yellow = SDL_MapRGBA( filledRectangle->format, 0xFF, 0xFF, 0x44,
        0xFF);
    Uint8 blue = 0x44;
    Uint8 colorChange = 1;
    SDL_Rect rect = { 0, 0, RECTANGLE_WIDTH, RECTANGLE_HEIGHT };
    SDL_FillRect(filledRectangle, &rect, yellow);
    inverseClipShape(fishImage, filledRectangle);

    while(quit == false)
    {
        handleInputQuit(quit);
        if( blue < 0x44 || blue >= 0xFF )
            colorChange *= -1;
        blue += colorChange;
        yellow = SDL_MapRGBA( glow->format, 0xFF, 0xFF, blue, 0xFF);
        SDL_FillRect(glow, &rect, yellow);
        inverseClipShape(filledRectangle, glow);
        drawGame(screen, glow);
    }

    freeImages(screen, fishImage, filledRectangle);

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
        
void drawGame(SDL_Surface *screen, SDL_Surface *image)
{
    SDL_Rect destinationRectangle = { FISH_POSITION.x, FISH_POSITION.y, 
        800, 600 };

    SDL_BlitSurface(image, NULL, screen, &destinationRectangle);
    SDL_Flip(screen);
}

void handleInputQuit(bool &quit)
{
    SDL_Event e;

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
        }
    }
}

void freeImages(SDL_Surface *screen, SDL_Surface *image, SDL_Surface *
    filledRectangle)
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(image);
    SDL_FreeSurface(filledRectangle);
}

//Preconditions:    destination.size >= source.size
void inverseClipShape(SDL_Surface *source, SDL_Surface *destination)
{
    int x = destination->w / 2 - source->w / 2;
    int y = destination->h / 2 - source->h / 2;
    Uint8 sourceRed;
    Uint8 sourceGreen;
    Uint8 sourceBlue;
    Uint8 sourceAlpha;
    Uint8 destinationRed;
    Uint8 destinationGreen;
    Uint8 destinationBlue;
    Uint8 destinationAlpha;

    SDL_LockSurface(source);
    SDL_LockSurface(destination);
    for( int i = 0; i < source->h; ++i )
    {
        for(int j = 0; j < source->w; ++j)
        {
            SDL_GetRGBA(((Uint32 *) source->pixels)[ i * source->w + j],
                source->format, &sourceRed, &sourceGreen, &sourceBlue,
                &sourceAlpha);
            SDL_GetRGBA(((Uint32 *) destination->pixels)[ (i + y) *
                destination->w + j + x],
                destination->format, &destinationRed, &destinationGreen, 
                &destinationBlue, &destinationAlpha);

            if( sourceAlpha >= destinationAlpha )
                destinationAlpha = sourceAlpha - destinationAlpha;
            else
                destinationAlpha = destinationAlpha - sourceAlpha;

            ((Uint32 *) destination->pixels)[ (i + y) * destination->w + j + x]
                = SDL_MapRGBA(destination->format, destinationRed,
                destinationGreen, destinationBlue, destinationAlpha);
        }
    }
    SDL_UnlockSurface(source);
    SDL_UnlockSurface(destination);
}

