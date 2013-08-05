//File: TitleMenu.hpp
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

#ifndef TITLE_MENU_HPP_
#define TITLE_MENU_HPP_

#include <SDL/SDL.h>
#include <list>
#include "boost/shared_ptr.hpp"
#include "Menu.hpp"
#include "Graphic.hpp"
#include "KeyboardSubscriber.hpp"
#include "MasterClockSubscriber.hpp"

class Layout;
class GridLayout;
class CenterLayout;
class Renderer;
class MenuItem;
class RendererElement;
class Scene;
class TextRendererElement;

class TitleMenu : public Menu, public Graphic, public KeyboardSubscriber,
    public MasterClockSubscriber
{
public:
    TitleMenu(boost::shared_ptr<boost::shared_ptr<Scene> > &currentScene,
    boost::shared_ptr<Scene> &mainGameScene, boost::shared_ptr<Scene> &
    creditGameScene);
    TitleMenu(const TitleMenu &rhs);
    TitleMenu &operator=(const TitleMenu &rhs);
    void next();
    void previous();
    void select();
    void reset();
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
    boost::shared_ptr<Layout> layoutToAttach();
    void keyPressed(const SDLKey &key);
    void keyReleased(const SDLKey &key);
    void clockTick(Uint32 elapsedTime);
private:
    TitleMenu();
    void createMenuItems(boost::shared_ptr<boost::shared_ptr<Scene> > 
        &currentScene, boost::shared_ptr<Scene> &mainGameScene,
        boost::shared_ptr<Scene> &creditGameScene);
    void createLayouts();
    void highlightCurrentMenuItem(bool highlight);
    static const int &STOP();
    static const int &NEXT();
    static const int &PREVIOUS();
    static const Uint32 &PRESSED_TIME_THRESHOLD();
    std::list<boost::shared_ptr<MenuItem> > menuItems;
    std::list<boost::shared_ptr<MenuItem> >::iterator currentMenuItem;
    std::list<boost::shared_ptr<TextRendererElement> > textRendererElements;
    boost::shared_ptr<GridLayout> menuGrid;
    std::list<boost::shared_ptr<CenterLayout> > layouts;
    int cycle;
    Uint32 pressedTime;
};

#endif

