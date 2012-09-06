//File: TitleScene.hpp
//Author:   John Miner
//Created:  09/05/12
//Purpose:  Show the title menu and allow player to select menu items.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef TITLE_SCENE_HPP_
#define TITLE_SCENE_HPP_

#include "boost/shared_ptr.hpp"
#include "Scene.hpp"

class TitleMenu;
class KeyboardPublisher;
class FitStrategy;
class LayeredLayout;
class CenterLayout;
class GridLayout;
class BorderLayout;
class Layout;
class MasterClockPublisher;
class MasterInputPublisher;
class KeyboardSubscriber;
class MasterInputSubscriber;

class TitleScene : public Scene
{
public:
    TitleScene(boost::shared_ptr<boost::shared_ptr<Scene> > &currentScene,
        boost::shared_ptr<Scene> &mainGameScene, boost::shared_ptr<
        KeyboardPublisher> &keyboardPublisher);
    TitleScene(const TitleScene &rhs);
    TitleScene &operator=(const TitleScene &rhs);
    void enter();
    void run();
    void exit();
    void transitionTo(boost::shared_ptr<Scene> &scene);
private:
    TitleScene();
    boost::shared_ptr<boost::shared_ptr<Scene> > currentScene;
    boost::shared_ptr<TitleMenu> titleMenu;
    boost::shared_ptr<KeyboardPublisher> keyboardPublisher;
    bool transition;
    boost::shared_ptr<Scene> toScene;
    boost::shared_ptr<FitStrategy> scaleClip;
    boost::shared_ptr<LayeredLayout> layeredLayout;
    boost::shared_ptr<CenterLayout> centerLayout;
    boost::shared_ptr<GridLayout> gridLayout;
    boost::shared_ptr<BorderLayout> borderLayout;
    boost::shared_ptr<Layout> superCenterLayout;
    boost::shared_ptr<Layout> superGridLayout;
    boost::shared_ptr<Layout> superBorderLayout;
    boost::shared_ptr<Layout> menuLayout;
    MasterInputPublisher *masterInputPublisher;
    MasterClockPublisher *masterClockPublisher;
    boost::shared_ptr<KeyboardSubscriber> clockSubscriber;
    boost::shared_ptr<MasterInputSubscriber> MiSubscriber;
};

#endif

