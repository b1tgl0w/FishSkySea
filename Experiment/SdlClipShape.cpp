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

const bool ALPHA = true;
const bool COLOR_KEY = false;
const int FISH_WIDTH = 552;
const int FISH_HEIGHT = 307;
const int RECTANGLE_WIDTH = 600;
const int RECTANGLE_HEIGHT = 400;
const Point FISH_POSITION = { 50, 50 };
void initializeSdl();
void initializeScreen(SDL_Surface **screen);
SDL_Surface *loadImage(std::string imagePath);
SDL_Surface *optimizeImage(SDL_Surface *unoptimizedImage);
void drawGame(SDL_Surface *screen, SDL_Surface *image, SDL_Surface *fish);
void handleInputQuit(bool &quit);
void freeImages(SDL_Surface *screen, SDL_Surface *image, SDL_Surface *
    filledRectangle, SDL_Surface *glow);
void inverseClipShape(SDL_Surface *source, SDL_Surface *destination, bool 
    alphaOrKey);
void clearScreen(SDL_Surface *screen);
void alphaSurface(SDL_Surface *surface, Uint8 newAlpha);

int main(int argc, char **argv)
{
    SDL_Surface *screen = NULL;
    SDL_Surface *fishImage;
    SDL_Surface *filledRectangle;
    SDL_Surface *glow;
    bool quit = false;
    initializeSdl();
    initializeScreen(&screen);
    fishImage = optimizeImage(loadImage("../../Media/Sloogie.png"));
    //Note: SDL_CreateRGBSurface cannot use screen->flags, etc
    filledRectangle = SDL_CreateRGBSurface(fishImage->flags | SDL_SRCALPHA,
        RECTANGLE_WIDTH, RECTANGLE_HEIGHT, 
        fishImage->format->BitsPerPixel, fishImage->format->Rmask, 
        fishImage->format->Gmask, fishImage->format->Bmask, 0x00);
    glow = SDL_CreateRGBSurface(fishImage->flags | SDL_SRCALPHA,
        RECTANGLE_WIDTH, RECTANGLE_HEIGHT, 
        fishImage->format->BitsPerPixel, fishImage->format->Rmask, 
        fishImage->format->Gmask, fishImage->format->Bmask, 0x00);
    const Uint32 MAGENTA = SDL_MapRGB(glow->format, 0xFF, 0x00, 0xFF);
    SDL_SetColorKey(glow, SDL_SRCCOLORKEY, MAGENTA);
    SDL_SetColorKey(fishImage, SDL_SRCCOLORKEY, MAGENTA);

    Uint32 yellow = SDL_MapRGB( filledRectangle->format, 0xFF, 0xFF, 0x44);
    Uint8 alpha = 0x33;
    Uint8 alphaChange = 1;
    SDL_Rect rect = { 0, 0, RECTANGLE_WIDTH, RECTANGLE_HEIGHT };
    SDL_FillRect(filledRectangle, &rect, yellow);
    inverseClipShape(fishImage, filledRectangle, ALPHA);
    SDL_FillRect(glow, &rect, yellow);
    inverseClipShape(filledRectangle, glow, COLOR_KEY);

    while(quit == false)
    {
        handleInputQuit(quit);
        if( alpha < 0x11 )
            alphaChange = 1;
        if(  alpha >= 0x99 )
            alphaChange = -1;
        alpha += alphaChange;
        //alphaSurface(glow, alpha);
        SDL_SetAlpha(glow, SDL_SRCALPHA, alpha);
        drawGame(screen, glow, fishImage);
    }

    freeImages(screen, fishImage, filledRectangle, glow);

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
        
void drawGame(SDL_Surface *screen, SDL_Surface *image, SDL_Surface *fish)
{
    clearScreen(screen);
    SDL_Rect destinationRectangle = { FISH_POSITION.x, FISH_POSITION.y, 
        800, 600 };
    SDL_Rect fishRectangle = { FISH_POSITION.x + image->w / 2 - fish->w / 2, 
        FISH_POSITION.y + image->h / 2 - fish->h / 2,
        800, 600 };

    SDL_BlitSurface(fish, NULL, screen, &fishRectangle);
    SDL_BlitSurface(image, NULL, screen, &destinationRectangle);
    SDL_Flip(screen);
}

void clearScreen(SDL_Surface *screen)
{
    const Uint32 BLACK = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
    SDL_Rect destinationRectangle = { 0, 0, screen->w, screen->h };
    SDL_FillRect(screen, &destinationRectangle, BLACK);
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
    filledRectangle, SDL_Surface *glow)
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(image);
    SDL_FreeSurface(filledRectangle);
    SDL_FreeSurface(glow);
}

//Preconditions:    destination.size >= source.size
void inverseClipShape(SDL_Surface *source, SDL_Surface *destination, bool
    alphaOrKey)
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

            //destinationAlpha ^= sourceAlpha; 
            if( sourceRed == 0xFF && sourceBlue == 0xFF && sourceGreen == 0x00 )
            {
            }
            else if( alphaOrKey == COLOR_KEY )
            {
                destinationRed = 0xFF;
                destinationBlue = 0xFF;
                destinationGreen = 0x00;
            }
                
            if( sourceAlpha == 0xFF && alphaOrKey == ALPHA )
            {
                destinationRed = 0xFF;
                destinationBlue = 0xFF;
                destinationGreen = 0x00;
            }

            ((Uint32 *) destination->pixels)[ (i + y) * destination->w + j + x]
                = SDL_MapRGBA(destination->format, destinationRed,
                destinationGreen, destinationBlue, destinationAlpha);
        }
    }
    SDL_UnlockSurface(source);
    SDL_UnlockSurface(destination);
}

//This is slow if called every frame, so try using per-surface alpha with
//SDL_SetAlpha and maybe color keys
void alphaSurface(SDL_Surface *surface, Uint8 newAlpha)
{
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;

    SDL_LockSurface(surface);
    for( int i = 0; i < surface->h; ++i )
    {
        for(int j = 0; j < surface->w; ++j )
        {
            SDL_GetRGBA(((Uint32 *) surface->pixels)[i * surface->w + j],
                surface->format, &red, &green, &blue, &alpha);

            if( alpha != 0 )
                alpha = newAlpha;

            ((Uint32 *) surface->pixels)[i * surface->w + j] = 
                SDL_MapRGBA(surface->format, red, green, blue, alpha);
        }
    }
    SDL_UnlockSurface(surface);
}

