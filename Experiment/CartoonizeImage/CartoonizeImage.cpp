//File: SdlImageFlip.cpp
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
#include "../../Header/Point.hpp"
#include "../../Header/Math.hpp"
#include <fstream>

struct Color
{
    int r;
    int g;
    int b;
};

const Point IMAGE_POSITION = { 0, 0 };
void initializeSdl();
void initializeScreen(SDL_Surface **screen);
SDL_Surface *loadImage(std::string imagePath);
SDL_Surface *optimizeImage(SDL_Surface *unoptimizedImage);
void drawGame(SDL_Surface *screen, SDL_Surface *image);
void handleInputQuit(bool &quit);
void freeImages(SDL_Surface *screen, SDL_Surface *image, SDL_Surface 
    *cartoonizedImage);
std::vector<Color> loadPalette(const std::string &PalettePath);
void printColors(const std::vector<Color> &colors);
SDL_Surface *cartoonizeImage(SDL_Surface *imageToCartoonize,
    const std::vector<Color> &colors);
void cartoonizePixel(Uint8 *r, Uint8 *g, Uint8 *b, const std::vector<Color> 
    &colors);

int main(int argc, char **argv)
{
    SDL_Surface *screen = NULL;
    SDL_Surface *image;
    bool quit = false;
    initializeSdl();
    initializeScreen(&screen);
    image = optimizeImage(loadImage("../Media/PictureToCartoonize.jpg"));
    std::vector<Color> colors = loadPalette("../Data/Palette.txt");
    SDL_Surface *cartoonizedImage = cartoonizeImage(image, colors);

    while(quit == false)
    {
        handleInputQuit(quit);
        drawGame(screen, cartoonizedImage);
    }

    freeImages(screen, image, cartoonizedImage);

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
    SDL_Rect destinationRectangle = { IMAGE_POSITION.x, IMAGE_POSITION.y, 
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

void freeImages(SDL_Surface *screen, SDL_Surface *image, SDL_Surface 
    *cartoonizedImage)
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(image);
    SDL_FreeSurface(cartoonizedImage);
}

std::vector<Color> loadPalette(const std::string &PalettePath)
{
    std::vector<Color> colors;
    Color color;
    int skip;
    char hsvString[256];
    std::ifstream file(PalettePath.c_str());
    file.getline(hsvString, 256);
    while(!file.eof())
    {
        file >> skip >> skip >> skip >> color.r >> color.g >> color.b;
        colors.push_back(color);
    }

    file.close();

    return colors;
}

void printColors(const std::vector<Color> &colors)
{
    for( std::vector<Color>::const_iterator it = colors.begin();
        it != colors.end(); ++it )
    {
        std::cout << (*it).r << '\t' << (*it).g << '\t' << (*it).b << std::endl;
    }
}

SDL_Surface *cartoonizeImage(SDL_Surface *imageToCartoonize,
    const std::vector<Color> &colors)
{
    SDL_Surface *cartoonizedImage = SDL_DisplayFormatAlpha(imageToCartoonize);
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    SDL_LockSurface(cartoonizedImage);

    for(int i = 0; i < cartoonizedImage->w * cartoonizedImage->h; ++i )
    {
        SDL_GetRGBA(((Uint32*) cartoonizedImage->pixels)[i], 
            cartoonizedImage->format, &r, &g, &b, &a);
        cartoonizePixel(&r, &g, &b, colors);
        ((Uint32 *) cartoonizedImage->pixels)[i] = SDL_MapRGBA(
            cartoonizedImage->format, r, g, b, a);
    }

    SDL_UnlockSurface(cartoonizedImage);

    return cartoonizedImage;
}

void cartoonizePixel(Uint8 *r, Uint8 *g, Uint8 *b, const std::vector<Color> 
    &colors)
{
    if( colors.empty() )
        return;

    Color closestColor = colors[0];
    int closestDifference = 9999;
    int currentDifference = 0;
    for( std::vector<Color>::const_iterator it = colors.begin();
        it != colors.end(); ++it )
    {
        currentDifference = Math::abs(*r - it->r) + Math::abs(*g - it->g) + 
            Math::abs(*b - it->b);

        if( currentDifference < closestDifference)
        {
            closestDifference = currentDifference;
            closestColor = *it;
        }
    }

    *r = closestColor.r;
    *g = closestColor.g;
    *b = closestColor.b;
}

