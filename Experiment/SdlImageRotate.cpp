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
#include <iostream>
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include "../Header/Point.hpp"
#include "../Header/Math.hpp"

const double PI = boost::math::constants::pi<double>();

const int FISH_WIDTH = 76;
const int FISH_HEIGHT = 26;
const Point FISH_POSITION = { 400.0, 300.0 };
void initializeSdl();
void initializeScreen(SDL_Surface **screen);
SDL_Surface *loadImage(std::string imagePath);
SDL_Surface *optimizeImage(SDL_Surface *unoptimizedImage);
void drawGame(SDL_Surface *screen, SDL_Surface *image);
void handleInput(bool &quit, Point &mouse);
void freeImages(SDL_Surface *screen, SDL_Surface *image);
void clearScreen(SDL_Surface *screen);
template <typename T>
void rotate(SDL_Surface *image, double angle, SDL_Surface *screen);
template <typename T>
void performRotate(SDL_Surface *image, SDL_Surface *rotated, double angle,
    SDL_Surface *screen);
double calculateRadius(Point center, double x, double y);
double getAngle(Point center, Point mouse);
double getSign(double number);

int main(int argc, char **argv)
{
    SDL_Surface *screen = NULL;
    SDL_Surface *fishImage;
    Point center = { 400.0, 300.0 };
    bool quit = false;
    Point mouse;
    initializeSdl();
    initializeScreen(&screen);
    fishImage = optimizeImage(loadImage("../../../Media/Fish.png"));
    //rotate<Uint32>(fishImage, 2.0, screen);
    //rotate<Uint32>(fishImage, PI, screen);

    while(quit == false)
    {
        handleInput(quit, mouse);
        //std::cout << getAngle(center, mouse) << std::endl;
        rotate<Uint32>(fishImage, getAngle(center, mouse), screen);
        //rotate<Uint32>(fishImage, PI);
        //drawGame(screen, fishImage);
    }

    freeImages(screen, fishImage);

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

void handleInput(bool &quit, Point &mouse)
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
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);
                mouse.x = x;
                mouse.y = y;
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
}

void freeImages(SDL_Surface *screen, SDL_Surface *image)
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(image);
}

void clearScreen(SDL_Surface *screen)
{
    Uint32 WHITE = 0xFFFFFF;
    SDL_Rect destinationRectangle = { 0, 0, 800, 600 };
    SDL_FillRect(screen, &destinationRectangle, WHITE);
}

template <typename T>
void rotate(SDL_Surface *image, double angle, SDL_Surface *screen)
{
    SDL_PixelFormat *format = image->format;
    SDL_Surface *rotated = SDL_CreateRGBSurface(image->flags,
        Math::greater(image->w, image->h), Math::greater(image->w, image->h),
        format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask,
        format->Amask);
    //SDL_Surface *rotated = SDL_CreateRGBSurface(image->flags,
        //image->w, image->h,
        //format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask,
        //format->Amask);
    performRotate<T>(image, rotated, angle, screen);
    //SDL_FreeSurface(image);
    //image = SDL_DisplayFormatAlpha(rotated);
    //SDL_FreeSurface(rotated);
}

template <typename T>
void performRotate(SDL_Surface *image, SDL_Surface *rotated, double angle, 
    SDL_Surface *screen)
{
    //Round or truncate or double?
    const Point IMAGE_CENTER = { (((int) image->w) / 2.0),
        (((int) image->h) / 2.0) };
    const Point ROTATED_CENTER = { (((int) rotated->w) / 2.0),
        (((int) rotated->h) / 2.0)};
    double x = 0.0; 
    double y = 0.0; 
    double lastX = 0.0;
    double lastY = 0.0;
    double radius = 0.0;
    double delX = 0.0;
    double delY = 0.0;
    double originalRadians = 0.0;
    int index = 0;

    SDL_LockSurface(image);
    SDL_LockSurface(rotated);

    for( int i = 0; i < image->h; ++i )
    {
        for( int j = 0; j < image->w; ++j )
        {
            radius = calculateRadius(IMAGE_CENTER, j, i);
            delX = j - IMAGE_CENTER.x;
            delY = i - IMAGE_CENTER.y;

            if( fabs(delX) >= 1.0)
            {
                originalRadians = atan(delY / delX);
            }
            else
            {
                if( i > IMAGE_CENTER.y )
                    originalRadians = 3.0 / 2.0 * 3.14159;
                else
                    originalRadians = 3.14159 / 2.0;
            }
            //std::cout << "cos " << cos(angle + originalRadians) << "\tsin "
                //<< sin(angle + originalRadians) << std::endl;
            x = ROTATED_CENTER.x - radius * cos(angle + originalRadians) *
                getSign(originalRadians) * (i > image->h / 2 ? 1.0 : -1.0);
            y = ROTATED_CENTER.y - radius * sin(angle + originalRadians) *
                getSign(originalRadians) * (i > image->h / 2 ? 1.0 : -1.0);
            //}
            //else
            //{
                //x = 
                //y = 
            //}

            index = rotated->w *
                round(y) + round(x);

            if( index > (rotated->w - 1) * (rotated->h - 1) || index < 0 )
            {
                //std::cout << "index " << index << std::endl;
            }
            else
            {
                ((T *) rotated->pixels)[index] = ((T *) image->pixels)[
                    (int) (image->w * i + j)];
            }

            //if( j == image->w / 2 )
                //std::cout << "j " << j << std::endl;
        }

        //std::cout << "i " << i << std::endl;
    }

    //std::cout << "----------------------------------------" << std::endl;

    SDL_UnlockSurface(image);
    SDL_UnlockSurface(rotated);

    SDL_Rect destinationRectangle = { 400 - 35, 300 - 13, 800, 600 };
    clearScreen(screen);
    SDL_BlitSurface(rotated, NULL, screen, &destinationRectangle);
    SDL_BlitSurface(image, NULL, screen, NULL);
    SDL_Flip(screen);
}

double calculateRadius(Point center, double x, double y)
{
    Point coordinatePair = { x, y };
    return Math::distance(center, coordinatePair);
}

double getAngle(Point center, Point mouse)
{
    double result = 0.0;

    if( mouse.x - center.x == 0 )
    {
        if( mouse.y > center.y )
            result = 3.0 / 2.0 * 3.14159;
        else
            result = 3.14159 / 2.0;
    }
    else
        result = atan((mouse.y - center.y) / (mouse.x - center.x));

    if( mouse.x > center.x )
        result += 3.14159;

    return result;
}

double getSign(double number)
{
    if( number >=0 )
        return 1.0;

    return -1.0;
}

