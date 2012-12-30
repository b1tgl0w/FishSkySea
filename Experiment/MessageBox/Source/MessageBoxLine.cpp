//File:MessageBoxLine.cpp
//Author: John Miner
//Created: 12/30/12
//Purpose: Store a line of text that fits within message box or a given area.

#include <sstream>
#include "../Header/MessageBoxLine.hpp"
#include "../../Header/Layout.hpp"
#include "../../Header/Renderer.hpp"

MessageBoxLine::MessageBoxLine(const Point &position, const Dimension &messageBoxSize,
    const Dimension &lineSize) :
    position(position), messageBoxSize(messageBoxSize), lineSize(lineSize) { }

MessageBoxLine::MessageBoxLine(const MessageBoxLine &rhs) : position(rhs.position),
    messageBoxSize(rhs.messageBoxSize), lineSize(rhs.lineSize), line(rhs.line)

MessageBoxLine &MessageBoxLine::operator=(const MessageBoxLine &rhs)
{
    if( &rhs == this )
        return *this;
    
    position = rhs.position;
    messageBoxSize = rhs.messageBoxSize;
    lineSize = rhs.lineSize;
    line = rhs.line;

    return *this;
}

//Returns false if its height is below bottom of box
bool MessageBoxLine::form(TTF_Font *font, const std::string &text, std::string 
    &whatsLeft)
{
    int currentWidth = 0;
    int currentHeight = 0;
    bool atLeastOneThingFits = false;
    std::string currentLine;
    std::string previousLine;
    std::string currentWord;
    std::stringstream stringStream(text);

    while( position.x + currentWidth < messageBoxSize.width && position.y + 
        currentHeight < messageBoxSize.height )
    {
        //This will be empty first iter, remain one iteration behind
        previousLine += currentWord; 
        stringStream >> currentWord;
        currentWord += ' ';
        currentLine += currentWord;
        TTF_SizeText(font, currentLine.c_str(), &currentWidth, &currentHeight);
    }

    line = previousLine;
    whatsLeft = currentWord + stringStream.str();

    return atLeastOneThingFits;
}

void MessageBoxLine::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    const SDL_Color COLOR = { 0x17, 0x00, 0x24, 0x00 };
    const int BORDER_SIZE = 0;
    const Layer LAYER = Layer::SCORE();

    renderer.loadText(line, COLOR, BORDER_SIZE); //Load every time? Or when? FIX!
    TextRendererElement re(line, LAYER.integer(), position, lineSize);
    layout->drawWhenReady(re);
}

void MessageBoxLine::loadImage(Renderer &renderer)
{
    //No-op, updated text is loaded right before rendering
}

