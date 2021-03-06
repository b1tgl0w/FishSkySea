//File: MainGameScene.cpp
//Author:   John Miner
//Created:  08/27/12
//Purpose:  Coordinate the main game, load media, and connect objects.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.
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
#include "../Header/OceanMode.hpp"
#include "../Header/FontSize.hpp"
#include "../Header/MessageRouter.hpp"
#include "../Header/StandardUnit.hpp"
#include "../Header/Jukebox.hpp"
#include "../Header/AiPlayer.hpp"
#include "../Header/AiDataCruncher.hpp"

const Point &MainGameScene::POLE_POINT()
{
    static const Point TMP_POLE_POINT(130.0, 205.0);
    return TMP_POLE_POINT;
}

const Point &MainGameScene::HOOK_POINT()
{
    static const Point TMP_HOOK_POINT(130.0, 550.0);
    return TMP_HOOK_POINT;
}

const Point &MainGameScene::POLE_POINT2()
{
    static const Point TMP_POLE_POINT2(670.0, 205.0);
    return TMP_POLE_POINT2;
}

const Point &MainGameScene::HOOK_POINT2()
{
    static const Point TMP_HOOK_POINT2(670.0, 550.0);
    return TMP_HOOK_POINT2;
}

const Point &MainGameScene::BACKGROUND_POINT()
{
    static const Point TMP_BACKGROUND_POINT(0.0, 0.0);
    return TMP_BACKGROUND_POINT;
}

const Point &MainGameScene::ELDER_FISHER_POINT()
{
    static const Point TMP_ELDER_FISHER_POINT(662.0, 126.0);
    return TMP_ELDER_FISHER_POINT;
}

const Point &MainGameScene::MOWHAWK_FISHER_POINT()
{
    static const Point TMP_MOWHAWK_FISHER_POINT(90.0, 120.0);
    return TMP_MOWHAWK_FISHER_POINT;
}

const Point &MainGameScene::DOCK_SUPPORTS_POINT()
{
    static const Point TMP_DOCK_SUPPORTS_POINT(0.0, 0.0);
    return TMP_DOCK_SUPPORTS_POINT;
}

const Dimension &MainGameScene::ELDER_FISHER_SIZE()
{
    static const Dimension TMP_ELDER_FISHER_SIZE(StandardUnit::DIMENSION()
        * 6.0, StandardUnit::DIMENSION() * 20.0);
    return TMP_ELDER_FISHER_SIZE;
}

const Dimension &MainGameScene::MOWHAWK_FISHER_SIZE()
{
    static const Dimension TMP_MOWHAWK_FISHER_SIZE(StandardUnit::DIMENSION()
        * 6.0, StandardUnit::DIMENSION() * 20.0);
    return TMP_MOWHAWK_FISHER_SIZE;
}

const std::string &MainGameScene::BACKGROUND_PATH()
{
    static std::string TMP_BACKGROUND_PATH = "../Media/Scene8.png";
    return TMP_BACKGROUND_PATH;
}

const std::string &MainGameScene::MOWHAWK_FISHER_PATH()
{
    static const std::string TMP_MOWHAWK_FISHER_PATH = 
        "../Media/MowhawkFisher2.png";
    return TMP_MOWHAWK_FISHER_PATH;
}

const std::string &MainGameScene::ELDER_FISHER_PATH()
{
    static const std::string TMP_ELDER_FISHER_PATH = 
        "../Media/ElderFisher2.png";
    return TMP_ELDER_FISHER_PATH;
}

const std::string &MainGameScene::DOCK_SUPPORTS_PATH()
{
    static const std::string TMP_DOCK_SUPPORTS_PATH = 
        "../Media/DockSupports3.png";
    return TMP_DOCK_SUPPORTS_PATH;
}

