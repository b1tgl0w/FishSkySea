//File: TitleMenu.cpp
//Author:   John Miner
//Created:  08/30/12
//Purpose:  Title screen menu that allows player to select Play, Play 2P, 
//          Story, Options, or Credits

#include <string>
#include "../Header/TitleMenu.hpp"
#include "../Header/Layout.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/MenuItem.hpp"
#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/Layer.hpp"
#include "../Header/RendererElement.hpp"
#include "../Header/TextRendererElement.hpp"

TitleMenu::TitleMenu()
{
}

TitleMenu::TitleMenu(const TitleMenu &rhs) : menuItems(rhs.menuItems),
    currentMenuItem(rhs.currentMenuItem), 
    textRendererElement(rhs.textRendererElement)
{
}

TitleMenu &TitleMenu::operator=(const TitleMenu &rhs)
{
    if( &rhs == this )
        return *this;

    menuItems = rhs.menuItems;
    currentMenuItem = rhs.currentMenuItem;
    textRendererElement = rhs.textRendererElement;

    return *this;
}

void TitleMenu::next()
{
    ++currentMenuItem;

    if( currentMenuItem == menuItems.end() )
        currentMenuItem = menuItems.begin();
}

void TitleMenu::previous()
{
    if( currentMenuItem == menuItems.begin() )
        currentMenuItem = menuItems.end();

    --currentMenuItem;
}

void TitleMenu::select()
{
    (*currentMenuItem)->select();
}

void TitleMenu::reset()
{
    currentMenuItem = menuItems.begin();
}

void TitleMenu::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    layout->drawWhenReady(*textRendererElement);
}

void TitleMenu::loadImage(Renderer &renderer)
{
    const Point POSITION = { 0.0, 0.0 };
    const Dimension SIZE = { 150.0, 50.0 * menuItems.size() };
    const SDL_Color COLOR = { 0x17, 0x00, 0x24, 0x00 };
    const int BORDER_SIZE = 0;
    std::string menuText; 

    for( std::list<boost::shared_ptr<MenuItem> >::iterator it =
        menuItems.begin(); it != menuItems.end(); ++it )
        menuText += (*it)->toString() + "\n";

    renderer.loadText(menuText, COLOR, BORDER_SIZE);
    boost::shared_ptr<RendererElement> tmp(new TextRendererElement(menuText, 
        Layer::TITLE_MENU().integer(), POSITION, SIZE));
    textRendererElement = tmp;
}

