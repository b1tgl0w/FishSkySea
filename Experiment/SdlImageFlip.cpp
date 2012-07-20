//File: SdlImageFlip.cpp
//Author:   John Miner
//Created:  10/10/11
//Modified: 10/10/11 
//Purpose:  Experiment with flipping/mirroring an image
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include "../Header/Point.hpp"

enum FlipType { HORIZONTAL_FLIP, VERTICAL_FLIP };
const int FISH_WIDTH = 76;
const int FISH_HEIGHT = 26;
const Point FISH_POSITION = { 400.0, 300.0 };
void initializeSdl();
void initializeScreen(SDL_Surface **screen);
SDL_Surface *loadImage(std::string imagePath);
SDL_Surface *optimizeImage(SDL_Surface *unoptimizedImage);
void loadImages(std::vector<SDL_Surface *> &images);
void drawGame(SDL_Surface *screen, std::vector<SDL_Surface *> images);
void flipImage(SDL_Surface **image, FlipType f);
void flipImageInPlace(SDL_Surface **image, FlipType f);
void flipImageInPlaceSdlLock(SDL_Surface **image, FlipType f);
template <typename T>
void flipImageInPlaceSdlLockTemplate(SDL_Surface **image, FlipType f);
template <typename T>
void flipImageFinal(SDL_Surface **image, const FlipType &f); //Integrate
void determineFlipLoopCondition(int &loopConditionRow, int &loopConditionColumn,
    SDL_Surface **image, const FlipType &f); //Integrate
template <typename T>
void swapPixel(T *pixel1, T *pixel2); //Integrate
int getFlipIndex(int width, int height, int i, int j, FlipType f);
void handleInputQuit(bool &quit);
void freeImages(SDL_Surface *screen, std::vector<SDL_Surface *> images);
void profileFlipImage(SDL_Surface **image, int numberOfIterations);
void profileFlipImageInPlace(SDL_Surface **image, int numberOfIterations);
void profileFlipImageInPlaceSdlLock(SDL_Surface **image, int numberOfIterations);
void profileFlipImageInPlaceSdlLockTemplate(SDL_Surface **image, int numberOfIterations);

int main(int argc, char **argv)
{
    SDL_Surface *screen = NULL;
    SDL_Surface *fishImage;
    bool quit = false;
    initializeSdl();
    initializeScreen(&screen);
    std::vector<SDL_Surface *> images;
    images.push_back(fishImage);
    loadImages(images);
    const int NUMBER_OF_PROFILE_ITERATIONS = 10000;

    if( images[0]->format->BitsPerPixel == 32 )
    {
        flipImageFinal<Uint32>(&images[0], HORIZONTAL_FLIP);
        flipImageFinal<Uint32>(&images[0], VERTICAL_FLIP);
    }
    else if( images[0]->format->BitsPerPixel == 16 )
    {
        flipImageFinal<Uint16>(&images[0], HORIZONTAL_FLIP);
        flipImageFinal<Uint16>(&images[0], VERTICAL_FLIP);
    }
    else if( images[0]->format->BitsPerPixel == 8 )
    {
        flipImageFinal<Uint8>(&images[0], HORIZONTAL_FLIP);
        flipImageFinal<Uint8>(&images[0], VERTICAL_FLIP);
    }


    while(quit == false)
    {
        handleInputQuit(quit);
        drawGame(screen, images);
    }

    freeImages(screen, images);

    return EXIT_SUCCESS;
}

void profileFlipImage(SDL_Surface **image, int numberOfIterations)
{
    for( int i = 0; i < numberOfIterations; ++i ) 
    {
        flipImage(image, HORIZONTAL_FLIP);
        flipImage(image, VERTICAL_FLIP);
    }
}

void profileFlipImageInPlace(SDL_Surface **image, int numberOfIterations)
{
    for( int i = 0; i < numberOfIterations; ++i ) 
    {
        flipImageInPlace(image, HORIZONTAL_FLIP);
        flipImageInPlace(image, VERTICAL_FLIP);
    }
}

void profileFlipImageInPlaceSdlLock(SDL_Surface **image, int numberOfIterations)
{
    for( int i = 0; i < numberOfIterations; ++i ) 
    {
        flipImageInPlaceSdlLock(image, HORIZONTAL_FLIP);
        flipImageInPlaceSdlLock(image, VERTICAL_FLIP);
    }
}

