//File: CollisionDetectionPp.cpp
//Author:   John Miner
//Created:  06/13/14
//Modified: 06/13/14
//Purpose:  Pixel perfect collision detection
//Copyright 2014 John Miner
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

#include <iostream>
#include <cmath>

#include <string>
#include <boost/shared_ptr.hpp>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../Header/BoundingBox.hpp"
#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"

using namespace std;

//Make these classwide instead of global
const int UFO_WIDTH = 32;
const int PLANET_WIDTH = 64;

//Dynamic programming version
bool isCollisionPp(int boolmap1[], int boolmap2[], int width, int height,
    int inX, int inY)
{
    for( int i = 0; i < inY; ++i )
    {
        int index1 = i * UFO_WIDTH + inX - 1;
        int index2 = i * PLANET_WIDTH + inX - 1;

        if( boolmap1[index1] == 1 && boolmap2[index2] == 1 )
            return true;

        index1 = i * UFO_WIDTH + width - inX;
        index2 = i * PLANET_WIDTH + width - inX;

        if( boolmap1[index1] == 1 && boolmap2[index2] == 1 )
            return true;

        index1 = inX - 1 + (height - 1 - i) * UFO_WIDTH;
        index2 = inX - 1 + (height - 1 - i) * PLANET_WIDTH;

        if( boolmap1[index1] == 1 && boolmap2[index2] == 1 )
            return true;

        index1 = (height - 1 - i) * UFO_WIDTH + width - inX;
        index2 = (height - 1 - i) * PLANET_WIDTH + width - inX;

        if( boolmap1[index1] == 1 && boolmap2[index2] == 1 )
            return true;
    }

    for( int j = 0; j < inX - 1; ++j )
    {
        int index1 = j + (inY - 1) * UFO_WIDTH;
        int index2 = j + (inY - 1) * PLANET_WIDTH;

        if( boolmap1[index1] == 1 && boolmap2[index2] == 1 )
            return true;

        index1 = width - 1 - j + (inY - 1) * UFO_WIDTH;
        index2 = width - 1 - j + (inY - 1) * PLANET_WIDTH;

        if( boolmap1[index1] == 1 && boolmap2[index2] == 1 )
            return true;

        index1 = j + (height - inY) * UFO_WIDTH;
        index2 = j + (height - inY) * PLANET_WIDTH;

        if( boolmap1[index1] == 1 && boolmap2[index2] == 1 )
            return true;

        index1 = (height - inY) * UFO_WIDTH + width - 1 - j;
        index2 = (height - inY) * PLANET_WIDTH + width - 1 - j;

        if( boolmap1[index1] == 1 && boolmap2[index2] == 1 )
            return true;
    }

    if( inX * 2 >= width && inY * 2 >= height )
        return false;

    return isCollisionPp(boolmap1, boolmap2, width, height,
        inX + (inX * 2 < width ? 1 : 0),
        inY + (inY * 2 < height ? 1 : 0) );
}

/******************************************************************************
//Divide and conquer version
bool isCollisionPp(int boolmap1[], int boolmap2[], int width, int height)
{
    if( width <= 1 && height <= 1 )
        return boolmap1[0] == 1 && boolmap2[0] == 1;

    int halfHeightMinus = height / 2;
    int halfWidthMinus = width / 2;
    int halfHeightPlus = ceil(double(height) / 2.0);
    int halfWidthPlus = ceil(double(width) / 2.0);

    if( width > 1 && height <= 1 )
        return isCollisionPp(boolmap1, boolmap2, halfWidthMinus, height) ||
            isCollisionPp(&boolmap1[halfWidthMinus], 
                          &boolmap2[halfWidthMinus], 
                          halfWidthPlus, height); 

    if( width <= 1 && height > 1 )
        return isCollisionPp(boolmap1, boolmap2, width, halfHeightMinus) ||
            isCollisionPp(&boolmap1[UFO_WIDTH * halfHeightMinus], 
                          &boolmap2[PLANET_WIDTH * halfHeightMinus], 
                          width, halfHeightPlus); 

    return isCollisionPp(boolmap1, boolmap2, halfWidthMinus, halfHeightMinus) ||
           isCollisionPp(&boolmap1[halfWidthMinus], &boolmap2[halfWidthMinus],
                         halfWidthPlus, halfHeightMinus) ||
           isCollisionPp(&boolmap1[UFO_WIDTH * halfHeightMinus], 
                         &boolmap2[PLANET_WIDTH * halfHeightMinus],
                         halfWidthMinus, halfHeightPlus) ||
           isCollisionPp(&boolmap1[UFO_WIDTH * halfHeightMinus + halfWidthMinus], 
                         &boolmap2[PLANET_WIDTH * halfHeightMinus + halfWidthMinus],
                         halfWidthPlus, halfHeightPlus);
}
******************************************************************************/

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

