//File: MainGameScene.cpp
//Author:   John Miner
//Created:  08/27/12
//Purpose:  Coordinate the main game, load media, and connect objects.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include "../Header/MainGameScene.hpp"
#include "../Header/Point.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/KeyboardPublisher.hpp"
#include "../Header/Game.hpp"
#include "../Header/MasterInputPublisher.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Score.hpp"
#include "../Header/HumanPlayer.hpp"
#include "../Header/FitStrategy.hpp"
#include "../Header/CoordinateLayout.hpp"
#include "../Header/CenterLayout.hpp"
#include "../Header/Layout.hpp"
#include "../Header/KeyboardSubscriber.hpp"
#include "../Header/MasterInputSubscriber.hpp"
#include "../Header/LayeredLayout.hpp"
#include "../Header/BorderLayout.hpp"
#include "../Header/GridLayout.hpp"
#include "../Header/ClipFit.hpp"
#include "../Header/Layer.hpp"

const Point &MainGameScene::POLE_POINT()
{
    static const Point TMP_POLE_POINT = { 150.0, 250.0 };
    return TMP_POLE_POINT;
}

const Point &MainGameScene::HOOK_POINT()
{
    static const Point TMP_HOOK_POINT = { 150.0, 500.0 };
    return TMP_HOOK_POINT;
}

const Point &MainGameScene::BACKGROUND_POINT()
{
    static const Point TMP_BACKGROUND_POINT = { 0.0, 0.0 };
    return TMP_BACKGROUND_POINT;
}

const std::string &MainGameScene::BACKGROUND_PATH()
{
    static std::string TMP_BACKGROUND_PATH = "../Media/Scene3.png";
    return TMP_BACKGROUND_PATH;
}

MainGameScene::MainGameScene(boost::shared_ptr<boost::shared_ptr<Scene> >
    &currentScene,
    boost::shared_ptr<Renderer> &renderer, 
    boost::shared_ptr<KeyboardPublisher> &keyboardPublisher,
    const Dimension &screenResolution, boost::shared_ptr<Game> &game) : 
    renderer(renderer), keyboardPublisher(keyboardPublisher),
    screenResolution(screenResolution), game(game),
    masterInputPublisher(MasterInputPublisher::getInstance()),
    masterClockPublisher(MasterClockPublisher::getInstance()),
    ocean(new Ocean(screenResolution)), score1(new Score(0)),
    player1(new HumanPlayer(POLE_POINT(), HOOK_POINT(), ocean, score1)), 
    background(BACKGROUND_PATH(), Layer::BACKGROUND().integer(), 
        BACKGROUND_POINT(), screenResolution), clipFit(new ClipFit), 
    quit(false), oceanLayout(new CoordinateLayout(clipFit)), 
    score1CenterLayout(new CenterLayout(clipFit)), superOceanLayout(oceanLayout),
    superScore1Layout(score1CenterLayout), clockSubscriber(masterClockPublisher,
    MasterClockPublisher::customDeleter), MiSubscriber(keyboardPublisher),
    playerSubscriber(player1), gameSubscriber(game),
    layeredLayout(new LayeredLayout(2, clipFit)), borderLayout(new BorderLayout(
    BorderSize::Thick())), superBorderLayout(borderLayout), gridLayout(new
    GridLayout(1, 3)), superGridLayout(gridLayout), superLayeredLayout(
    layeredLayout), currentScene(currentScene) 
{
    ocean->initializeSharedFromThis();
    player1->initializeLine();
    player1->initializePlayerKeyTranslater();
}

MainGameScene::MainGameScene(const MainGameScene &rhs) : renderer(rhs.renderer),
    keyboardPublisher(rhs.keyboardPublisher), screenResolution(
    rhs.screenResolution), game(rhs.game), masterInputPublisher(
    rhs.masterInputPublisher), masterClockPublisher(rhs.masterClockPublisher),
    ocean(rhs.ocean), score1(rhs.score1), player1(rhs.player1), background(
    rhs.background), quit(rhs.quit), oceanLayout(rhs.oceanLayout), 
    score1CenterLayout(rhs.score1CenterLayout), 
    superOceanLayout(rhs.superOceanLayout), 
    superScore1Layout(rhs.superScore1Layout), clockSubscriber(
    rhs.clockSubscriber), MiSubscriber(rhs.MiSubscriber), playerSubscriber(
    rhs.playerSubscriber), gameSubscriber(rhs.gameSubscriber), layeredLayout(
    rhs.layeredLayout), borderLayout(rhs.borderLayout), superBorderLayout(
    rhs.superBorderLayout), gridLayout(rhs.gridLayout), superGridLayout(
    rhs.superGridLayout), superLayeredLayout(superLayeredLayout),
    currentScene(rhs.currentScene)
{
}

