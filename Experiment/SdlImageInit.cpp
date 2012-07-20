//File: SdlImgInit.cpp
//Author:   John Miner
//Created:  09/28/11
//Modified: 09/28/11
//Purpose:  lSDL_image does not have a was init function. See if calling
//          IMG_Init(0) works similarly. Note: According to the documentation,
//          you can call IMG_Init multiple times and only need one IMG_Quit.
//Note:     Might as well test SDL_WasInit too.
//Results:  IMG_Init(0) did not produce the results I wanted. Instead, I'm
//          just going to call IMG_Init(IMG_INIT_PNG) every time the renderer
//          is constructed. This is okay because there only needs to be one
//          call to IMG_Quit(). I probably won't even construct multiple
//          renderers, even though it's not a singleton
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"

int main( int argc, char ** argv )
{

    if( SDL_WasInit(SDL_INIT_EVERYTHING) == 0 )
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        std::cout << "SDL_Init called" << std::endl;
    }

    if( SDL_WasInit(SDL_INIT_EVERYTHING) == 0 )
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        std::cout << "SDL_Init called" << std::endl;
    }

    if( true ) //IMG_Init(0) does not work as expected
    {
        std::cout << "IMG_Init called" << std::endl;
        IMG_Init(IMG_INIT_PNG);
    }

    if( true ) //IMG_Init(0) does not work as expected
    {
        std::cout << "IMG_Init called" << std::endl;
        IMG_Init(IMG_INIT_PNG);
    }

    SDL_Quit();
    IMG_Quit();

    return EXIT_SUCCESS;
}