void profileFlipImageInPlaceSdlLockTemplate(SDL_Surface **image, int numberOfIterations)
{
    if( (*image)->format->BitsPerPixel == 32 )
    {
        for( int i = 0; i < numberOfIterations; ++i ) 
        {
            flipImageInPlaceSdlLockTemplate<Uint32>(image, HORIZONTAL_FLIP);
            flipImageInPlaceSdlLockTemplate<Uint32>(image, VERTICAL_FLIP);
        }
    }

    if( (*image)->format->BitsPerPixel == 16 )
    {
        for( int i = 0; i < numberOfIterations; ++i ) 
        {
            flipImageInPlaceSdlLockTemplate<Uint16>(image, HORIZONTAL_FLIP);
            flipImageInPlaceSdlLockTemplate<Uint16>(image, VERTICAL_FLIP);
        }
    }

    if( (*image)->format->BitsPerPixel == 8 )
    {
        for( int i = 0; i < numberOfIterations; ++i ) 
        {
            flipImageInPlaceSdlLockTemplate<Uint8>(image, HORIZONTAL_FLIP);
            flipImageInPlaceSdlLockTemplate<Uint8>(image, VERTICAL_FLIP);
        }
    }
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
        
void loadImages(std::vector<SDL_Surface *> &images)
{
    if(images.empty())
        return;

    for(std::vector<SDL_Surface *>::iterator it = images.begin();
        it != images.end(); ++it)
        *it = optimizeImage(loadImage("../../../Media/Fish.png"));
}

void drawGame(SDL_Surface *screen, std::vector<SDL_Surface *> images)
{
    SDL_Rect destinationRectangle = { FISH_POSITION.x, FISH_POSITION.y, 
        800, 600 };

    if( images.empty() )
        return;

    for( std::vector<SDL_Surface *>::iterator it = images.begin();
        it != images.end(); ++it )
    {
        SDL_BlitSurface(*it, NULL, screen, &destinationRectangle);
    }

    SDL_Flip(screen);
}

//Choose either this or flipImageInpPlace
void flipImage(SDL_Surface **image, FlipType f)
{
    int flippedImageIndex = 0;
    int imageIndex = 0;
    SDL_Surface *flippedImage = SDL_CreateRGBSurface((*image)->flags, (*image)->w,
        (*image)->h, (*image)->format->BitsPerPixel, (*image)->format->Rmask,
        (*image)->format->Gmask, (*image)->format->Bmask, (*image)->format->Amask);

    if( !flippedImage )
        std::cout << "SDL_CreateRGBSurface:" << SDL_GetError() << std::endl;

    for( int i = 0; i <= (*image)->h - 1; ++i )
    {
        for( int j = 0; j <= (*image)->w - 1; ++j )
        {
            SDL_LockSurface(flippedImage);
            SDL_LockSurface(*image);
            flippedImageIndex = getFlipIndex((*image)->w, (*image)->h, i,
                j, f);
            imageIndex = (*image)->w * i + j;
            ((Uint32 *)flippedImage->pixels)[flippedImageIndex] = 
                ((Uint32 *) (*image)->pixels)[imageIndex];
            SDL_UnlockSurface(flippedImage);
            SDL_UnlockSurface(*image);
        }
    }

    SDL_Surface *tmp = *image;
    *image = flippedImage;
    SDL_FreeSurface(tmp);
}

//Code duplication okay because only one of the two will be integrated into
//the final project. Run profiles on each of these to see which one is faster
//and/or has a lower memory footprint
//Results: This function is more than twice as fast as flip with temporary
//surface
void flipImageInPlace(SDL_Surface **image, FlipType f)
{
    Uint32 temporaryPixel;
    int flippedImageIndex = 0;
    int imageIndex = 0;
    int loopConditionRow = (*image)->h;
    int loopConditionColumn = (*image)->w;
    
    if( f == HORIZONTAL_FLIP )
        loopConditionColumn = (*image)->w / 2;
    else if( f == VERTICAL_FLIP )
        loopConditionRow = (*image)->h / 2;
        
    for( int i = 0; i < loopConditionRow; ++i )
    {
        for( int j = 0; j < loopConditionColumn; ++j )
        {
            SDL_LockSurface(*image);
            flippedImageIndex = getFlipIndex((*image)->w, (*image)->h, i,
                j, f);
            imageIndex = (*image)->w * i + j;
            temporaryPixel = ((Uint32 *) (*image)->pixels)[flippedImageIndex];
            ((Uint32 *) (*image)->pixels)[flippedImageIndex] = ((Uint32 *)
                (*image)->pixels)[imageIndex];
            ((Uint32 *) (*image)->pixels)[imageIndex] = temporaryPixel;
            SDL_UnlockSurface(*image);
        }
    }
}

//Profiling the difference between locking/unlocking the surface
//within/without the loop
//Would this function slow down other threads?
//Results: This function is .02 MILIseconds faster per call than flipImageInPlace
void flipImageInPlaceSdlLock(SDL_Surface **image, FlipType f)
{
    Uint32 temporaryPixel;
    int flippedImageIndex = 0;
    int imageIndex = 0;
    int loopConditionRow = (*image)->h;
    int loopConditionColumn = (*image)->w;
    
    if( f == HORIZONTAL_FLIP )
        loopConditionColumn = (*image)->w / 2;
    else if( f == VERTICAL_FLIP )
        loopConditionRow = (*image)->h / 2;
        
    SDL_LockSurface(*image);
    for( int i = 0; i < loopConditionRow; ++i )
    {
        for( int j = 0; j < loopConditionColumn; ++j )
        {
            flippedImageIndex = getFlipIndex((*image)->w, (*image)->h, i,
                j, f);
            imageIndex = (*image)->w * i + j;
            temporaryPixel = ((Uint32 *) (*image)->pixels)[flippedImageIndex];
            ((Uint32 *) (*image)->pixels)[flippedImageIndex] = ((Uint32 *)
                (*image)->pixels)[imageIndex];
            ((Uint32 *) (*image)->pixels)[imageIndex] = temporaryPixel;
        }
    }
    SDL_UnlockSurface(*image);
}

//Templatized so works with pixels of different bit depths
template <typename T>
void flipImageInPlaceSdlLockTemplate(SDL_Surface **image, FlipType f)
{
    T temporaryPixel;
    int flippedImageIndex = 0;
    int imageIndex = 0;
    int loopConditionRow = (*image)->h;
    int loopConditionColumn = (*image)->w;
    
    if( f == HORIZONTAL_FLIP )
        loopConditionColumn = (*image)->w / 2;
    else if( f == VERTICAL_FLIP )
        loopConditionRow = (*image)->h / 2;
        
    SDL_LockSurface(*image);
    for( int i = 0; i < loopConditionRow; ++i )
    {
        for( int j = 0; j < loopConditionColumn; ++j )
        {
            flippedImageIndex = getFlipIndex((*image)->w, (*image)->h, i,
                j, f);
            imageIndex = (*image)->w * i + j;
            temporaryPixel = ((T *) (*image)->pixels)[flippedImageIndex];
            ((T *) (*image)->pixels)[flippedImageIndex] = ((T *)
                (*image)->pixels)[imageIndex];
            ((T *) (*image)->pixels)[imageIndex] = temporaryPixel;
        }
    }
    SDL_UnlockSurface(*image);
}

//This is the modularized, optimized flip function that should be integrated
// into the game
template <typename T>
void flipImageFinal(SDL_Surface **image, const FlipType &f)
{
    T temporaryPixel;
    int flippedImageIndex = 0;
    int imageIndex = 0;
    int loopConditionRow = (*image)->h;
    int loopConditionColumn = (*image)->w;
    
    determineFlipLoopCondition(loopConditionRow, loopConditionColumn,
        image, f);
        
    SDL_LockSurface(*image);
    for( int i = 0; i < loopConditionRow; ++i )
    {
        for( int j = 0; j < loopConditionColumn; ++j )
        {
            flippedImageIndex = getFlipIndex((*image)->w, (*image)->h, i,
                j, f);
            imageIndex = (*image)->w * i + j;
            //swapPixel(...) would not compile, so just writing the body
            // of swapPixel(...) here.
            //temporaryPixel = ((T *) (*image)->pixels)[flippedImageIndex];
            //((T *) (*image)->pixels)[flippedImageIndex] = ((T *)
                //(*image)->pixels)[imageIndex];
            //((T *) (*image)->pixels)[imageIndex] = temporaryPixel;
            std::swap(((T *) (*image)->pixels)[flippedImageIndex], ((T *)
                (*image)->pixels)[imageIndex]);
        }
    }
    SDL_UnlockSurface(*image);
}

void determineFlipLoopCondition(int &loopConditionRow, int &loopConditionColumn,
    SDL_Surface **image, const FlipType &f)
{
    if( f == HORIZONTAL_FLIP )
        loopConditionColumn = (*image)->w / 2;
    else if( f == VERTICAL_FLIP )
        loopConditionRow = (*image)->h / 2;
}

template <typename T>
void swapPixel(T *pixel1, T *pixel2)
{
    T temporaryPixel = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temporaryPixel;
}

int getFlipIndex(int width, int height, int i, int j, FlipType f)
{
    if( f == VERTICAL_FLIP )
        return width * (height - 1 - i) + j;
    else if( f == HORIZONTAL_FLIP )
        return width * i + (width - 1 - j);

    return 0; //Bad arg exception?
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

void freeImages(SDL_Surface *screen, std::vector<SDL_Surface *> images)
{
    SDL_FreeSurface(screen);

    if( images.empty() )
        return;

    for( std::vector<SDL_Surface *>::iterator it = images.begin();
        it != images.end(); ++it )
        SDL_FreeSurface(*it);
}

