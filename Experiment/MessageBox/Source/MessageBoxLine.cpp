//File:MessageBoxLine.cpp
//Author: John Miner
//Created: 12/30/12
//Purpose: Store a line of text that fits within message box or a given area.
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include <sstream>
#include "../Header/MessageBoxLine.hpp"
#include "../../../Header/Layout.hpp"
#include "../../../Header/Renderer.hpp"
#include "../../../Header/TextRendererElement.hpp"
#include "../../../Header/DirectGraphicStrategy.hpp"
#include "../../../Header/DirectFilledRectangleGraphic.hpp"
#include "../../../Header/DirectRendererElement.hpp"

MessageBoxLine::MessageBoxLine(const Point &position, const Dimension &messageBoxSize,
    const Dimension &lineSize, const Layer &layer, Uint32 bgColor) :
    position(position), messageBoxSize(messageBoxSize), lineSize(lineSize),
    layer(layer), uuid(boost::uuids::random_generator()()),
    identifier(boost::uuids::to_string(uuid)), bgColor(bgColor)
    { }

MessageBoxLine::MessageBoxLine(const MessageBoxLine &rhs) : position(rhs.position),
    messageBoxSize(rhs.messageBoxSize), lineSize(rhs.lineSize), layer(rhs.layer), 
    line(rhs.line), uuid(rhs.uuid), identifier(rhs.identifier), bgColor(rhs.bgColor)
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

    return *this;
}

//Returns false if text exceeds this current line
bool MessageBoxLine::form(TTF_Font *font, std::string &whatsLeft)
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
        //TTF_SizeText(font, currentLine.c_str(), &currentWidth, &currentHeight);
        lineCharacters += currentWord.size();

        //std::cout << currentWord << "\t" << position.x + currentWidth << std::endl;
        if( lineCharacters > MAX_LINE_CHARACTERS )
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

    return !(whatsLeft.empty());
}

void MessageBoxLine::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    const SDL_Color COLOR = { 0xFF, 0xFF, 0xFF, 0xFF };
    const int BORDER_SIZE = 0;
    const Layer LAYER = Layer::SCORE();

    if( line.size() > 0 )
    {
        renderer.loadText(line, COLOR, BORDER_SIZE); //Load every time? Or when? FIX!
        TextRendererElement re(line, layer.integer() + 1, position, lineSize);
        layout->drawWhenReady(re);
    }
    //Otherwise, blank

    Point origin = { 0.0, 0.0 };
    boost::shared_ptr<DirectGraphicStrategy> dgs(new DirectFilledRectangleGraphic(
        origin, lineSize, bgColor));
    DirectRendererElement re2(identifier, layer.integer(), origin,
        lineSize, dgs);
    layout->drawWhenReady(re2);
}

void MessageBoxLine::loadImage(Renderer &renderer)
{
    //No-op, updated text is loaded right before rendering
}

