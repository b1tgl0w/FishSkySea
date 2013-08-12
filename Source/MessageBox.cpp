//File: MessageBox.cpp
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

#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/lexical_cast.hpp" //for debian
#include "../Header/MessageBox.hpp"
#include "../Header/ScaleClipFit.hpp"
#include "../Header/DirectGraphicStrategy.hpp"
#include "../Header/DirectFilledRectangleGraphic.hpp"
#include "../Header/DirectRendererElement.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"

const bool MessageBox::BORDER()
{
    static const bool TMP_BORDER = true;
    return TMP_BORDER;
}

const bool MessageBox::NO_BORDER()
{
    static const bool TMP_NO_BORDER = false;
    return TMP_NO_BORDER;
}

MessageBox::MessageBox(const std::string &text, 
    const Dimension &lineSize, Uint32 color, bool border,
    const Layer &layer, boost::shared_ptr<Renderer> &renderer,
    const FontSize &fontSize, const int numberOfLines) 
    : text(text), size(lineSize.width, lineSize.height * numberOfLines),
    lineSize(lineSize), color(color),  border(border), lines(), gridLayout(),
    layouts(), fitStrategy(new ClipFit), layer(layer), 
    uuid(boost::uuids::random_generator()()),
    identifier(boost::uuids::to_string(uuid)),
    //identifier(boost::lexical_cast<std::string>(uuid)), //for debian, old boost
    renderer(renderer), fontSize(fontSize), numberOfLines(numberOfLines),
    shouldShow(true)
{
    formLines();
    createLayouts();
}

MessageBox::MessageBox(const MessageBox &rhs) : text(rhs.text),
    size(rhs.size), lineSize(rhs.lineSize), color(rhs.color), border(rhs.border), 
    lines(rhs.lines), gridLayout(rhs.gridLayout), layouts(rhs.layouts),
    fitStrategy(rhs.fitStrategy),
    layer(rhs.layer), uuid(rhs.uuid), identifier(rhs.identifier),
    renderer(rhs.renderer), fontSize(rhs.fontSize), numberOfLines(
    rhs.numberOfLines), shouldShow(rhs.shouldShow)
{ }

MessageBox &MessageBox::operator=(const MessageBox &rhs)
{
    if( &rhs == this )
        return *this;

    text = rhs.text;
    size = rhs.size;
    lineSize = rhs.lineSize;
    color = rhs.color;
    border = rhs.border;
    lines = rhs.lines;
    gridLayout = rhs.gridLayout;
    layouts = rhs.layouts;
    fitStrategy = rhs.fitStrategy;
    layer = rhs.layer;
    uuid = rhs.uuid;
    identifier = rhs.identifier;
    renderer = rhs.renderer;
    fontSize = rhs.fontSize;
    numberOfLines = rhs.numberOfLines;
    shouldShow = rhs.shouldShow;

    return *this;
}

boost::shared_ptr<Layout> MessageBox::layoutToAttach()
{
    boost::shared_ptr<Layout> tmp(gridLayout);
    //std::cout << gridLayout->position.y << "\t";
    return tmp;
}

bool MessageBox::advance()
{
    if( shouldShow == false )
        return true;

    if( lines.empty() )
        return false;

    if (formLines() == false )
        return false;
    
    return true;
}

void MessageBox::createLayouts()
{
    layouts.clear();
    boost::shared_ptr<GridLayout> newGridLayout(new GridLayout(lines.size(), 
        1));
    gridLayout = newGridLayout;
    Point cell( 0.0, 0.0);
    for( std::vector<MessageBoxLine>::iterator it = lines.begin(); it != lines.end();
        ++it )
    {
        boost::shared_ptr<CenterLayout> currentLayout(new CenterLayout(
            fitStrategy));
        boost::shared_ptr<Layout> superCurrentLayout(currentLayout);
        gridLayout->addLayout(superCurrentLayout, cell);
        layouts.push_back(currentLayout);
        ++(cell.y);
    }
}

bool MessageBox::formLines()
{
    lines.clear();
    bool notFull = true;
    //Let the layout manager take care of line position. All lines 0, 0
    Point position(0.0, 0.0); 
    
    while( notFull == true && !(text.empty()) && (lines.size() + 1) * 
        lineSize.height <= size.height )
    {
        MessageBoxLine currentLine(position, size, lineSize, layer, color,
            fontSize);
        notFull = currentLine.form(text, *renderer);
        lines.push_back(currentLine);
    }

    while( lines.size() < numberOfLines )
    {
        MessageBoxLine currentLine(position, size, lineSize, layer, color,
            fontSize);
        lines.push_back(currentLine);
    }

    return !notFull;
}

void MessageBox::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    if( shouldShow == false )
        return;

    std::list<boost::shared_ptr<CenterLayout> >::iterator layoutIterator =
        layouts.begin();

    for( std::vector<MessageBoxLine>::iterator it = lines.begin(); it !=
        lines.end() && layoutIterator != layouts.end(); ++it, ++layoutIterator)
    {
        boost::shared_ptr<Layout> superCurrentLayout(*layoutIterator);
        it->draw(superCurrentLayout, renderer);
    }
}

void MessageBox::loadImage(Renderer &renderer)
{
    //No-op, direct graphic strategy created and used during draw
}

void MessageBox::moveTo(const Point &position)
{
    gridLayout->moveTo(position);
}

void MessageBox::show(bool shouldShow)
{
    this->shouldShow = shouldShow;
}

