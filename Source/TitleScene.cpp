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
#include "../Header/MasterInputPublisher.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"
#include "../Header/FitStrategy.hpp"
#include "../Header/ClipFit.hpp"
#include "../Header/LayeredLayout.hpp"
#include "../Header/CenterLayout.hpp"
#include "../Header/GridLayout.hpp"
#include "../Header/BorderLayout.hpp"
#include "../Header/Layout.hpp"
#include "../Header/MasterInputSubscriber.hpp"
#include "../Header/Renderer.hpp"

const Point &TitleScene::BACKGROUND_POSITION()
{
    static const Point TMP_BACKGROUND_POSITION = { 0.0, 0.0 };
    return TMP_BACKGROUND_POSITION;
}

TitleScene::TitleScene(boost::shared_ptr<boost::shared_ptr<Scene> > 
    &currentScene, boost::shared_ptr<Scene> &mainGameScene,
    boost::shared_ptr<KeyboardPublisher> &keyboardPublisher,
    boost::shared_ptr<Renderer> &renderer, const Dimension &screenSize) : 
    currentScene(currentScene), titleMenu(new TitleMenu(currentScene, 
    mainGameScene)), keyboardPublisher(keyboardPublisher), transition(false),
    scaleClip(new ClipFit), layeredLayout(new LayeredLayout(2,
    scaleClip)), centerLayout(new CenterLayout(scaleClip)), gridLayout( new 
    GridLayout(2, 3)), borderLayout(new BorderLayout(BorderSize::Medium())),
    superLayeredLayout(layeredLayout), superCenterLayout(centerLayout), 
    superGridLayout(gridLayout), superBorderLayout(borderLayout), 
    menuLayout(titleMenu->layoutToAttach()), masterInputPublisher(
    MasterInputPublisher::getInstance()), 
    masterClockPublisher(MasterClockPublisher::getInstance()), clockSubscriber(
    masterClockPublisher, MasterClockPublisher::customDeleter), MiSubscriber(
    keyboardPublisher), renderer(renderer), titleBackground(
    "../Media/TitleBackground.png", 0, BACKGROUND_POSITION(), screenSize)
{
}

TitleScene::TitleScene(const TitleScene &rhs) : currentScene(rhs.currentScene),
    titleMenu(rhs.titleMenu), keyboardPublisher(keyboardPublisher),
    transition(rhs.transition), toScene(rhs.toScene), scaleClip(rhs.scaleClip),
    layeredLayout(rhs.layeredLayout), centerLayout(rhs.centerLayout),
    gridLayout(rhs.gridLayout), borderLayout(rhs.borderLayout),
    superLayeredLayout(rhs.layeredLayout), superCenterLayout(
    rhs.superCenterLayout), superGridLayout(rhs.superGridLayout), 
    superBorderLayout(rhs.superBorderLayout), menuLayout(rhs.menuLayout), 
    clockSubscriber(rhs.clockSubscriber), MiSubscriber(rhs.MiSubscriber), 
    renderer(rhs.renderer), titleBackground(rhs.titleBackground)
{
}

TitleScene &TitleScene::operator=(const TitleScene &rhs)
{
    if( &rhs == this )
        return *this;

    currentScene = rhs.currentScene;
    titleMenu = rhs.titleMenu;
    keyboardPublisher = rhs.keyboardPublisher;
    transition = rhs.transition;
    toScene = rhs.toScene;
    scaleClip = rhs.scaleClip;
    layeredLayout = rhs.layeredLayout;
    centerLayout = rhs.centerLayout;
    gridLayout = rhs.gridLayout;
    borderLayout = rhs.borderLayout;
    superLayeredLayout = rhs.superLayeredLayout;
    superCenterLayout = rhs.superCenterLayout;
    superGridLayout = rhs.superGridLayout;
    superBorderLayout = rhs.superBorderLayout;
    menuLayout = rhs.menuLayout;
    clockSubscriber = rhs.clockSubscriber;
    MiSubscriber = rhs.MiSubscriber;
    renderer = rhs.renderer;
    titleBackground = rhs.titleBackground;

    return *this;
}

void TitleScene::enter()
{
    
    Point cell = { 1, 1 };
    boost::shared_ptr<KeyboardSubscriber> titleMenuKeySubscriber(titleMenu);
    boost::shared_ptr<MasterClockSubscriber> titleMenuClockSubscriber(titleMenu);
    transition = false;
    keyboardPublisher->subscribe(titleMenuKeySubscriber);
    masterClockPublisher->subscribe(titleMenuClockSubscriber);
    layeredLayout->addLayout(superCenterLayout, 0);
    layeredLayout->addLayout(superGridLayout, 1);
    gridLayout->addLayout(menuLayout, cell);
    //borderLayout->addLayout(menuLayout, BorderCell::Center());
    renderer->addLayout(superLayeredLayout);
    //keyboardPublisher->subscribe(clockSubscriber);
    masterInputPublisher->subscribe(MiSubscriber);
    loadImage(*renderer);
    titleMenu->loadImage(*renderer);
}

void TitleScene::run()
{
    masterInputPublisher->pollInput();
    masterClockPublisher->pollClock();
    draw(superCenterLayout, *renderer);
    titleMenu->draw(superBorderLayout, *renderer);
    renderer->render();

    if( transition )
    {
        exit();
        *currentScene = toScene;
        toScene->enter();
    }
}

void TitleScene::exit()
{
    Point cell = { 1, 1 };
    boost::shared_ptr<KeyboardSubscriber> titleMenuSubscriber(titleMenu);
    boost::shared_ptr<MasterClockSubscriber> titleMenuClockSubscriber(titleMenu);
    keyboardPublisher->unsubscribe(titleMenuSubscriber);
    masterClockPublisher->unsubscribe(titleMenuClockSubscriber);
    layeredLayout->removeLayout(superCenterLayout, 0);
    layeredLayout->removeLayout(superGridLayout, 1);
    gridLayout->removeLayout(superBorderLayout, cell);
    borderLayout->removeLayout(menuLayout, BorderCell::Center());
    renderer->removeLayout(superLayeredLayout);
    //keyboardPublisher->unsubscribe(clockSubscriber);
    masterInputPublisher->unsubscribe(MiSubscriber);
}

void TitleScene::transitionTo(boost::shared_ptr<Scene> &scene)
{
    transition = true;
    toScene = scene;
}

void TitleScene::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    layout->drawWhenReady(titleBackground);
}

void TitleScene::loadImage(Renderer &renderer)
{
    renderer.loadImage("../Media/TitleBackground.png");
}

