//File: TitleMenu.cpp
//Author:   John Miner
//Created:  08/30/12
//Purpose:  Title screen menu that allows player to select Play, Play 2P, 
//          Story, Options, or Credits

#include <iostream> //delete
#include <string>
#include "../Header/TitleMenu.hpp"
#include "../Header/Layout.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/MenuItem.hpp"
#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/Layer.hpp"
#include "../Header/TextRendererElement.hpp"
#include "../Header/GridLayout.hpp"
#include "../Header/CenterLayout.hpp"
#include "../Header/FillClipFit.hpp"
#include "../Header/ScaleClipFit.hpp"
#include "../Header/SceneMenuItem.hpp"
#include "../Header/Scene.hpp"

const int &TitleMenu::STOP()
{
    static const int TMP_STOP = 0;
    return TMP_STOP;
}

const int &TitleMenu::NEXT()
{
    static const int TMP_NEXT = 1;
    return TMP_NEXT;
}

const int &TitleMenu::PREVIOUS()
{
    static const int TMP_PREVIOUS = 2;
    return TMP_PREVIOUS;
}

const Uint32 &TitleMenu::PRESSED_TIME_THRESHOLD()
{
    static const Uint32 TMP_PRESSED_TIME_THRESHOLD = 600;
    return TMP_PRESSED_TIME_THRESHOLD;
}

TitleMenu::TitleMenu(boost::shared_ptr<boost::shared_ptr<Scene> > &currentScene,
    boost::shared_ptr<Scene> &mainGameScene) : cycle(STOP()), pressedTime(0)
{
    createMenuItems(currentScene, mainGameScene);
    createLayouts();
    reset();
}

TitleMenu::TitleMenu(const TitleMenu &rhs) : menuItems(rhs.menuItems),
    currentMenuItem(rhs.currentMenuItem), 
    textRendererElements(rhs.textRendererElements), menuGrid(rhs.menuGrid),
    cycle(rhs.cycle), pressedTime(rhs.pressedTime)
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
    cycle = rhs.cycle;
    pressedTime = rhs.pressedTime;

    return *this;
}

void TitleMenu::next()
{
    highlightCurrentMenuItem(false);

    ++currentMenuItem;

    if( currentMenuItem == menuItems.end() )
        currentMenuItem = menuItems.begin();

    highlightCurrentMenuItem(true);
}

void TitleMenu::previous()
{
    highlightCurrentMenuItem(false);

    if( currentMenuItem == menuItems.begin() )
        currentMenuItem = menuItems.end();

    --currentMenuItem;

    highlightCurrentMenuItem(true);
}

void TitleMenu::select()
{
    (*currentMenuItem)->select();
}

void TitleMenu::reset()
{
    currentMenuItem = menuItems.begin();
    highlightCurrentMenuItem(true);
}

void TitleMenu::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    std::list<boost::shared_ptr<TextRendererElement> >::iterator it2 = 
        textRendererElements.begin();

    for( std::list<boost::shared_ptr<CenterLayout> >::iterator it = 
        layouts.begin(); it != layouts.end() && it2 != 
        textRendererElements.end(); ++it, ++it2)
        (*it)->drawWhenReady(**it2);
}

void TitleMenu::loadImage(Renderer &renderer)
{
    const Point POSITION = { 0.0, 0.0 };
    const Dimension SIZE = { 230.0, 88.0 };
    const SDL_Color COLOR = { 0x17, 0x00, 0x24, 0x00 };
    const int BORDER_SIZE = 0;
    std::string menuText; 

    for( std::list<boost::shared_ptr<MenuItem> >::iterator it =
        menuItems.begin(); it != menuItems.end(); ++it )
    {
        renderer.loadText((*it)->toString(), COLOR, BORDER_SIZE); 
        boost::shared_ptr<TextRendererElement> tmp(new TextRendererElement(
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

void TitleMenu::createMenuItems(boost::shared_ptr<boost::shared_ptr<Scene> >
    &currentScene, boost::shared_ptr<Scene> &mainGameScene)
{
    boost::shared_ptr<MenuItem> play(new SceneMenuItem(currentScene,
        mainGameScene, "Play"));
    menuItems.push_back(play);
    menuItems.push_back(play);
    menuItems.push_back(play);
    menuItems.push_back(play);
}

void TitleMenu::keyPressed(const SDLKey &key)
{
    if( key == SDLK_w || key == SDLK_UP )
    {
        previous();
        cycle = PREVIOUS();
        pressedTime = 0;
    }

    if( key == SDLK_s || key == SDLK_DOWN )
    {
        next();
        cycle = NEXT();
        pressedTime = 0;
    }

    if( key == SDLK_RETURN )
        select();
}

void TitleMenu::keyReleased(const SDLKey &key)
{
    if( (key == SDLK_w || key == SDLK_UP) && cycle == PREVIOUS() )
        cycle = STOP();

    if( (key == SDLK_s || key == SDLK_DOWN) && cycle == NEXT() )
        cycle = STOP();
}

void TitleMenu::clockTick(Uint32 elapsedTime)
{
    if( cycle != STOP() )
        pressedTime += elapsedTime;

    if( pressedTime >= PRESSED_TIME_THRESHOLD() )
    {
        if( cycle == NEXT() )
            next();
        else if( cycle == PREVIOUS() )
            previous();

        pressedTime = 0; //Smaller delay here
    }
}

//Shall be called after menuItems is filled
void TitleMenu::createLayouts()
{
    boost::shared_ptr<ScaleClipFit> fillClipFit(new ScaleClipFit);
    Point cell = { 0.0, 0.0 };
    boost::shared_ptr<GridLayout> tmp(new GridLayout(menuItems.size(), 1));
    menuGrid = tmp;
    
    for( cell.y = 0; cell.y < menuItems.size(); ++(cell.y) )
    {
        boost::shared_ptr<CenterLayout> centerLayout(new CenterLayout(
            fillClipFit));
        boost::shared_ptr<Layout> superCenterLayout(centerLayout);
        menuGrid->addLayout(superCenterLayout, cell);
        layouts.push_back(centerLayout);
    }
}

void TitleMenu::highlightCurrentMenuItem(bool highlight)
{
    if( textRendererElements.empty() || menuItems.empty() )
        return;

    std::list<boost::shared_ptr<TextRendererElement> >::iterator it = 
        textRendererElements.begin();
    std::list<boost::shared_ptr<MenuItem> >::iterator it2 = menuItems.begin();

    for( ; it2 != currentMenuItem; ++it, ++it2 );

    if( highlight )
        (*it)->transform(Transformation::HighlightText());
    else
        (*it)->transform(Transformation::None());
}

