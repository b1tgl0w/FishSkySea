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

