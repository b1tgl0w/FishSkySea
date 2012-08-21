//File: MouseSubscriber.hpp
//Author:   John Miner
//Created:  04/13/12
//Purpose:  Listen for mouse clicks and movement
//(C) 2012 John Miner
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef MOUSE_SUBSCRIBER_HPP_
#define MOUSE_SUBSCRIBER_HPP_

#include <SDL/SDL.h> // changed back to <SDL/SDL.h>
#include "Point.hpp"

class MouseSubscriber
{
public:
    virtual void mousePressed(Uint8 button,
        const Point &position) = 0;
    virtual void mouseReleased(Uint8 button,
        const Point &position) = 0;
    virtual void mouseMoved(const Point &position) = 0;
};

#endif

