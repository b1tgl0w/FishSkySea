//File: DirectFilledGraphic.cpp
//Author:   John Miner
//Created:  01/04/13
//Purpose:  Draw a filled rectangle directly to the screen
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/DirectFilledRectangleGraphic.hpp"
#include "../Header/Math.hpp"
#include "../Header/Clip.hpp"

DirectFilledRectangleGraphic::DirectFilledRectangleGraphic(const Point &position,
const Dimension &size, const Uint32 color) : position(position), size(size),
    color(color)
{ }

DirectFilledRectangleGraphic::DirectFilledRectangleGraphic(const 
    DirectFilledRectangleGraphic &rhs) : position(rhs.position), size(rhs.size),
    color(rhs.color)
{ }

DirectFilledRectangleGraphic &DirectFilledRectangleGraphic::operator=(const 
    DirectFilledRectangleGraphic &rhs)
{
    if( &rhs == this )
        return *this;

    position = rhs.position;
    size = rhs.size;
    color = rhs.color;

    return *this;
}

DirectFilledRectangleGraphic::~DirectFilledRectangleGraphic()
{
}

void DirectFilledRectangleGraphic::drawToScreen(SDL_Surface *screen, const Point 
    &position, const Dimension &size, const Clip &clipObject)
{
    DimensionPercent dimensionPercent(size.width / this->size.width,
        size.height / this->size.height);
    this->size.width *= dimensionPercent.widthPercent;
    this->size.height *= dimensionPercent.heightPercent;

    this->position.x += position.x;
    this->position.y += position.y;

    SDL_Rect rect = { this->position.x, this->position.y,
        this->size.width, this->size.height };

    SDL_FillRect(screen, &rect, color);

}

