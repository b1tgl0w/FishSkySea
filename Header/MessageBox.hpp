//File: MessageBox.hpp
//Author: John Miner
//Created: 12/31/12
//Purpose:  Display text within a black rectangle.
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef MESSAGE_BOX_HPP_
#define MESSAGE_BOX_HPP_

#include <string>
#ifdef linux
#include <SDL/SDL_ttf.h>
#else
#include <SDL_ttf.h>
#endif
#include "boost/shared_ptr.hpp"
#include "boost/uuid/uuid.hpp"
#include <string>
#include "../Header/Graphic.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/MessageBoxLine.hpp"
#include "../Header/GridLayout.hpp"
#include "../Header/CenterLayout.hpp"
#include "../Header/ClipFit.hpp"
#include "../Header/Layer.hpp"

class Renderer;
class Dimension;
class Point;

class MessageBox : public Graphic
{
public:
    MessageBox(const std::string &text, 
        const Dimension &size, const Dimension &lineSize, Uint32 color, bool border,
        const Layer &layer, boost::shared_ptr<Renderer> &renderer);
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
private:
    bool formLines();
    boost::shared_ptr<TTF_Font> font;
    std::string text;
    Dimension size;
    Dimension lineSize;
    Uint32 color;
    bool border;
    std::vector<MessageBoxLine> lines;
    boost::shared_ptr<GridLayout> gridLayout;
    std::list<boost::shared_ptr<CenterLayout> > layouts;
    boost::shared_ptr<ClipFit> fitStrategy;
    Layer layer;
    boost::uuids::uuid uuid;
    std::string identifier;
    boost::shared_ptr<Renderer> renderer;
};

#endif

