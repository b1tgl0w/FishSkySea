//File: DirectFilledGraphic.cpp
//Author:   John Miner
//Created:  01/04/13
//Purpose:  Draw a filled rectangle directly to the screen
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/

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

void DirectFilledRectangleGraphic::drawToScreen(SDL_Renderer *sdlRenderer, const Point 
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

    Uint8 red = (color >> 24) & 0xFF;
    Uint8 green = (color >> 16) & 0xFF;
    Uint8 blue = (color >> 8) & 0xFF;
    Uint8 alpha = color & 0xFF;

    SDL_SetRenderDrawColor(sdlRenderer, red, green, blue, alpha);
    SDL_RenderFillRect(sdlRenderer, &rect);
}

