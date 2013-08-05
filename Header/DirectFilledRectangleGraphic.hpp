//File: DirectFilledRectangleGraphic.hpp
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