MainGameScene &MainGameScene::operator=(const MainGameScene &rhs)
{
    if( &rhs == this )
        return *this;

    renderer = rhs.renderer;
    keyboardPublisher = rhs.keyboardPublisher;
    screenResolution = rhs.screenResolution;
    game = rhs.game;
    masterInputPublisher = rhs.masterInputPublisher;
    masterClockPublisher = rhs.masterClockPublisher;
    ocean = rhs.ocean;
    score1 = rhs.score1;
    player1 = rhs.player1;
    background = rhs.background;
    quit = rhs.quit;
    oceanLayout = rhs.oceanLayout;
    score1CenterLayout = rhs.score1CenterLayout,
    superOceanLayout = rhs.superOceanLayout;
    superScore1Layout = rhs.superScore1Layout;
    clockSubscriber = rhs.clockSubscriber;
    MiSubscriber = rhs.MiSubscriber;
    playerSubscriber = rhs.playerSubscriber;
    gameSubscriber = rhs.gameSubscriber;
    layeredLayout = rhs.layeredLayout;
    borderLayout = rhs.borderLayout;
    superBorderLayout = rhs.superBorderLayout;
    gridLayout = rhs.gridLayout;
    superGridLayout = rhs.superGridLayout;
    superLayeredLayout = rhs.superLayeredLayout;
    currentScene = rhs.currentScene;

    return *this;
}

//NOTE: BEWARE OF SUBSCRIBING TWICE! SCENE MUST BE IN A VALID STATE TO BE
//      ENTERED(...) INTO AGAIN!
void MainGameScene::enter()
{
    Point cell = { 0, 0 };

    transition = false;
    ocean->loadImage(*(renderer));
    ocean->addCollidable(ocean);
    player1->loadImage(*renderer);
    renderer->loadImage("../Media/Scene3.png");
    player1->sendCollidable(ocean);
    keyboardPublisher->subscribe(clockSubscriber);
    masterInputPublisher->subscribe(MiSubscriber);
    keyboardPublisher->subscribe(playerSubscriber);
    keyboardPublisher->subscribe(gameSubscriber);
    layeredLayout->addLayout(superOceanLayout, 0);
    layeredLayout->addLayout(superBorderLayout, 1);
    borderLayout->addLayout(superGridLayout, BorderCell::Top());
    gridLayout->addLayout(superScore1Layout, cell);
    renderer->addLayout(superLayeredLayout);
    ocean->gameLive(true);
    player1->gameLive(true);
}

void MainGameScene::run()
{
    masterInputPublisher->pollInput();
    masterClockPublisher->pollClock();
    player1->draw(superOceanLayout, *renderer);
    ocean->draw(superOceanLayout, *renderer);
    oceanLayout->drawWhenReady(background);
    score1->draw(superScore1Layout, *renderer);
    renderer->render();

    if( game->shouldQuit() )
        exit();

    if( transition )
    {
        exit();
        *currentScene = toScene;
        toScene->enter();
    }
}

//Note: Should we tell renderer to free images here or flag them for free if
//      unused?
//NOTE: THIS METHOD MUST PUT SCENE IN A VALID STATE THAT CAN BE ENTERED(...)
//AGAIN
void MainGameScene::exit()
{
    Point cell = { 0, 0 };
    ocean->removeCollidable(ocean);
    player1->sendCollidableRemove(ocean);
    keyboardPublisher->unsubscribe(clockSubscriber);
    masterInputPublisher->unsubscribe(MiSubscriber);
    keyboardPublisher->subscribe(playerSubscriber);
    keyboardPublisher->subscribe(gameSubscriber);
    layeredLayout->removeLayout(superOceanLayout, 0);
    layeredLayout->removeLayout(superBorderLayout, 1);
    borderLayout->removeLayout(superGridLayout, BorderCell::Top());
    gridLayout->removeLayout(superScore1Layout, cell);
    renderer->removeLayout(superLayeredLayout);
    ocean->gameLive(false);
}

void MainGameScene::transitionTo(boost::shared_ptr<Scene> &scene)
{
    transition = true;
    toScene = scene;
}

