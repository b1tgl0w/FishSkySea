//File: TitleScene.cpp
//Author:   John Miner
//Created:  09/05/12
//Purpose:  Show the title menu and allow player to select menu items.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include "../Header/TitleScene.hpp"
#include "../Header/TitleMenu.hpp"
#include "../Header/KeyboardPublisher.hpp"
#include "../Header/KeyboardSubscriber.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"

TitleScene::TitleScene(boost::shared_ptr<boost::shared_ptr<Scene> > 
    &currentScene, boost::shared_ptr<Scene> &mainGameScene,
    boost::shared_ptr<KeyboardPublisher> &keyboardPublisher) : currentScene(
    currentScene), titleMenu(new TitleMenu(currentScene, mainGameScene)),
    keyboardPublisher(keyboardPublisher)
{
}

TitleScene::TitleScene(const TitleScene &rhs) : currentScene(rhs.currentScene),
    titleMenu(rhs.titleMenu), keyboardPublisher(keyboardPublisher)
{
}

TitleScene &TitleScene::operator=(const TitleScene &rhs)
{
    if( &rhs == this )
        return *this;

    currentScene = rhs.currentScene;
    titleMenu = rhs.titleMenu;
    keyboardPublisher = rhs.keyboardPublisher;

    return *this;
}

void TitleScene::enter()
{
    transition = false;
    boost::shared_ptr<KeyboardSubscriber> titleMenuKeySubscriber(titleMenu);
    boost::shared_ptr<MasterClockSubscriber> titleMenuClockSubscriber(titleMenu);
    MasterClockPublisher *masterClockPublisher = MasterClockPublisher::
        getInstance();
    
    keyboardPublisher->subscribe(titleMenuKeySubscriber);
    masterClockPublisher->subscribe(titleMenuClockSubscriber);
}

void TitleScene::run()
{
    if( transition )
    {
        exit();
        *currentScene = toScene;
        toScene->enter();
    }
}

void TitleScene::exit()
{
    boost::shared_ptr<KeyboardSubscriber> titleMenuSubscriber(titleMenu);
    boost::shared_ptr<MasterClockSubscriber> titleMenuClockSubscriber(titleMenu);
    MasterClockPublisher *masterClockPublisher = MasterClockPublisher::
        getInstance();

    keyboardPublisher->unsubscribe(titleMenuSubscriber);
    masterClockPublisher->unsubscribe(titleMenuClockSubscriber);
}

void TitleScene::transitionTo(boost::shared_ptr<Scene> &scene)
{
    transition = true;
    toScene = scene;
}


