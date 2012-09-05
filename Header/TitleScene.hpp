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
};

#endif

