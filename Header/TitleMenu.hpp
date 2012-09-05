//File: TitleMenu.hpp
//Author:   John Miner
//Created:  08/30/12
//Purpose:  Title screen menu that allows player to select Play, Play 2P, 
//          Story, Options, or Credits

#ifndef TITLE_MENU_HPP_
#define TITLE_MENU_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "Menu.hpp"
#include "Graphic.hpp"

class Layout;
class GridLayout;
class CenterLayout;
class Renderer;
class MenuItem;
class RendererElement;
class Scene;

class TitleMenu : public Menu, public Graphic
{
public:
    TitleMenu(boost::shared_ptr<Scene> &mainGameScene);
    TitleMenu(const TitleMenu &rhs);
    TitleMenu &operator=(const TitleMenu &rhs);
    void next();
    void previous();
    void select();
    void reset();
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
    boost::shared_ptr<Layout> layoutToAttach();
private:
    TitleMenu();
    void createMenuItems(boost::shared_ptr<Scene> &mainGameScene);
    void createLayouts();
    std::list<boost::shared_ptr<MenuItem> > menuItems;
    std::list<boost::shared_ptr<MenuItem> >::iterator currentMenuItem;
    std::list<boost::shared_ptr<RendererElement> > textRendererElements;
    boost::shared_ptr<GridLayout> menuGrid;
    std::list<boost::shared_ptr<CenterLayout> > layouts;
};

#endif

