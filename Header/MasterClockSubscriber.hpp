//File: MasterClockSubscriber.hpp
//Author:   John Miner
//Created:  11/29/11
//Modified: 11/29/11
//Purpose:  Interface that takes the role of observer in observer pattern.
//          Receives elapsed time notifications every frame.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef MASTER_CLOCK_SUBSCRIBER_HPP_
#define MASTER_CLOCK_SUBSCRIBER_HPP_

#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif

class MasterClockSubscriber
{
public:
    virtual void clockTick(Uint32 elapsedTime) = 0;
};

#endif

