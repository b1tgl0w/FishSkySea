//File:MessageBoxLine.hpp
//Author: John Miner
//Created: 12/30/12
//Purpose: Store a line of text that fits within message box or a given area.
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef MESSAGE_BOX_LINE_HPP_
#define MESSAGE_BOX_LINE_HPP_

#ifdef linux
#include <SDL/SDL_ttf.h>
#else
#include <SDL_ttf.h>
#endif
#include <string>
#include "boost/uuid/uuid.hpp"
#include "../../../Header/Point.hpp"
#include "../../../Header/Dimension.hpp"
#include "../../../Header/Graphic.hpp"
#include "../../../Header/Layer.hpp"

class Layout;
class Renderer;

class MessageBoxLine : public Graphic
{
public:
    //Position relative to MB top-left
    explicit MessageBoxLine(const Point &position, const Dimension &messageBoxSize,
        const Dimension &lineSize, const Layer &layer, Uint32 bgColor);
    MessageBoxLine(const MessageBoxLine &rhs);
    MessageBoxLine &operator=(const MessageBoxLine &rhs);
    bool form(TTF_Font *font, std::string &leftOver); 
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
    //Position relative to MB top-left
};

#endif

