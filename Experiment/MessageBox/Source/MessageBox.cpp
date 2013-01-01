//File: MessageBox.cpp
//Author: John Miner
//Created: 12/31/12
//Purpose:  Display text within a black rectangle.

#include "../Header/MessageBox.hpp"

static const bool MessageBox::BORDER()
{
    static const bool TMP_BORDER = true;
    return TMP_BORDER;
}

static const bool MessageBox::NO_BORDER()
{
    static const bool TMP_NO_BORDER = false;
    return TMP_NO_BORDER;
}

MessageBox::MessageBox(TTF_Font *font, const std::string &text, 
    const Dimension &size, Uint32 color, bool border) : font(font), text(text),
    size(size), color(color), border(border)
{
    formLines();
    createLayouts();
}

MessageBox::MessageBox(const MessageBox &rhs) : font(rhs.font), text(rhs.text),
    size(rhs.size), color(rhs.color), border(rhs.border), lines(rhs.lines),
    gridLayout(rhs.gridLayout), layouts(rhs.layouts) { }

MessageBox &MessageBox::operator=(const MessageBox &rhs)
{
    if( &rhs == this )
        return *this;

    font = rhs.font;
    text = rhs.text;
    size = rhs.size;
    color = rhs.color;
    border = rhs.border;
    lines = rhs.lines;
    gridLayout = rhs.gridLayout;
    layouts = rhs.layouts;

    return *this;
}

boost::shared_ptr<Layout> MessageBox::layoutToAttach()
{
    return gridLayout;
}

bool MessageBox::advance()
{
    if( lines.empty() )
        return false;

    if (formLines() == false )
        return false;
    
    return true;
}

void MessageBox::createLayouts()
{
    layouts.clear();
    boost::shared_ptr<GridLayout> newGridLayout(new GridLayout(layouts.size(), 
        1));
    gridLayout = newGridLayout;
    Point cell = { 0.0, 0.0 };

    for( std::vector<MessageBox>::iterator it = lines.begin(); it != lines.end();
        ++it )
    {
        boost::shared_ptr<CenterLayout> currentLayout(new CenterLayout(
            fitStrategy));
        boost::shared_ptr<Layout> superCenterLayout(currentLayout);
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
    Point position = { 0.0, 0.0 }; 
    Dimension lineSize;
    lineSize.width = size.width;
    lineSize.height = //Figure out font height?
    
    while( notFull == true && !(text.empty()) )
    {
        MessageBoxLine currentLine(;
        notFull = currentLine.form(font, text, text);
        lines.push_back(currentLine);
    }

    return !notFull;
}

void MessageBox::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
}

void MessageBox::loadImage(Renderer &renderer)
{
    //No-op, direct graphic strategy created and used during draw
}

