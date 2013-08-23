//File:MessageBoxLine.hpp
//Author: John Miner
//Created: 12/30/12
//Purpose: Store a line of text that fits within message box or a given area.
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

#ifndef MESSAGE_BOX_LINE_HPP_
#define MESSAGE_BOX_LINE_HPP_

#include <SDL2/SDL_ttf.h>
#include <string>
#include "boost/uuid/uuid.hpp"
#include "boost/shared_ptr.hpp"
#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/Graphic.hpp"
#include "../Header/Layer.hpp"
#include "../Header/FontSize.hpp"

class Layout;
class Renderer;

class MessageBoxLine : public Graphic
{
public:
    //Position relative to MB top-left
    explicit MessageBoxLine(const Point &position, const Dimension &messageBoxSize,
        const Dimension &lineSize, const Layer &layer, Uint32 bgColor,
        const FontSize &fontSize);
    MessageBoxLine(const MessageBoxLine &rhs);
    MessageBoxLine &operator=(const MessageBoxLine &rhs);
    bool form(std::string &leftOver, Renderer &renderer); 
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
private:
    Point position;
    Dimension messageBoxSize;
    Dimension lineSize;
    Layer layer;
    std::string line;
    boost::uuids::uuid uuid;
    std::string identifier;
    Uint32 bgColor;
    FontSize fontSize;
    Dimension originalLineSize;
    //Position relative to MB top-left
};

#endif

