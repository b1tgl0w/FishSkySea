//File: MessageBox.hpp
//Author: John Miner
//Created: 12/31/12
//Purpose:  Display text within a black rectangle.

#ifndef MESSAGE_BOX_HPP_
#define MESSAGE_BOX_HPP_

#include <string>
#include <SDL/SDL_ttf.h>
#include "boost/shared_ptr.hpp"
#include "../../Header/Graphic.hpp"
#include "../../Header/Dimension.hpp"
#include "../Header/MessageBoxLine.hpp"
#include "../../Header/GridLayout.hpp"
#include "../../Header/CenterLayout.hpp"
#include "../../Header/ScaleClipFit.hpp"

class MessageBox : public Graphic
{
public:
    MessageBox(TTF_Font *font, const std::string &text, 
        const Dimension &size, Uint32 color, bool border);
    MessageBox(const MessageBox &rhs);
    MessageBox &operator=(const MessageBox &rhs);
    static const bool BORDER();
    static const bool NO_BORDER();
    boost::shared_ptr<Layout> layoutToAttach();
    bool advance();
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
private:
    void formLines();
    void createLayouts();
    std::vector<MessageBoxLine> lines;
    boost::shared_ptr<GridLayout> gridLayout;
    std::list<boost::shared_ptr<CenterLayout> > layouts;
    boost::shared_ptr<ScaleClipFit> fitStrategy;
    std::string text;
    TTF_Font *font;
    Dimension size;
    Uint32 color;
    bool border;
};

#endif