//Global constants
//Note to students: Global variable should not be used, but
//                  for a small program like this, global constants
//                  are okay. In object oriented programming, constants
//                  would usually be static members of various classes
//                  or local to a method.
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const string UFO_IMAGE_PATH = "../Graphics/UFO.png";
const string PLANET_IMAGE_PATH = "../Graphics/Planet.png";
//These coordinates are the center of the screen
//Half the screen width/height - half the image width/height
const int UFO_X_INITIAL = 0;
const int UFO_Y_INITIAL = 0;
const int PLANET_X_INITIAL = 400 - 32;
const int PLANET_Y_INITIAL = 300 - 32;
//const int UFO_WIDTH = 32;
const int UFO_HEIGHT = 32;
//const int PLANET_WIDTH = 64;
const int PLANET_HEIGHT = 64;
const int UFO_X_VELOCITY_MIN = -1;
const int UFO_X_VELOCITY_MAX = 1;
const int UFO_Y_VELOCITY_MIN = -1;
const int UFO_Y_VELOCITY_MAX = 1;
const int UFO_VELOCITY_REST = 0;

//Function prototypes
void initializeSDL();
SDL_Texture *loadImage(string path);
SDL_Texture *loadImage(SDL_Surface *image);
SDL_Surface *loadUnoptimizedImage(string path);
void handleInput(bool &stillPlaying, int &xVelocity, int &yVelocity);
void handleArrows(SDL_Event event, int &ufoXVelocity, int &ufoYVelocity);
void handleEscape(SDL_Event event, bool &stillPlaying);
void handleQuit(SDL_Event event, bool &stillPlaying);
void moveUfo(int &coordinate, int velocity);
void wrapUfo(int &ufoX, int &ufoY);
bool isUfoPlanetCollision(int ufoX, int ufoY);
int distance(int y2, int y1, int x2, int x1);
void drawGame(SDL_Texture *ufo, 
    SDL_Texture *planet, int ufoX, int ufoY);
void clearScreen(SDL_Surface *screen);

void convertSurfaceToBoolmap(SDL_Surface *surface, int boolmap[])
{
    int width = surface->w;
    int height = surface->h;
    Uint8 alpha;

    SDL_LockSurface(surface);
    
    for( int i = 0; i < height; ++i )
    {
        for( int j = 0; j < width; ++j )
        {
            Uint32 pixel = ((Uint32 *)surface->pixels)[ i * width + j ];
            alpha = (pixel >> 24) & 0xFF;
            if( alpha == 0xFF)
                boolmap[ i * width + j ] = 1;
            else
                boolmap[ i * width + j ] = 0;
        }
    }

    SDL_UnlockSurface(surface);
}

/******************************************************************************
void getSubArray(int boolmap[], int submap[], int width, int subX, int subY, int subWidth,
    int subHeight)
{
    for(int i = subY, i2 = 0; i2 < subHeight; ++i, ++i2)
        for(int j = subX, j2 = 0; j2 < subWidth; ++j, ++j2)
            submap[i2 * subWidth + j2] = boolmap[i * width + j];
}
******************************************************************************/

