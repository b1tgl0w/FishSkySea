//File: DirectGraphicStrategy
//Author:   John Miner
//Created:  03/20/12
//Modified: 03/20/12
//Purpose:  Interface for primatives/images that are drawn directly to the screen
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef DIRECT_GRAPHIC_STRATEGY_H_
#define DIRECT_GRAPHIC_STRATEGY_H_

#include <SDL/SDL.h>
#include "boost/shared_ptr.hpp"
#include "Point.hpp"
#include "Dimension.hpp"
#include "Clip.hpp"

class DirectGraphicStrategy
{
public:
    virtual void drawToScreen(SDL_Surface *screen,  const Point &position,
        const Dimension &size, const Clip &clipObject) = 0;
};

#endif

