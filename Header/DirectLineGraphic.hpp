//File: DirectLineGraphic.hpp
//Author:   John Miner
//Created:  03/20/12
//Modified: 03/20/12
//Purpose:  Draw a line directly to the screen
//Copyright 2012 John Miner
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

#ifndef DIRECT_LINE_GRAPHIC_H_
#define DIRECT_LINE_GRAPHIC_H_

#include <SDL2/SDL.h> 
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
    void drawToScreen(SDL_Renderer *sdlRenderer, const Point &position,
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