int main(int argc, char **argv)
{
    initializeSDL();
    SDL_Texture *ufo = loadImage(UFO_IMAGE_PATH);
    SDL_Texture *planet = loadImage(PLANET_IMAGE_PATH);
    bool stillPlaying = true;
    int ufoX = UFO_X_INITIAL;
    int ufoY = UFO_Y_INITIAL;
    int ufoXVelocity = UFO_VELOCITY_REST;
    int ufoYVelocity = UFO_VELOCITY_REST;

    int *boolmap1 = new int[UFO_WIDTH * UFO_HEIGHT];
    int *boolmap2 = new int[PLANET_WIDTH * PLANET_HEIGHT];
    SDL_Surface *tempUfo = loadUnoptimizedImage(UFO_IMAGE_PATH);
    SDL_Surface *tempPlanet = loadUnoptimizedImage(PLANET_IMAGE_PATH);
    convertSurfaceToBoolmap(tempUfo, boolmap1);
    convertSurfaceToBoolmap(tempPlanet, boolmap2);
    SDL_FreeSurface(tempUfo);
    SDL_FreeSurface(tempPlanet);

    boost::shared_ptr<Point> ufoPosition(new Point(ufoX, ufoY));
    boost::shared_ptr<Dimension> ufoSize(new Dimension(UFO_WIDTH, UFO_HEIGHT));

    boost::shared_ptr<Point> planetPosition(new Point(PLANET_X_INITIAL, PLANET_Y_INITIAL));
    boost::shared_ptr<Dimension> planetSize(new Dimension(PLANET_WIDTH, PLANET_HEIGHT));

    BoundingBox ufoBox(ufoPosition, ufoSize);
    BoundingBox planetBox(planetPosition, planetSize);
    Point overlapPosition;
    Dimension overlapSize;

    while( stillPlaying == true )
    {
        handleInput(stillPlaying, ufoXVelocity, ufoYVelocity);
        moveUfo(ufoX, ufoXVelocity);
        moveUfo(ufoY, ufoYVelocity);
        ufoPosition->x = ufoX;
        ufoPosition->y = ufoY;

        if(ufoBox.getCollisionOverlap(planetBox, overlapPosition, overlapSize))
        {
            /***************************************************
            int *subBoolmap1 = new int[int(overlapSize.width) * int(overlapSize.height)];
            int *subBoolmap2 = new int[int(overlapSize.width) * int(overlapSize.height)];

            getSubArray(boolmap1, subBoolmap1, ufoSize->width,
                overlapPosition.x - ufoPosition->x,
                overlapPosition.y - ufoPosition->y,
                overlapSize.width, overlapSize.height);
            getSubArray(boolmap2, subBoolmap2, planetSize->width,
                overlapPosition.x - planetPosition->x,
                overlapPosition.y - planetPosition->y,
                overlapSize.width, overlapSize.height);
            ***************************************************/

            /******************************************************************
            cout << "-----------------------------------" << endl;
            cout << overlapPosition.x - ufoPosition->x << "\t" 
                << overlapPosition.y - ufoPosition->y <<endl;
            cout << overlapSize.width << "\t" << overlapSize.height <<endl;
            cout << "-----------------------------------" << endl;

            for(int i = 0; i < overlapSize.height; ++i)
            {
                for(int j = 0; j < overlapSize.width; ++j)
                    cout << subBoolmap1[i * int(overlapSize.width) + j];
                cout << endl;
            }
            ******************************************************************/
                
            //if( isCollisionPp(subBoolmap1, subBoolmap2, overlapSize.width,
                //overlapSize.width, overlapSize.height) )
            if( isCollisionPp(&boolmap1[(int(overlapPosition.y) - int(ufoPosition->y))
                * int(ufoSize->width) + (int(overlapPosition.x) - int(ufoPosition->x))],
                &boolmap2[(int(overlapPosition.y) - int(planetPosition->y)) *
                int(planetSize->width) + (int(overlapPosition.x) - int(planetPosition->x))],
                overlapSize.width, overlapSize.height, 1, 1) )
            {
                moveUfo(ufoX, -ufoXVelocity);
                moveUfo(ufoY, -ufoYVelocity);
                ufoPosition->x = ufoX;
                ufoPosition->y = ufoY;
            }
            //delete [] subBoolmap1;
            //delete [] subBoolmap2;
        }
            
        wrapUfo(ufoX, ufoY);
        ufoPosition->x = ufoX;
        ufoPosition->y = ufoY;
        drawGame(ufo, planet, ufoX, ufoY);
    }

    SDL_DestroyTexture(ufo);
    SDL_DestroyTexture(planet);
    IMG_Quit();
    SDL_Quit();
    delete [] boolmap1;
    delete [] boolmap2;

    return 0;
}

