//File: TitleMenu.cpp
//Author:   John Miner
//Created:  08/30/12
//Purpose:  Title screen menu that allows player to select Play, Play 2P, 
//          Story, Options, or Credits
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/


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
#include "../Header/FontSize.hpp"
#include "../Header/StandardUnit.hpp"

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
    static const Uint32 TMP_PRESSED_TIME_THRESHOLD = StandardUnit::DURATION()
        * 15;
    return TMP_PRESSED_TIME_THRESHOLD;
}

TitleMenu::TitleMenu(boost::shared_ptr<boost::shared_ptr<Scene> > &currentScene,
    boost::shared_ptr<Scene> &mainGameScene, boost::shared_ptr<Scene> 
    &creditGameScene, boost::shared_ptr<Scene> &storyScene) : menuItems(), 
    textRendererElements(), menuGrid(),
    layouts(), cycle(STOP()), pressedTime(0)
{
    createMenuItems(currentScene, mainGameScene, creditGameScene, storyScene);
    createLayouts();
    reset();
}

TitleMenu::TitleMenu(const TitleMenu &rhs) : menuItems(rhs.menuItems),
    currentMenuItem(rhs.currentMenuItem), 
    textRendererElements(rhs.textRendererElements), menuGrid(rhs.menuGrid),
    layouts(rhs.layouts), cycle(rhs.cycle), pressedTime(rhs.pressedTime)
{ }

TitleMenu &TitleMenu::operator=(const TitleMenu &rhs)
{
    if( &rhs == this )
        return *this;

    menuItems = rhs.menuItems;
    currentMenuItem = rhs.currentMenuItem;
    textRendererElements = rhs.textRendererElements;
    menuGrid = rhs.menuGrid;
    layouts = rhs.layouts;
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
    std::list<boost::shared_ptr<TextRendererElement> > textRendererElementsCopy =
        textRendererElements;
    std::list<boost::shared_ptr<TextRendererElement> >::iterator it2 = 
        textRendererElementsCopy.begin();

    std::list<boost::shared_ptr<CenterLayout> > layoutsCopy = layouts;
    for( std::list<boost::shared_ptr<CenterLayout> >::iterator it = 
        layoutsCopy.begin(); it != layoutsCopy.end() && it2 != 
        textRendererElementsCopy.end(); ++it, ++it2)
        (*it)->drawWhenReady(**it2);
}

void TitleMenu::loadImage(Renderer &renderer)
{
    const Point POSITION(0.0, 0.0);
    const Dimension SIZE(StandardUnit::DIMENSION() * 30.0, StandardUnit::
        DIMENSION() * 10.0);
    const SDL_Color COLOR = { 0xc2, 0xde, 0xa7, 0x00 };
    const int BORDER_SIZE = 0;
    std::string menuText; 

    for( std::list<boost::shared_ptr<MenuItem> >::iterator it =
        menuItems.begin(); it != menuItems.end(); ++it )
    {
        renderer.loadText((*it)->toString(), COLOR, BORDER_SIZE, FontSize::Huge()); 
        boost::shared_ptr<TextRendererElement> tmp(new TextRendererElement(
            (*it)->toString(), Layer::TITLE_MENU().integer(), POSITION, SIZE,
            FontSize::Huge()));
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
    &currentScene, boost::shared_ptr<Scene> &mainGameScene, boost::shared_ptr<Scene>
    &creditGameScene, boost::shared_ptr<Scene> &storyScene)
{
    boost::shared_ptr<MenuItem> play(new SceneMenuItem(currentScene,
        mainGameScene, "2 Play"));
    boost::shared_ptr<MenuItem> credits(new SceneMenuItem(currentScene,
        creditGameScene, "Credits"));
    boost::shared_ptr<MenuItem> story(new SceneMenuItem(currentScene,
        storyScene, "Story"));
    menuItems.push_back(play);
    menuItems.push_back(credits);
    menuItems.push_back(story);
    menuItems.push_back(play);
}

void TitleMenu::keyPressed(const SDL_Keycode &key)
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

void TitleMenu::keyReleased(const SDL_Keycode &key)
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
    Point cell(0.0, 0.0);
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

