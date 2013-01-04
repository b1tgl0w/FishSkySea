//File:MessageBoxLine.cpp
//Author: John Miner
//Created: 12/30/12
//Purpose: Store a line of text that fits within message box or a given area.

#include <sstream>
#include "../Header/MessageBoxLine.hpp"
#include "../../../Header/Layout.hpp"
#include "../../../Header/Renderer.hpp"
#include "../../../Header/TextRendererElement.hpp"

MessageBoxLine::MessageBoxLine(const Point &position, const Dimension &messageBoxSize,
    const Dimension &lineSize, const Layer &layer) :
    position(position), messageBoxSize(messageBoxSize), lineSize(lineSize),
    layer(layer)
    { }

MessageBoxLine::MessageBoxLine(const MessageBoxLine &rhs) : position(rhs.position),
    messageBoxSize(rhs.messageBoxSize), lineSize(rhs.lineSize), layer(rhs.layer), 
    line(rhs.line) { }

MessageBoxLine &MessageBoxLine::operator=(const MessageBoxLine &rhs)
{
    if( &rhs == this )
        return *this;
    
    position = rhs.position;
    messageBoxSize = rhs.messageBoxSize;
    lineSize = rhs.lineSize;
    layer = rhs.layer;
    line = rhs.line;

    return *this;
}

//Returns false if text exceeds this current line
bool MessageBoxLine::form(TTF_Font *font, std::string &whatsLeft)
{
    int currentWidth = 0;
    int currentHeight = 0;
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
        TTF_SizeText(font, currentLine.c_str(), &currentWidth, &currentHeight);

        std::cout << currentWord << "\t" << position.x + currentWidth << std::endl;
        if( position.x + currentWidth > lineSize.width )
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

    renderer.loadText(line, COLOR, BORDER_SIZE); //Load every time? Or when? FIX!
    TextRendererElement re(line, layer.integer(), position, lineSize);
    layout->drawWhenReady(re);
}

void MessageBoxLine::loadImage(Renderer &renderer)
{
    //No-op, updated text is loaded right before rendering
}

