//File: MasterInputSubscriber.hpp
//Author:   John Miner
//Created:  11/29/11
//Modified: 11/29/11
//Purpose:  Interface that takes role of observer in observer pattern. Subscribes
//          to notifications from an object that polls SDL_Events.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef MASTER_INPUT_SUBSCRIBER_HPP_
#define MASTER_INPUT_SUBSCRIBER_HPP_

#include <SDL/SDL.h> // changed back to <SDL/SDL.h>

class MasterInputSubscriber
{
public:
    virtual void inputEvent(const SDL_Event &e) = 0;
};

#endif

