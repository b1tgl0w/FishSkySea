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
#include "../Header/TextRendererElement.hpp"
#include "../Header/Timer.hpp"

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

const Point &MainGameScene::DOCK_SUPPORTS_POINT()
{
    static const Point TMP_DOCK_SUPPORTS_POINT = { 0.0, 0.0 };
    return TMP_DOCK_SUPPORTS_POINT;
}

const std::string &MainGameScene::BACKGROUND_PATH()
{
    static std::string TMP_BACKGROUND_PATH = "../Media/Scene4.png";
    return TMP_BACKGROUND_PATH;
}

const std::string &MainGameScene::DOCK_SUPPORTS_PATH()
{
    static const std::string TMP_DOCK_SUPPORTS_PATH = 
        "../Media/DockSupports.png";
    return TMP_DOCK_SUPPORTS_PATH;
}

MainGameScene::MainGameScene(boost::shared_ptr<boost::shared_ptr<Scene> >
    &currentScene,
    boost::shared_ptr<Renderer> &renderer, 
    boost::shared_ptr<KeyboardPublisher> &keyboardPublisher,
    const Dimension &screenResolution) : 
    renderer(renderer), keyboardPublisher(keyboardPublisher),
    screenResolution(screenResolution), 
    masterInputPublisher(MasterInputPublisher::getInstance()),
    masterClockPublisher(MasterClockPublisher::getInstance()),
    ocean(new Ocean(screenResolution)), score1(new Score(0)),
    player1(new HumanPlayer(POLE_POINT(), HOOK_POINT(), ocean, score1,
        HumanPlayer::PLAYER_ONE())), 
    background(BACKGROUND_PATH(), Layer::BACKGROUND().integer(), 
        BACKGROUND_POINT(), screenResolution), 
    dockSupports(DOCK_SUPPORTS_PATH(), Layer::DOCK_SUPPORTS().integer(),
        DOCK_SUPPORTS_POINT(), screenResolution), clipFit(new ClipFit), 
    quit(false), oceanLayout(new CoordinateLayout(clipFit)), 
    score1CenterLayout(new CenterLayout(clipFit)), statusLayout(new 
    CenterLayout(clipFit)), superOceanLayout(oceanLayout),
    superScore1Layout(score1CenterLayout), superStatusLayout(statusLayout),
    clockSubscriber(masterClockPublisher,
    MasterClockPublisher::customDeleter), MiSubscriber(keyboardPublisher),
    playerSubscriber(player1), 
    layeredLayout(new LayeredLayout(2, clipFit)), borderLayout(new BorderLayout(
    BorderSize::Thick())), superBorderLayout(borderLayout), gridLayout(new
    GridLayout(1, 3)), superGridLayout(gridLayout), superLayeredLayout(
    layeredLayout), currentScene(currentScene), game(new Game(
        score1, score1))
{
    ocean->initializeStates();
    ocean->initializeSharedFromThis();
    player1->initializeLine();
    player1->initializePlayerKeyTranslater();
}

MainGameScene::MainGameScene(const MainGameScene &rhs) : renderer(rhs.renderer),
    keyboardPublisher(rhs.keyboardPublisher), screenResolution(
    rhs.screenResolution), masterInputPublisher(
    rhs.masterInputPublisher), masterClockPublisher(rhs.masterClockPublisher),
    ocean(rhs.ocean), score1(rhs.score1), player1(rhs.player1), background(
    rhs.background), dockSupports(rhs.dockSupports), quit(rhs.quit), 
    oceanLayout(rhs.oceanLayout), score1CenterLayout(rhs.score1CenterLayout), 
    statusLayout(rhs.statusLayout), superOceanLayout(rhs.superOceanLayout), 
    superScore1Layout(rhs.superScore1Layout), 
    superStatusLayout(rhs.superStatusLayout), clockSubscriber(
    rhs.clockSubscriber), MiSubscriber(rhs.MiSubscriber), playerSubscriber(
    rhs.playerSubscriber), layeredLayout(
    rhs.layeredLayout), borderLayout(rhs.borderLayout), superBorderLayout(
    rhs.superBorderLayout), gridLayout(rhs.gridLayout), superGridLayout(
    rhs.superGridLayout), superLayeredLayout(superLayeredLayout),
    currentScene(rhs.currentScene), game(rhs.game)
{
}