MainGameScene::MainGameScene(boost::shared_ptr<boost::shared_ptr<Scene> >
    &currentScene,
    boost::shared_ptr<Renderer> &renderer, 
    boost::shared_ptr<KeyboardPublisher> &keyboardPublisher,
    const Dimension &screenResolution, boost::shared_ptr<MessageRouter>
        &messageRouter, boost::shared_ptr<AiDataCruncher> &aiDataCruncher) : 
    renderer(renderer), keyboardPublisher(keyboardPublisher),
    screenResolution(screenResolution), 
    masterInputPublisher(MasterInputPublisher::getInstance()),
    masterClockPublisher(MasterClockPublisher::getInstance()),
    messageRouter(messageRouter),
    ocean(new Ocean(screenResolution, renderer, messageRouter)),
    score1(new Score(0)), score2(new Score(0)),
    player1(new HumanPlayer(POLE_POINT(), HOOK_POINT(), ocean, score1,
        HumanPlayer::PLAYER_ONE(), HumanPlayer::MAIN_GAME(), messageRouter)), 
    aiDataCruncher(aiDataCruncher),
    player2(new AiPlayer(POLE_POINT2(), HOOK_POINT2(), ocean, score2,
        HumanPlayer::PLAYER_TWO(), messageRouter, aiDataCruncher)), 
    background(BACKGROUND_PATH(), Layer::BACKGROUND1().integer(), 
        BACKGROUND_POINT(), screenResolution), 
    dockSupports(DOCK_SUPPORTS_PATH(), Layer::DOCK_SUPPORTS().integer(),
        DOCK_SUPPORTS_POINT(), screenResolution),
    elderFisher(ELDER_FISHER_PATH(), Layer::FOREGROUND().integer(), 
        ELDER_FISHER_POINT(), ELDER_FISHER_SIZE()), 
    mowhawkFisher(MOWHAWK_FISHER_PATH(), Layer::FOREGROUND().integer(), 
        MOWHAWK_FISHER_POINT(), MOWHAWK_FISHER_SIZE()), 
    clipFit(new ClipFit), 
    quit(false), oceanLayout(new CoordinateLayout(clipFit)), 
    score1CenterLayout(new CenterLayout(clipFit)), score2CenterLayout(new CenterLayout(clipFit)),
    statusLayout(new CenterLayout(clipFit)), superOceanLayout(oceanLayout),
    superScore1Layout(score1CenterLayout), superScore2Layout(score2CenterLayout),
    superStatusLayout(statusLayout), clockSubscriber(masterClockPublisher,
    MasterClockPublisher::customDeleter), MiSubscriber(keyboardPublisher),
    playerSubscriber(player1), 
    layeredLayout(new LayeredLayout(2, clipFit)), borderLayout(new BorderLayout(
    BorderSize::Thick())), superBorderLayout(borderLayout), gridLayout(new
    GridLayout(1, 3)), superGridLayout(gridLayout), superLayeredLayout(
    layeredLayout), currentScene(currentScene), transition(false), toScene(),
    statusElement(), readyTimer(), goTimer(), game(new Game(score1, score2)),
    titleScene(), jukebox(Jukebox::getInstance()), jukeboxSubscriber(
        jukebox, Jukebox::customDeleter), aiSubscriber(player2)
{
    ocean->initializeStates();
    ocean->initializeSharedFromThis();
    player1->initializeLine();
    player1->initializePlayerKeyTranslater();
    player2->initializeLine();
}

