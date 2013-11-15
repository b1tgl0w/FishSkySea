//File: Song.hpp
//Author:   John Miner
//Created:  11/15/13
//Purpose:  A song played during the game.
//Copyright 2013 John Miner
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
#include "../Header/Song.hpp"

Song::Song(const std::string &pathname) : pathname(pathname)
{
    music = Mix_LoadMUS(pathname.c_str());
    
    if( !music )
        std::cout << "Error loading music " << Mix_GetError() << std::endl;
}

bool Song::loaded(const std::string &pathname)
{
    return this->pathname == pathname;
}

void Song::play()
{
    //if( Mix_FadeInMusic(music, 1, FADE_TIME) == -1 )
    if( Mix_PlayMusic(music, 1) == -1 )
        std::cout << "Error playing music " << Mix_GetError() << std::endl;
}

void Song::pause()
{
}

void Song::changeVolume(VOLUME volume)
{
}

void Song::stop()
{
    //Mix_FadeOutMusic(FADE_TIME);
    Mix_HaltMusic();
}

Song::~Song()
{
    stop();
    Mix_FreeMusic(music);
    music = NULL;
}