//Purpose: Group all SDL initialization
//Note: Only call this function once.
void initializeSDL()
{
    if( SDL_WasInit(SDL_INIT_VIDEO) == 0 )
    {
        SDL_Init(SDL_INIT_VIDEO);
        atexit(SDL_Quit);
    }

    //There is no IMG_WasInit and IMG_Init(0) does not work as expected
    //Multiple calls to IMG_Init(...) only need one call to IMG_Quit, so
    //even though there is a performance cost, I'm going to allow multiple
    //calls to IMG_Init(IMG_INIT_PNG);
    IMG_Init(IMG_INIT_PNG);

    sdlWindow = SDL_CreateWindow("Collision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if( sdlWindow == NULL )
    {
        std::cout << "Error: Could not initialize SDL. Exiting" << std::endl;
        exit(1);
    }
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
    if( sdlRenderer == NULL )
    {
        std::cout << "Error: Could not initialize SDL. Exiting" << std::endl;
        exit(1);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(sdlRenderer, SCREEN_WIDTH,
        SCREEN_HEIGHT);
}
//Method:   Renderer::loadImage(...)
//Purpose:  Load an image from file and store it in internal map
SDL_Texture *loadImage(std::string path)
{
    return loadImage(loadUnoptimizedImage(path));
}

//Method:   Renderer::loadImage(...)
//Purpose:  Store an already loaded image into an internal map
//Note:     If this method changes to freeing an image and REloading it,
//          make sure all the transformations are also freed or updated.
SDL_Texture *loadImage(SDL_Surface *image)
{
    SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer,
        image);
    SDL_FreeSurface(image);

    return sdlTexture;
}

//Method:   Renderer::loadUnoptimizedImage(...)
//Purpose:  Utility method that wraps the SDL_Image IMG_Load(...) function
//          to load an unoptimized image.
SDL_Surface *loadUnoptimizedImage(std::string path)
{
    SDL_Surface *image = IMG_Load(path.c_str());

    if(!image)
    {
        std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    return image;
}

//Purpose:  Detect arrow key presses and respond accordingly. Also detect
//          escape key presses which indicate player wants to quit.
void handleInput(bool &stillPlaying, int &ufoXVelocity, int &ufoYVelocity)
{
    SDL_Event event;

    while( SDL_PollEvent(&event) == true )
    {
        handleArrows(event, ufoXVelocity, ufoYVelocity);
        handleEscape(event, stillPlaying);
        handleQuit(event, stillPlaying);
    }
}

//Purpose:  Detect arrow key presses and change the UFO's velocity
void handleArrows(SDL_Event event, int &ufoXVelocity, int &ufoYVelocity)
{
    if( event.type == SDL_KEYDOWN )
    {
        if( event.key.keysym.sym == SDLK_LEFT )
        {
            ufoXVelocity = UFO_X_VELOCITY_MIN;
        }

        if( event.key.keysym.sym == SDLK_RIGHT )
        {
            ufoXVelocity = UFO_X_VELOCITY_MAX;
        }
    
        if( event.key.keysym.sym == SDLK_UP )
        {
            ufoYVelocity = UFO_Y_VELOCITY_MIN;
        }

        if( event.key.keysym.sym == SDLK_DOWN )
        {
            ufoYVelocity = UFO_Y_VELOCITY_MAX;
        }
    }
    else if( event.type == SDL_KEYUP )
    {
        if( event.key.keysym.sym == SDLK_LEFT )
        {
            ufoXVelocity = UFO_VELOCITY_REST;
        }
        
        if( event.key.keysym.sym == SDLK_RIGHT )
        {
            ufoXVelocity = UFO_VELOCITY_REST;
        }

        if( event.key.keysym.sym == SDLK_UP )
        {
            ufoYVelocity = UFO_VELOCITY_REST;
        }
        
        if( event.key.keysym.sym == SDLK_DOWN )
        {
            ufoYVelocity = UFO_VELOCITY_REST;
        }
    }
}
    
//Purpose:  A module that detects an escape key press and causes the game to
//          exit.
void handleEscape(SDL_Event event, bool &stillPlaying)
{
    if( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE )
    {
        stillPlaying = false;
    }
}    

//Purpose:  A module detects sdl quit call
//Note to students: A full screen application does not have an 'X' button to
//                  close the program. It is still good practice to handle
//                  quit events. There are times when the operating system
//                  wants to terminate a program prematurely, and this
//                  helps that process along.
void handleQuit(SDL_Event event, bool &stillPlaying)
{
    if( event.type == SDL_QUIT )
    {
        stillPlaying = false;
    }
}

//Purpose:  Move the ufo according to its current velocity
//Note to students: This is a general function that will work for both
//                  vertical AND horizontal movements, just pass in
//                  the velocity that cooresponds to the coordinate. For
//                  instance, calling moveUfo(xCoordinate, xVelocity) will
//                  move the ufo horizontally, and calling
//                  moveUfo(yCoordinate, yVelocity) will move it vertically.
void moveUfo(int &coordinate, int velocity)
{
    coordinate = coordinate + velocity;
}

//Purpose:  If the ufo reaches the edge of the screen, teleport him to the
//          opposite side.
void wrapUfo(int &ufoX, int &ufoY)
{
    if( ufoX > SCREEN_WIDTH )
        ufoX = 0 - UFO_WIDTH;
    else if( ufoX < 0 - UFO_WIDTH )
        ufoX = SCREEN_WIDTH;
    if( ufoY > SCREEN_HEIGHT )
        ufoY = 0 - UFO_HEIGHT;
    else if( ufoY < 0 - UFO_HEIGHT )
        ufoY = SCREEN_HEIGHT;
}

//Purpose:  Check if ufo collided with planet
//Note:     Since the ufo and planet are circles, you can check if the distance
//          between the center of each object is less than the radii added
//          together. If so, collision
bool isUfoPlanetCollision(int ufoX, int ufoY)
{
    int ufoCenterX = ufoX + UFO_WIDTH / 2;
    int ufoCenterY = ufoY + UFO_HEIGHT / 2;
    int planetCenterX = PLANET_X_INITIAL + PLANET_WIDTH / 2;
    int planetCenterY = PLANET_Y_INITIAL + PLANET_HEIGHT / 2;
    int collisionDistance = UFO_WIDTH / 2 + PLANET_WIDTH / 2;

    if( distance(ufoCenterY, planetCenterY, ufoCenterX, planetCenterX) <
        collisionDistance )
        return true;

    return false;
}

//Purpose:  Use the distance formula to calculate distance between two points.
int distance(int y2, int y1, int x2, int x1)
{
    return sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

//Purpose:  Draws to the screen the image that we previously loaded
void drawGame(SDL_Texture *ufo, SDL_Texture *planet, 
    int ufoX, int ufoY)
{
    SDL_RenderClear(sdlRenderer);

    SDL_Rect ufoPosition = { ufoX, ufoY, UFO_WIDTH, UFO_HEIGHT };
    SDL_Rect planetPosition = { PLANET_X_INITIAL, PLANET_Y_INITIAL,
        PLANET_WIDTH, PLANET_HEIGHT };

    SDL_RenderCopy(sdlRenderer, ufo, NULL, &ufoPosition);
    SDL_RenderCopy(sdlRenderer, planet, NULL, &planetPosition);

    SDL_RenderPresent(sdlRenderer);
}

