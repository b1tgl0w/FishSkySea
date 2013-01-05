//File: CartoonizeImage.cpp
//Author:   John Miner
//Created:  01/04/13
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
#include "../../SharedHeader/PaletteHarmony/Color.hpp"
#include <fstream>

const Point IMAGE_POSITION = { 0, 0 };
void initializeSdl();
void initializeScreen(SDL_Surface **screen);
SDL_Surface *loadImage(std::string imagePath);
SDL_Surface *optimizeImage(SDL_Surface *unoptimizedImage);
void drawGame(SDL_Surface *screen, SDL_Surface *image);
void handleInputQuit(bool &quit);
void freeImages(SDL_Surface *screen, SDL_Surface *image, SDL_Surface 
    *cartoonizedImage);
std::vector<Color> generateReducedPalette();
void printColors(const std::vector<Color> &colors);
SDL_Surface *cartoonizeImage(SDL_Surface *imageToCartoonize,
    std::vector<Color> &colors);
void cartoonizePixel(Uint8 *r, Uint8 *g, Uint8 *b, std::vector<Color> 
    &colors);

int main(int argc, char **argv)
{
    if( argc != 3 )
    {
        std::cerr << "Error: Malformed command." << std::endl;
        std::cerr << "Usage: CartoonizeImage imagePath outputPath.bmp" << std::endl;
        exit(1);
    }

    SDL_Surface *screen = NULL;
    SDL_Surface *image = NULL;
    bool quit = false;
    initializeSdl();
    initializeScreen(&screen);
    image = optimizeImage(loadImage(argv[1]));
    std::vector<Color> colors = generateReducedPalette();
    SDL_Surface *cartoonizedImage = cartoonizeImage(image, colors);
    SDL_SaveBMP(cartoonizedImage, argv[2]);
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
    {
        std::cout << "Error: " <<  SDL_GetError() << std::endl;
        exit(1);
    }

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

std::vector<Color> generateReducedPalette()
{
    int hueStepValue = 10;
    int otherStepValue = 33;
    std::vector<Color> colors;
    Color color;
    for( int h = 0; h < 360; h += hueStepValue )
    {
        for( int s = 0; s <= 100; s += otherStepValue )
        {
            
            for( int v = 0; v <= 100; v += otherStepValue )
            {
                color.blendHsv(h, s, v);
                colors.push_back(color);
            }
        }
    }

    return colors;
}

void printColors(const std::vector<Color> &colors)
{
    for( std::vector<Color>::const_iterator it = colors.begin();
        it != colors.end(); ++it )
        it->print();
}

SDL_Surface *cartoonizeImage(SDL_Surface *imageToCartoonize,
    std::vector<Color> &colors)
{
    SDL_Surface *cartoonizedImage = SDL_DisplayFormatAlpha(imageToCartoonize);
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    Color color;
    Uint32 newSdlColor;

    SDL_LockSurface(cartoonizedImage);

    for(int i = 0; i < cartoonizedImage->w * cartoonizedImage->h; ++i )
    {
        SDL_GetRGBA(((Uint32*) cartoonizedImage->pixels)[i], 
            cartoonizedImage->format, &r, &g, &b, &a);
        color.blendRgb(r, g, b);
        color.cartoonize(colors);
        newSdlColor = color.convertToSdlColor(cartoonizedImage->format);
        ((Uint32 *) cartoonizedImage->pixels)[i] = newSdlColor;
    }

    SDL_UnlockSurface(cartoonizedImage);

    return cartoonizedImage;
}

/*void cartoonizePixel(Uint8 *r, Uint8 *g, Uint8 *b, std::vector<Color> 
    &colors)
{
    if( colors.empty() )
        return;

    Color closestColor = colors[0];
    int closestDifference = 9999;
    int currentDifference = 0;
    Uint8 paletteColorR;
    Uint8 paletteColorG;
    Uint8 paletteColorB;
    Uint8 paletteColorA;
    SDL_PixelFormat *format = SDL_GetVideoSurface()->format;
    for( std::vector<Color>::iterator it = colors.begin();
        it != colors.end(); ++it )
    {
        SDL_GetRGBA(it->convertToSdlColor(format), format, &paletteColorR,
            &paletteColorG, &paletteColorB, &paletteColorA);
        currentDifference = Math::abs(*r - paletteColorR) + Math::abs(*g 
            - paletteColorG) + Math::abs(*b - paletteColorB);

        if( currentDifference < closestDifference)
        {
            closestDifference = currentDifference;
            closestColor = *it;
        }
    }

    SDL_GetRGBA(closestColor.convertToSdlColor(format), format, &paletteColorR,
        &paletteColorG, &paletteColorB, &paletteColorA);
    *r = paletteColorR;
    *g = paletteColorG;
    *b = paletteColorB;
}*/

