//File: Game.hpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Manage the game
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef GAME_HPP_
#define GAME_HPP_

#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "KeyboardSubscriber.hpp"

class Game : public KeyboardSubscriber
{
public:
    Game();
    bool shouldQuit();
    void keyPressed(const SDLKey &key);
    void keyReleased(const SDLKey &key);
protected:
    void initialize();
private:
    bool quit;
};

#endif

