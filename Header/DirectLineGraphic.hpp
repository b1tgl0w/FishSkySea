//File: DirectLineGraphic.hpp
//Author:   John Miner
//Created:  03/20/12
//Modified: 03/20/12
//Purpose:  Draw a line directly to the screen
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef DIRECT_LINE_GRAPHIC_H_
#define DIRECT_LINE_GRAPHIC_H_

#include <SDL/SDL.h> // changed back to <SDL/SDL.h>
#include "DirectGraphicStrategy.hpp"
#include "Point.hpp"
#include "Dimension.hpp"

class DirectLineGraphic : public DirectGraphicStrategy
{
public:
    explicit DirectLineGraphic(const Point &p1, const Point &p2,
        const Uint32 color);
    DirectLineGraphic(const DirectLineGraphic &rhs);
    DirectLineGraphic &operator=(const DirectLineGraphic &rhs);
    ~DirectLineGraphic();
    void drawToScreen(SDL_Surface *screen, const Point &position,
        const Dimension &size, const Clip &clipObject);
protected:
    void initialize(const Point &p1, const Point &p2, const Uint32 color);
    void dispose();
private:
    DirectLineGraphic();
    Point p1;
    Point p2;
    Uint32 color;
};

#endif