MainGameScene &MainGameScene::operator=(const MainGameScene &rhs)
{
    if( &rhs == this )
        return *this;

    renderer = rhs.renderer;
    keyboardPublisher = rhs.keyboardPublisher;
    screenResolution = rhs.screenResolution;
    masterInputPublisher = rhs.masterInputPublisher;
    masterClockPublisher = rhs.masterClockPublisher;
    ocean = rhs.ocean;
    score1 = rhs.score1;
    player1 = rhs.player1;
    background = rhs.background;
    dockSupports = rhs.dockSupports;
    quit = rhs.quit;
    oceanLayout = rhs.oceanLayout;
    score1CenterLayout = rhs.score1CenterLayout,
    statusLayout = rhs.statusLayout;
    superOceanLayout = rhs.superOceanLayout;
    superScore1Layout = rhs.superScore1Layout;
    superStatusLayout = rhs.superStatusLayout;
    clockSubscriber = rhs.clockSubscriber;
    MiSubscriber = rhs.MiSubscriber;
    playerSubscriber = rhs.playerSubscriber;
    layeredLayout = rhs.layeredLayout;
    borderLayout = rhs.borderLayout;
    superBorderLayout = rhs.superBorderLayout;
    gridLayout = rhs.gridLayout;
    superGridLayout = rhs.superGridLayout;
    superLayeredLayout = rhs.superLayeredLayout;
    currentScene = rhs.currentScene;
    game = rhs.game;

    return *this;
}

//NOTE: BEWARE OF SUBSCRIBING TWICE! SCENE MUST BE IN A VALID STATE TO BE
//      ENTERED(...) INTO AGAIN!
void MainGameScene::enter()
{
    Point cell = { 0, 0 };
    const SDL_Color COLOR = { 0x17, 0x00, 0x24, 0x00 };
    const int BORDER_SIZE = 0;

    transition = false;
    ocean->loadImage(*(renderer));
    ocean->addCollidable(ocean);
    boost::weak_ptr<Collidable> playerCollidable(player1);
    ocean->addCollidable(playerCollidable);
    player1->loadImage(*renderer);
    renderer->loadImage("../Media/Scene4.png");
    renderer->loadImage("../Media/DockSupports.png");
    renderer->loadText("Ready", COLOR, BORDER_SIZE);
    renderer->loadText("Go", COLOR, BORDER_SIZE);
    game->loadImage(*renderer);
    player1->sendCollidable(ocean);
    keyboardPublisher->subscribe(clockSubscriber);
    masterInputPublisher->subscribe(MiSubscriber);
    keyboardPublisher->subscribe(playerSubscriber);
    layeredLayout->addLayout(superOceanLayout, 0);
    layeredLayout->addLayout(superBorderLayout, 1);
    borderLayout->addLayout(superGridLayout, BorderCell::Top());
    gridLayout->addLayout(superScore1Layout, cell);
    cell.x = 1;
    gridLayout->addLayout(superStatusLayout, cell);
    renderer->addLayout(superLayeredLayout);
    displayReady();
    boost::shared_ptr<KeyboardSubscriber> sharedThisSubscriber(
        shared_from_this());
    keyboardPublisher->subscribe(sharedThisSubscriber);
}

