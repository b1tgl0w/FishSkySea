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
#include "../Header/GridLayout.hpp"
#include "../Header/CenterLayout.hpp"
#include "../Header/FillClipFit.hpp"
#include "../Header/SceneMenuItem.hpp"
#include "../Header/Scene.hpp"

TitleMenu::TitleMenu(boost::shared_ptr<Scene> &mainGameScene)
{
    createMenuItems(mainGameScene);
    createLayouts();
}

TitleMenu::TitleMenu(const TitleMenu &rhs) : menuItems(rhs.menuItems),
    currentMenuItem(rhs.currentMenuItem), 
    textRendererElements(rhs.textRendererElements), menuGrid(rhs.menuGrid)
{
}

TitleMenu &TitleMenu::operator=(const TitleMenu &rhs)
{
    if( &rhs == this )
        return *this;

    menuItems = rhs.menuItems;
    currentMenuItem = rhs.currentMenuItem;
    textRendererElements = rhs.textRendererElements;
    menuGrid = rhs.menuGrid;

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
    std::list<boost::shared_ptr<RendererElement> >::iterator it2 = 
        textRendererElements.begin();

    for( std::list<boost::shared_ptr<CenterLayout> >::iterator it = 
        layouts.begin(); it != layouts.end() && it2 != 
        textRendererElements.end(); ++it, ++it2)
        (*it)->drawWhenReady(**it2);
}

void TitleMenu::loadImage(Renderer &renderer)
{
    const Point POSITION = { 0.0, 0.0 };
    const Dimension SIZE = { 150.0, 50.0 };
    const SDL_Color COLOR = { 0x17, 0x00, 0x24, 0x00 };
    const int BORDER_SIZE = 0;
    std::string menuText; 

    for( std::list<boost::shared_ptr<MenuItem> >::iterator it =
        menuItems.begin(); it != menuItems.end(); ++it )
    {
        renderer.loadText((*it)->toString(), COLOR, BORDER_SIZE); 
        boost::shared_ptr<RendererElement> tmp(new TextRendererElement(
            (*it)->toString(), Layer::TITLE_MENU().integer(), POSITION, SIZE));
        textRendererElements.push_back(tmp);
    }
}

//This is a getter.
//Would be better for Layout to have ::addLayout or to have a Cell::addLayout
// in the iface and avoid a getter
boost::shared_ptr<Layout> TitleMenu::layoutToAttach()
{
    boost::shared_ptr<Layout> tmp(menuGrid);
    return tmp;
}

void TitleMenu::createMenuItems(boost::shared_ptr<Scene> &mainGameScene)
{
    boost::shared_ptr<MenuItem> play(new SceneMenuItem(mainGameScene, "Play"));
    menuItems.push_back(play);
}

//Shall be called after menuItems is filled
void TitleMenu::createLayouts()
{
    boost::shared_ptr<FillClipFit> fillClipFit(new FillClipFit);
    Point cell = { 0.0, 0.0 };
    boost::shared_ptr<GridLayout> tmp(new GridLayout(1, menuItems.size()));
    menuGrid = tmp;
    
    for( cell.y = 0; cell.y < menuItems.size(); ++(cell.y) )
    {
        boost::shared_ptr<Layout> centerLayout(new CenterLayout(
            fillClipFit));
        menuGrid->addLayout(centerLayout, cell);
    }
}

