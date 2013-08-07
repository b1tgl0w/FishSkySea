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
double calculateRadius(double centerX, double centerY, double x, double y);
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
    fishImage = optimizeImage(loadImage("../Media/Fish.png"));
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
    const double ROTATED_CENTER_X = ((double) rotated->w)/2.0;
    const double ROTATED_CENTER_Y = ((double) rotated->h)/2.0;
    const double IMAGE_CENTER_X = ((double) image->w) / 2.0;
    const double IMAGE_CENTER_Y = ((double) image->h) / 2.0;
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

    for( double i = 0.0; i < image->h; ++i )
    {
        for( double j = 0.0; j < image->w; ++j )
        {
            radius = calculateRadius(IMAGE_CENTER_X, IMAGE_CENTER_Y, j, i);
            delX = j - IMAGE_CENTER_X;
            delY = i - IMAGE_CENTER_Y;

            originalRadians = atan(delY / delX);
            
            if( delX <= 0)
                originalRadians -= PI;

            x = ROTATED_CENTER_X - radius * cos(angle + originalRadians);
            y = ROTATED_CENTER_Y - radius * sin(angle + originalRadians);

            //The bug probably lies here
            //What I think happens is that two pixels occupy the same index
            //when one is rounded up and an adjacent one is rounded down
            index = round(rotated->w *
                round(y) + round(x));

            if( index > (rotated->w - 1) * (rotated->h - 1) || index < 0 )
            {
            }
            else
            {
                //The bug might also be here
                ((T *) rotated->pixels)[index] = ((T *) image->pixels)[
                   (int) round(((double) image->w) * i + j)];
            }
        }
    }

    SDL_UnlockSurface(image);
    SDL_UnlockSurface(rotated);

    SDL_Rect destinationRectangle = { 400 - 35, 300 - 13, 800, 600 };
    clearScreen(screen);
    SDL_BlitSurface(rotated, NULL, screen, &destinationRectangle);
    SDL_BlitSurface(image, NULL, screen, NULL);
    SDL_Flip(screen);
}

double calculateRadius(double centerX, double centerY, double x, double y)
{
    return sqrt(Math::power(x - centerX, 2) + Math::power(y - centerY, 2));
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

    if( mouse.x - center.x <= 0 )
        result += PI;

    return result;
}

double getSign(double number)
{
    if( number >=0 )
        return 1.0;

    return -1.0;
}

