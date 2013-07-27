//File: DirectLineGraphic.cpp
//Author:   John Miner
//Created:  03/20/12
//Modified: 03/20/12
//Purpose:  Draw a line directly to the screen
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/DirectLineGraphic.hpp"
#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/Math.hpp"

DirectLineGraphic::DirectLineGraphic(const Point &p1, const Point &p2,
    const Uint32 color)
{
    initialize(p1, p2, color);
}

DirectLineGraphic::DirectLineGraphic(const DirectLineGraphic &rhs)
{
    initialize(rhs.p1, rhs.p2, rhs.color);
}

DirectLineGraphic &DirectLineGraphic::operator=(const DirectLineGraphic &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.p1, rhs.p2, rhs.color);

    return *this;
}

DirectLineGraphic::~DirectLineGraphic()
{
    dispose();
}

void DirectLineGraphic::initialize(const Point &p1, const Point &p2, const Uint32
    color)
{
    this->p1 = p1;
    this->p2 = p2;
    this->color = color;
}

void DirectLineGraphic::dispose()
{
}

void DirectLineGraphic::drawToScreen(SDL_Surface *screen, const Point &position,
    const Dimension &size, const Clip &clipObject)
{
    const int LINE_SEGMENT_WIDTH = 1; //Make variable
    const int LINE_SEGMENT_HEIGHT = 1; //Make variable

    Point localP1;
    Point localP2;
    
    if( p1.x < p2.x )
    {
        localP1 = p1;
        localP2 = p2;
    }
    else
    {
        localP1 = p2;
        localP2 = p1;
    }

    //ToDo, don't base off screen
    DimensionPercent dimensionPercent(size.width / (double) screen->w,
        size.height / (double) screen->h);
    localP1.x *= dimensionPercent.widthPercent;
    localP1.y *= dimensionPercent.heightPercent;
    localP2.x *= dimensionPercent.widthPercent;
    localP2.y *= dimensionPercent.heightPercent;

    localP1.x += position.x; //Position is already scaled
    localP1.y += position.y;
    localP2.x += position.x;
    localP2.y += position.y;

    SDL_Rect currentRectangle = { localP1.x, localP1.y,
        LINE_SEGMENT_WIDTH, LINE_SEGMENT_HEIGHT };

    double rise = Math::calculateRise(localP1, localP2);
    double run = Math::calculateRun(localP1, localP2);
    double greaterCalculation = 
        Math::greater(Math::greater(localP2.x, localP2.y), Math::greater(localP1.x,localP1.y));
    double condition1 = (localP2.x - localP1.x) / (run / greaterCalculation);
    double condition2 = (localP2.y - localP1.y ) / (rise / greaterCalculation);
    double calculation1Part = (run / greaterCalculation);
    double calculation2Part = (rise / greaterCalculation);

    for(double curX = localP1.x, i = 0, curY = localP1.y;
        i < condition1 ||
        i < condition2;
        curX = localP1.x + i * calculation1Part,
        curY = localP1.y + i * calculation2Part,
        ++i)
    {
        currentRectangle.x = curX;
        currentRectangle.y = curY;
        SDL_FillRect(screen, &currentRectangle, color);
    }
}