MainGameScene::MainGameScene(const MainGameScene &rhs) : renderer(rhs.renderer),
    keyboardPublisher(rhs.keyboardPublisher), screenResolution(
    rhs.screenResolution), masterInputPublisher(
    rhs.masterInputPublisher), masterClockPublisher(rhs.masterClockPublisher),
    messageRouter(rhs.messageRouter),
    ocean(rhs.ocean), score1(rhs.score1), score2(rhs.score2),
    player1(rhs.player1), aiDataCruncher(rhs.aiDataCruncher), player2(rhs.player2),
    background(rhs.background), dockSupports(rhs.dockSupports), 
    elderFisher(rhs.elderFisher), mowhawkFisher(rhs.mowhawkFisher), clipFit(rhs.clipFit), 
    quit(rhs.quit), oceanLayout(rhs.oceanLayout), score1CenterLayout(rhs.score1CenterLayout), 
    score2CenterLayout(rhs.score2CenterLayout),
    statusLayout(rhs.statusLayout), superOceanLayout(rhs.superOceanLayout), 
    superScore1Layout(rhs.superScore1Layout), 
    superScore2Layout(rhs.superScore2Layout), 
    superStatusLayout(rhs.superStatusLayout), clockSubscriber(
    rhs.clockSubscriber), MiSubscriber(rhs.MiSubscriber), playerSubscriber(
    rhs.playerSubscriber), layeredLayout(
    rhs.layeredLayout), borderLayout(rhs.borderLayout), superBorderLayout(
    rhs.superBorderLayout), gridLayout(rhs.gridLayout), superGridLayout(
    rhs.superGridLayout), superLayeredLayout(rhs.superLayeredLayout),
    currentScene(rhs.currentScene), transition(rhs.transition),
    toScene(rhs.toScene), statusElement(rhs.statusElement), readyTimer(
    rhs.readyTimer), goTimer(rhs.goTimer), game(rhs.game), titleScene(rhs.
    titleScene), jukebox(rhs.jukebox), jukeboxSubscriber(rhs.jukeboxSubscriber),
    aiSubscriber(rhs.aiSubscriber)

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
    messageRouter = rhs.messageRouter;
    ocean = rhs.ocean;
    score1 = rhs.score1;
    score2 = rhs.score2;
    player1 = rhs.player1;
    aiDataCruncher = rhs.aiDataCruncher;
    player2 = rhs.player2;
    background = rhs.background;
    dockSupports = rhs.dockSupports;
    elderFisher = rhs.elderFisher;
    mowhawkFisher = rhs.mowhawkFisher;
    clipFit = rhs.clipFit;
    quit = rhs.quit;
    oceanLayout = rhs.oceanLayout;
    score1CenterLayout = rhs.score1CenterLayout,
    score2CenterLayout = rhs.score2CenterLayout,
    statusLayout = rhs.statusLayout;
    superOceanLayout = rhs.superOceanLayout;
    superScore1Layout = rhs.superScore1Layout;
    superScore2Layout = rhs.superScore2Layout;
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
    transition = rhs.transition;
    toScene = rhs.toScene;
    statusElement = rhs.statusElement;
    readyTimer = rhs.readyTimer;
    goTimer = rhs.goTimer;
    game = rhs.game;
    titleScene = rhs.titleScene;
    jukebox = rhs.jukebox;
    jukeboxSubscriber = rhs.jukeboxSubscriber;
    aiSubscriber = rhs.aiSubscriber;

    return *this;
}

//NOTE: BEWARE OF SUBSCRIBING TWICE! SCENE MUST BE IN A VALID STATE TO BE
//      ENTERED(...) INTO AGAIN!
void MainGameScene::enter()
{
    Point cell(0, 0);
    const SDL_Color COLOR = StandardUnit::SDL_BLACK();
    const int BORDER_SIZE = 0;

    transition = false;
    ocean->changeState(OceanMode::GAME_MODE());
    ocean->loadImage(*(renderer));
    ocean->addCollidable(ocean);
    boost::weak_ptr<Collidable> playerCollidable(player1);
    boost::weak_ptr<Collidable> playerCollidable2(player2);
    ocean->addCollidable(playerCollidable);
    ocean->addCollidable(playerCollidable2);
    player1->loadImage(*renderer);
    player2->loadImage(*renderer);
    renderer->loadImage("../Media/Scene8.png");
    renderer->loadImage("../Media/MowhawkFisher2.png");
    renderer->loadImage("../Media/ElderFisher2.png");
    renderer->loadImage("../Media/DockSupports3.png");
    renderer->loadText("Ready", COLOR, BORDER_SIZE, FontSize::Big());
    renderer->loadText("Go", COLOR, BORDER_SIZE, FontSize::Huge());
    game->loadImage(*renderer);
    player1->sendCollidable(ocean);
    player2->sendCollidable(ocean);
    keyboardPublisher->subscribe(clockSubscriber);
    masterInputPublisher->subscribe(MiSubscriber);
    keyboardPublisher->subscribe(playerSubscriber);
    layeredLayout->addLayout(superOceanLayout, 0);
    layeredLayout->addLayout(superBorderLayout, 1);
    borderLayout->addLayout(superGridLayout, BorderCell::Top());
    gridLayout->addLayout(superScore1Layout, cell);
    cell.x = 1;
    gridLayout->addLayout(superStatusLayout, cell);
    cell.x = 2;
    gridLayout->addLayout(superScore2Layout, cell);
    renderer->addLayout(superLayeredLayout);
    displayReady();
    boost::shared_ptr<KeyboardSubscriber> sharedThisSubscriber(
        shared_from_this());
    keyboardPublisher->subscribe(sharedThisSubscriber);
    boost::shared_ptr<SongScene> sharedThis(shared_from_this());
    masterClockPublisher->subscribe(jukeboxSubscriber);
    masterClockPublisher->subscribe(aiSubscriber);
    jukebox->registerSong(sharedThis, "../Music/Overcast.mp3");
    jukebox->registerSong(sharedThis, "../Music/Acid Trumpet.mp3");
    jukebox->registerSong(sharedThis, "../Music/Easy Jam.mp3");
    jukebox->changeScene(sharedThis);
    jukebox->play();
}

