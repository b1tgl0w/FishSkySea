//File: Game.hpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Manage the game
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SDL/SDL.h> // changed back to <SDL/SDL.h>
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

