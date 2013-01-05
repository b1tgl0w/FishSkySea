//File: DirectFilledRectangleGraphic.hpp
//Author:   John Miner
//Created:  01/04/13
//Purpose:  Draw a filled rectangle directly to the screen
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef DIRECT_FILLED_RECTANGLE_GRAPHIC_HPP_
#define DIRECT_FILLED_RECTANGLE_GRAPHIC_HPP_

#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "DirectGraphicStrategy.hpp"
#include "Point.hpp"
#include "Dimension.hpp"

class Clip;

class DirectFilledRectangleGraphic : public DirectGraphicStrategy
{
public:
    explicit DirectFilledRectangleGraphic(const Point &position, const Dimension &size,
        const Uint32 color);
    DirectFilledRectangleGraphic(const DirectFilledRectangleGraphic &rhs);
    DirectFilledRectangleGraphic &operator=(const DirectFilledRectangleGraphic &rhs);
    ~DirectFilledRectangleGraphic();
    void drawToScreen(SDL_Surface *screen, const Point &position,
        const Dimension &size, const Clip &clipObject);
private:
    DirectFilledRectangleGraphic();
    Point position;
    Dimension size;
    Uint32 color;
};

#endif