void MainGameScene::run()
{
    masterInputPublisher->pollInput();
    masterClockPublisher->pollClock();
    game->checkWinner();
    player1->draw(superOceanLayout, *renderer);
    ocean->draw(superOceanLayout, *renderer);
    oceanLayout->drawWhenReady(background);
    oceanLayout->drawWhenReady(dockSupports);
    score1->draw(superScore1Layout, *renderer);
    boost::shared_ptr<Layout> superStatusLayout(statusLayout);
    game->draw(superStatusLayout, *renderer);

    if( statusElement )
        statusLayout->drawWhenReady(*statusElement);

    renderer->render();

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
    boost::weak_ptr<Collidable> playerCollidable(player1);
    ocean->removeCollidable(playerCollidable);
    player1->sendCollidableRemove(ocean);
    keyboardPublisher->unsubscribe(clockSubscriber);
    masterInputPublisher->unsubscribe(MiSubscriber);
    keyboardPublisher->subscribe(playerSubscriber);
    layeredLayout->removeLayout(superOceanLayout, 0);
    layeredLayout->removeLayout(superBorderLayout, 1);
    borderLayout->removeLayout(superGridLayout, BorderCell::Top());
    gridLayout->removeLayout(superScore1Layout, cell);
    cell.x = 1;
    gridLayout->removeLayout(superStatusLayout, cell);
    renderer->removeLayout(superLayeredLayout);
    ocean->gameLive(false);
    boost::shared_ptr<KeyboardSubscriber> sharedThisSubscriber(
        shared_from_this());
    keyboardPublisher->unsubscribe(sharedThisSubscriber);
}

void MainGameScene::transitionTo(boost::shared_ptr<Scene> &scene)
{
    transition = true;
    toScene = scene;
}

void MainGameScene::displayReady()
{
    Point origin = { 0.0, 0.0 };
    Dimension textSize = { 150.0, 50.0 };
    boost::shared_ptr<TextRendererElement> readyElement(new TextRendererElement(
        "Ready", 0, origin, textSize));
    statusElement = readyElement;
    boost::shared_ptr<Timer<MainGameScene> > tmpTimer(new Timer<MainGameScene>
        (3000));
    readyTimer = tmpTimer;
    boost::function<void (MainGameScene *)> f = &MainGameScene::displayGo;
    boost::weak_ptr<MainGameScene> sharedThis(shared_from_this());
    std::pair<boost::function<void (MainGameScene *)>, boost::weak_ptr<
        MainGameScene> > action(f, sharedThis);
    readyTimer->addAction(action);
    boost::shared_ptr<MasterClockSubscriber> timerSubscriber(readyTimer);
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    masterClockPublisher->subscribe(timerSubscriber);
}

void MainGameScene::displayGo()
{
    ocean->gameLive(true);
    player1->gameLive(true);
    Point origin = { 0.0, 0.0 };
    Dimension textSize = { 150.0, 50.0 };
    boost::shared_ptr<TextRendererElement> goElement(new TextRendererElement(
        "Go", 0, origin, textSize));
    statusElement = goElement;
    boost::shared_ptr<Timer<MainGameScene> > tmpTimer(new Timer<MainGameScene>
        (3000));
    goTimer = tmpTimer;
    boost::function<void (MainGameScene *)> f = 
        &MainGameScene::displayGoComplete;
    boost::weak_ptr<MainGameScene> sharedThis(shared_from_this());
    std::pair<boost::function<void (MainGameScene *)>, boost::weak_ptr<
        MainGameScene> > action(f, sharedThis);
    goTimer->addAction(action);
    boost::shared_ptr<MasterClockSubscriber> timerSubscriber(goTimer);
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    masterClockPublisher->subscribe(timerSubscriber);
}

void MainGameScene::displayGoComplete()
{
    statusElement.reset();
}

bool MainGameScene::shouldExit()
{
    return quit;
}

void MainGameScene::keyPressed(const SDLKey &key)
{
}

void MainGameScene::keyReleased(const SDLKey &key)
{
    if( key == SDLK_ESCAPE )
        quit = true;
}

