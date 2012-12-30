//File:MessageBoxLine.hpp
//Author: John Miner
//Created: 12/30/12
//Purpose: Store a line of text that fits within message box or a given area.

#ifndef MESSAGE_BOX_LINE_HPP_
#define MESSAGE_BOX_LINE_HPP_

#include <SDL/SDL_TTF.h>
#include <string>
#include "../../Header/Point.hpp"
#include "../../Header/Dimension.hpp"
#include "../Header/Justify.hpp"
#include "../../Header/Graphic.hpp"

class Layout;
class Renderer;

class MessageBoxLine : public Graphic
{
public:
    //Position relative to MB top-left
    explicit MessageBoxLine(const Point &position, const Dimension &messageBoxSize,
        const Dimension &lineSize);
    MessageBoxLine(const MessageBoxLine &rhs);
    MessageBoxLine &operator=(const MessageBoxLine &rhs);
    bool form(TTF_Font *font, const std::string &text, std::string &leftOver); 
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
private:
    std::string line;
    Dimension messageBoxSize;
    Dimension lineSize;
    //Position relative to MB top-left
    Point position;
};

#endif

