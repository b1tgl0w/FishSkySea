//File: MessageBox.hpp
//Author: John Miner
//Created: 12/31/12
//Purpose:  Display text within a black rectangle.
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

#ifndef MESSAGE_BOX_HPP_
#define MESSAGE_BOX_HPP_

#include <string>
#include <SDL2/SDL_ttf.h>
#include "boost/shared_ptr.hpp"
#include "boost/uuid/uuid.hpp"
#include <string>
#include "../Header/Graphic.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/MessageBoxLine.hpp"
#include "../Header/GridLayout.hpp"
#include "../Header/CenterLayout.hpp"
#include "../Header/ScaleClipFit.hpp"
#include "../Header/ClipFit.hpp"
#include "../Header/Layer.hpp"
#include "../Header/FontSize.hpp"

class Renderer;
class Dimension;
class Point;

class MessageBox : public Graphic
{
public:
    MessageBox(const std::string &text, 
        const Dimension &lineSize, Uint32 color, bool border,
        const Layer &layer, boost::shared_ptr<Renderer> &renderer,
        const FontSize &fontSize, const int numberOfLines);
    MessageBox(const MessageBox &rhs);
    MessageBox &operator=(const MessageBox &rhs);
    static const bool BORDER();
    static const bool NO_BORDER();
    boost::shared_ptr<Layout> layoutToAttach();
    bool advance();
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
    void createLayouts();
    void moveTo(const Point &position);
    void show(bool shouldShow);
private:
    bool formLines();
    std::string text;
    Dimension size;
    Dimension lineSize;
    Uint32 color;
    bool border;
    std::vector<MessageBoxLine> lines;
    boost::shared_ptr<GridLayout> gridLayout;
    std::list<boost::shared_ptr<CenterLayout> > layouts;
    boost::shared_ptr<ScaleClipFit> fitStrategy;
    Layer layer;
    boost::uuids::uuid uuid;
    std::string identifier;
    boost::shared_ptr<Renderer> renderer;
    FontSize fontSize;
    int numberOfLines;
    bool shouldShow;
    std::string originalText;
};

#endif

