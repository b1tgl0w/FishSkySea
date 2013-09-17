//File:MessageBoxLine.cpp
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

#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/lexical_cast.hpp"
#include <sstream>
#include "../Header/MessageBoxLine.hpp"
#include "../Header/Layout.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/TextRendererElement.hpp"
#include "../Header/DirectGraphicStrategy.hpp"
#include "../Header/DirectFilledRectangleGraphic.hpp"
#include "../Header/DirectRendererElement.hpp"
#include "../Header/StandardUnit.hpp"

MessageBoxLine::MessageBoxLine(const Point &position, const Dimension &messageBoxSize,
    const Dimension &lineSize, const Layer &layer, Uint32 bgColor,
    const FontSize &fontSize) :
    position(position), messageBoxSize(messageBoxSize), lineSize(lineSize),
    layer(layer), line(), uuid(boost::uuids::random_generator()()),
    identifier(boost::uuids::to_string(uuid)), bgColor(bgColor),
    fontSize(fontSize), originalLineSize(lineSize)
    //identifier(boost::lexical_cast<std::string>(uuid)), bgColor(bgColor) //for debian, old boost
    { }

MessageBoxLine::MessageBoxLine(const MessageBoxLine &rhs) : position(rhs.position),
    messageBoxSize(rhs.messageBoxSize), lineSize(rhs.lineSize), layer(rhs.layer), 
    line(rhs.line), uuid(rhs.uuid), identifier(rhs.identifier), bgColor(rhs.bgColor),
    fontSize(rhs.fontSize), originalLineSize(rhs.originalLineSize)
    { }

MessageBoxLine &MessageBoxLine::operator=(const MessageBoxLine &rhs)
{
    if( &rhs == this )
        return *this;
    
    position = rhs.position;
    messageBoxSize = rhs.messageBoxSize;
    lineSize = rhs.lineSize;
    layer = rhs.layer;
    line = rhs.line;
    uuid = rhs.uuid;
    identifier = rhs.identifier;
    bgColor = rhs.bgColor;
    fontSize = rhs.fontSize;
    originalLineSize = rhs.originalLineSize;

    return *this;
}

//Returns false if text exceeds this current line
bool MessageBoxLine::form(std::string &whatsLeft, Renderer &renderer)
{
    const int MAX_LINE_CHARACTERS = 78;
    int currentWidth = 0;
    int currentHeight = 0;
    int lineCharacters = 0;
    std::string currentLine;
    std::string previousLine;
    std::string currentWord;
    std::stringstream stringStream(whatsLeft);
    bool doesntFit = false;
    whatsLeft.clear();

    while(true)// && position.y + 
        //currentHeight < lineSize.height )
    {
        //This will be empty first iter, remain one iteration behind

        if( !(stringStream >> currentWord) )
            break;

        currentWord += ' ';
        currentLine += currentWord;
        renderer.sizeText(currentLine, currentWidth, currentHeight,
            fontSize);
        lineCharacters += currentWord.size();

        //std::cout << currentWord << "\t" << position.x + currentWidth << std::endl;
        if( lineCharacters > MAX_LINE_CHARACTERS || position.x + currentWidth >
            lineSize.width)
        {
            doesntFit = true;
            break;
        }
    }
    
    line = currentLine;

    if( doesntFit )
    {
        whatsLeft.clear();

        while( stringStream >> currentWord )
        {
            whatsLeft += currentWord;
            whatsLeft += ' ';
        }
    }

    //return !(whatsLeft.empty());
    return !(whatsLeft.empty()) && doesntFit;
}

void MessageBoxLine::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    const SDL_Color COLOR = StandardUnit::SDL_WHITE();
    const int BORDER_SIZE = 0;

    Point origin(0.0, 0.0);
    boost::shared_ptr<DirectGraphicStrategy> dgs(new DirectFilledRectangleGraphic(
        origin, originalLineSize, bgColor));
    DirectRendererElement re2(identifier, layer.integer(), origin,
        originalLineSize, dgs);
    layout->drawWhenReady(re2);

    if( line.size() > 0 )
    {
        int width = 0;
        int height = 0;
        renderer.sizeText(line, width, height, fontSize);
        if( width < lineSize.width )
            lineSize.width = width;
        if( height < lineSize.height )
            lineSize.height = height;
        renderer.loadText(line, COLOR, BORDER_SIZE, fontSize); //Load every time? Or when? FIX!
        TextRendererElement re(line, layer.integer() + 1, position, lineSize,
            fontSize);
        layout->drawWhenReady(re);
    }
}

void MessageBoxLine::loadImage(Renderer &renderer)
{
    //No-op, updated text is loaded right before rendering
}