void MainGameScene::run()
{
    masterInputPublisher->pollInput();
    masterClockPublisher->pollClock();
    game->checkWinner();
    player1->draw(superOceanLayout, *renderer);
    player2->draw(superOceanLayout, *renderer);
    ocean->draw(superOceanLayout, *renderer);
    oceanLayout->drawWhenReady(background);
    oceanLayout->drawWhenReady(mowhawkFisher);
    oceanLayout->drawWhenReady(elderFisher);
    oceanLayout->drawWhenReady(dockSupports);
    score1->draw(superScore1Layout, *renderer);
    score2->draw(superScore2Layout, *renderer);
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
    Point cell(0.0, 0.0);
    ocean->removeCollidable(ocean);
    boost::weak_ptr<Collidable> playerCollidable(player1);
    boost::weak_ptr<Collidable> playerCollidable2(player2);
    ocean->removeCollidable(playerCollidable2);
    player1->sendCollidableRemove(ocean);
    player2->sendCollidableRemove(ocean);
    keyboardPublisher->unsubscribe(clockSubscriber);
    masterInputPublisher->unsubscribe(MiSubscriber);
    keyboardPublisher->subscribe(playerSubscriber);
    layeredLayout->removeLayout(superOceanLayout, 0);
    layeredLayout->removeLayout(superBorderLayout, 1);
    borderLayout->removeLayout(superGridLayout, BorderCell::Top());
    gridLayout->removeLayout(superScore1Layout, cell);
    cell.x = 1;
    gridLayout->removeLayout(superStatusLayout, cell);
    cell.x = 2;
    gridLayout->removeLayout(superScore2Layout, cell);
    renderer->removeLayout(superLayeredLayout);
    ocean->gameLive(false);
    boost::shared_ptr<KeyboardSubscriber> sharedThisSubscriber(
        shared_from_this());
    keyboardPublisher->unsubscribe(sharedThisSubscriber);
    masterClockPublisher->unsubscribe(jukeboxSubscriber);
    masterClockPublisher->unsubscribe(aiSubscriber);
}

void MainGameScene::transitionTo(boost::shared_ptr<Scene> &scene)
{
    transition = true;
    toScene = scene;
}

void MainGameScene::displayReady()
{
    Point origin(0.0, 0.0);
    Dimension textSize(150.0, 50.0);
    boost::shared_ptr<TextRendererElement> readyElement(new TextRendererElement(
        "Ready", 0, origin, textSize, FontSize::Big()));
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
    player2->gameLive(true);
    Point origin (0.0, 0.0);
    Dimension textSize(150.0, 50.0);
    boost::shared_ptr<TextRendererElement> goElement(new TextRendererElement(
        "Go", 0, origin, textSize, FontSize::Huge()));
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
    return false;
}

void MainGameScene::keyPressed(const SDL_Keycode &key)
{
}

void MainGameScene::keyReleased(const SDL_Keycode &key)
{
    if( key == SDLK_ESCAPE )
    {
        boost::shared_ptr<Scene> sharedTitleScene = titleScene.lock();

        if( sharedTitleScene )
            transitionTo(sharedTitleScene);
    }
}

void MainGameScene::registerParentScene(boost::weak_ptr<Scene> parentScene)
{
    titleScene = parentScene;
}

