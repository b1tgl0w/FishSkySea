//File: Game.cpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Manage the game
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Game.hpp"

Game::Game()
{
    initialize();
}

void Game::initialize()
{
    quit = false;
}

bool Game::shouldQuit()
{
    return quit;
}

void Game::keyPressed(const SDLKey &key)
{
}

void Game::keyReleased(const SDLKey &key)
{
    if( key == SDLK_ESCAPE )
        quit = true;
}


