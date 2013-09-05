//File: CreditGameScene.cpp
//Author:   John Miner
//Created:  07/15/13
//Purpose:  Coordinate the credit minigame, load media, and connect objects.
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

#include "boost/signals2.hpp"
#include "boost/bind.hpp"
#include "../Header/CreditGameScene.hpp"
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
#include "../Header/ScaleClipFit.hpp"
#include "../Header/Layer.hpp"
#include "../Header/TextRendererElement.hpp"
#include "../Header/Timer.hpp"
#include "../Header/OceanMode.hpp"
#include "../Header/Biography.hpp"
#include "../Header/BorderCorner.hpp"

const Point &CreditGameScene::POLE_POINT()
{
    static const Point TMP_POLE_POINT(130.0, 205.0);
    return TMP_POLE_POINT;
}

const Point &CreditGameScene::HOOK_POINT()
{
    static const Point TMP_HOOK_POINT(130.0, 550.0);
    return TMP_HOOK_POINT;
}

const Point &CreditGameScene::BACKGROUND_POINT()
{
    static const Point TMP_BACKGROUND_POINT(0.0, 0.0);
    return TMP_BACKGROUND_POINT;
}

const Point &CreditGameScene::MOWHAWK_FISHER_POINT()
{
    static const Point TMP_MOWHAWK_FISHER_POINT(90.0, 120.0);
    return TMP_MOWHAWK_FISHER_POINT;
}

const Point &CreditGameScene::DOCK_SUPPORTS_POINT()
{
    static const Point TMP_DOCK_SUPPORTS_POINT(0.0, 0.0);
    return TMP_DOCK_SUPPORTS_POINT;
}

const Dimension &CreditGameScene::MOWHAWK_FISHER_SIZE()
{
    static const Dimension TMP_MOWHAWK_FISHER_SIZE(50.0, 161.0);
    return TMP_MOWHAWK_FISHER_SIZE;
}

const std::string &CreditGameScene::BACKGROUND_PATH()
{
    static std::string TMP_BACKGROUND_PATH = "../Media/Scene8.png";
    return TMP_BACKGROUND_PATH;
}

const std::string &CreditGameScene::MOWHAWK_FISHER_PATH()
{
    static const std::string TMP_MOWHAWK_FISHER_PATH = 
        "../Media/MowhawkFisher2.png";
    return TMP_MOWHAWK_FISHER_PATH;
}

const std::string &CreditGameScene::DOCK_SUPPORTS_PATH()
{
    static const std::string TMP_DOCK_SUPPORTS_PATH = 
        "../Media/DockSupports3.png";
    return TMP_DOCK_SUPPORTS_PATH;
}

CreditGameScene::CreditGameScene(boost::shared_ptr<boost::shared_ptr<Scene> >
    &currentScene,
    boost::shared_ptr<Renderer> &renderer, 
    boost::shared_ptr<KeyboardPublisher> &keyboardPublisher,
    const Dimension &screenResolution) : 
    renderer(renderer), keyboardPublisher(keyboardPublisher),
    screenResolution(screenResolution), 
    masterInputPublisher(MasterInputPublisher::getInstance()),
    masterClockPublisher(MasterClockPublisher::getInstance()),
    ocean(new Ocean(screenResolution, renderer)), score1(new Score(0)),
    player1(new HumanPlayer(POLE_POINT(), HOOK_POINT(), ocean, score1,
        HumanPlayer::PLAYER_ONE(), !HumanPlayer::MAIN_GAME())), 
    background(BACKGROUND_PATH(), Layer::BACKGROUND1().integer(), 
        BACKGROUND_POINT(), screenResolution), 
    dockSupports(DOCK_SUPPORTS_PATH(), Layer::DOCK_SUPPORTS().integer(),
        DOCK_SUPPORTS_POINT(), screenResolution),
    mowhawkFisher(MOWHAWK_FISHER_PATH(), Layer::FOREGROUND().integer(), 
        MOWHAWK_FISHER_POINT(), MOWHAWK_FISHER_SIZE()), 
        scaleClipFit(new ScaleClipFit), 
    quit(false), oceanLayout(new CoordinateLayout(scaleClipFit)), 
    statusLayout(new 
    CenterLayout(scaleClipFit)), superOceanLayout(oceanLayout),
    superStatusLayout(statusLayout),
    clockSubscriber(masterClockPublisher,
    MasterClockPublisher::customDeleter), MiSubscriber(keyboardPublisher),
    playerSubscriber(player1), 
    layeredLayout(new LayeredLayout(3, scaleClipFit)), borderLayout(new BorderLayout(
    BorderSize::Thick())), superBorderLayout(borderLayout), gridLayout(new
    GridLayout(1, 3)), superGridLayout(gridLayout), superLayeredLayout(
    layeredLayout), currentScene(currentScene), transition(false),
    toScene(), statusElement(), readyTimer(), goTimer(),
    titleScene(), biographies(), bioGridLayout(new GridLayout(3, 4)), 
    superBioGridLayout(bioGridLayout), bioBorderLayout(new BorderLayout(
    BorderSize::Thick())), superBioBorderLayout(bioBorderLayout),
    nameCoordinateLayout(new CoordinateLayout(scaleClipFit)),
    superNameCoordinateLayout(nameCoordinateLayout), pictureCenterLayout(
    new CenterLayout(scaleClipFit)), superPictureCenterLayout(pictureCenterLayout),
    titleCoordinateLayout(new CoordinateLayout(scaleClipFit)), superTitleCoordinateLayout(
    titleCoordinateLayout), bioCoordinateLayout(new CoordinateLayout(scaleClipFit)),
    superBioCoordinateLayout(bioCoordinateLayout),
    johnBio(new Biography("../Media/JohnBioPicture.png", "Testing biography text. This guy likes to CODE!", 
        "John Miner", "Designer Coder Writer", renderer)),
    connections()
{
    ocean->initializeStates();
    ocean->initializeSharedFromThis();
    player1->initializeLine();
    player1->initializePlayerKeyTranslater();
    bioBorderLayout->useCorners(BorderCorner::TopBottomCenter());
}

CreditGameScene::CreditGameScene(const CreditGameScene &rhs) : renderer(rhs.renderer),
    keyboardPublisher(rhs.keyboardPublisher), screenResolution(
    rhs.screenResolution), masterInputPublisher(
    rhs.masterInputPublisher), masterClockPublisher(rhs.masterClockPublisher),
    ocean(rhs.ocean), score1(rhs.score1), player1(rhs.player1), background(
    rhs.background), dockSupports(rhs.dockSupports), 
    mowhawkFisher(rhs.mowhawkFisher), scaleClipFit(rhs.scaleClipFit), quit(rhs.quit), 
    oceanLayout(rhs.oceanLayout), 
    statusLayout(rhs.statusLayout), 
    superOceanLayout(rhs.superOceanLayout), 
    superStatusLayout(rhs.superStatusLayout), clockSubscriber(
    rhs.clockSubscriber), MiSubscriber(rhs.MiSubscriber), playerSubscriber(
    rhs.playerSubscriber), layeredLayout(
    rhs.layeredLayout), borderLayout(rhs.borderLayout), superBorderLayout(
    rhs.superBorderLayout), gridLayout(rhs.gridLayout), superGridLayout(
    rhs.superGridLayout), superLayeredLayout(rhs.superLayeredLayout),
    currentScene(rhs.currentScene), transition(rhs.transition),
    toScene(rhs.toScene), statusElement(rhs.statusElement),
    readyTimer(rhs.readyTimer), goTimer(rhs.goTimer), 
    titleScene(rhs.titleScene), biographies(rhs.biographies),
    bioGridLayout(rhs.bioGridLayout), superBioGridLayout(rhs.superBioGridLayout),
    bioBorderLayout(rhs.bioBorderLayout), superBioBorderLayout(rhs.superBioBorderLayout),
    nameCoordinateLayout(rhs.nameCoordinateLayout), superNameCoordinateLayout(
    rhs.superNameCoordinateLayout), pictureCenterLayout(rhs.
    pictureCenterLayout), superPictureCenterLayout(rhs.
    superPictureCenterLayout), titleCoordinateLayout(rhs.titleCoordinateLayout),
    superTitleCoordinateLayout(rhs.superTitleCoordinateLayout),
    bioCoordinateLayout(rhs.bioCoordinateLayout), superBioCoordinateLayout(
    rhs.superBioCoordinateLayout), johnBio(rhs.johnBio),
    connections(rhs.connections)
{ }

CreditGameScene &CreditGameScene::operator=(const CreditGameScene &rhs)
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
    mowhawkFisher = rhs.mowhawkFisher;
    scaleClipFit = rhs.scaleClipFit;
    quit = rhs.quit;
    oceanLayout = rhs.oceanLayout;
    statusLayout = rhs.statusLayout;
    superOceanLayout = rhs.superOceanLayout;
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
    titleScene = rhs.titleScene;
    biographies = rhs.biographies;
    bioGridLayout = rhs.bioGridLayout;
    superBioGridLayout = rhs.superBioGridLayout;
    bioBorderLayout = rhs.bioBorderLayout;
    superBioBorderLayout = rhs.superBioBorderLayout;
    nameCoordinateLayout = rhs.nameCoordinateLayout;
    superNameCoordinateLayout = rhs.superNameCoordinateLayout;
    pictureCenterLayout = rhs.pictureCenterLayout;
    superPictureCenterLayout = rhs.superPictureCenterLayout;
    titleCoordinateLayout = rhs.titleCoordinateLayout;
    superTitleCoordinateLayout = rhs.superTitleCoordinateLayout;
    bioCoordinateLayout = rhs.bioCoordinateLayout;
    superBioCoordinateLayout = rhs.superBioCoordinateLayout;
    johnBio = rhs.johnBio;
    connections = rhs.connections;

    return *this;
}

CreditGameScene::~CreditGameScene()
{
}

//NOTE: BEWARE OF SUBSCRIBING TWICE! SCENE MUST BE IN A VALID STATE TO BE
//      ENTERED(...) INTO AGAIN!
void CreditGameScene::enter()
{
    Point cell(0, 0);
    const SDL_Color COLOR = { 0x17, 0x00, 0x24, 0x00 };
    const int BORDER_SIZE = 0;

    Layer::randomize();
    transition = false;
    ocean->changeState(OceanMode::CREDIT_MODE());
    ocean->loadImage(*(renderer));
    ocean->addCollidable(ocean);
    boost::weak_ptr<Collidable> playerCollidable(player1);
    ocean->addCollidable(playerCollidable);
    player1->loadImage(*renderer);
    renderer->loadImage("../Media/Scene8.png");
    renderer->loadImage("../Media/MowhawkFisher2.png");
    renderer->loadImage("../Media/DockSupports3.png");
    renderer->loadText("Ready", COLOR, BORDER_SIZE, FontSize::Big());
    renderer->loadText("Go", COLOR, BORDER_SIZE, FontSize::Huge());
    player1->sendCollidable(ocean);
    keyboardPublisher->subscribe(clockSubscriber);
    masterInputPublisher->subscribe(MiSubscriber);
    keyboardPublisher->subscribe(playerSubscriber);

    //start bios

    johnBio->loadImage(*renderer);

    biographies.push_back(johnBio);
    
    boost::shared_ptr<Layout> tmpNameLayout(johnBio->layoutToAttachName());
    boost::shared_ptr<Layout> tmpTitleLayout(johnBio->layoutToAttachTitle());
    boost::shared_ptr<Layout> tmpBioLayout(johnBio->layoutToAttachBio());
    Point origin(0.0, 0.0);
    nameCoordinateLayout->addLayout(tmpNameLayout, origin);
    titleCoordinateLayout->addLayout(tmpTitleLayout, origin);
    bioCoordinateLayout->addLayout(tmpBioLayout, origin);

    bioBorderLayout->addLayout(superNameCoordinateLayout, BorderCell::Top());
    bioBorderLayout->addLayout(superPictureCenterLayout, BorderCell::Center());
    bioBorderLayout->addLayout(superTitleCoordinateLayout, BorderCell::Bottom());
    cell.x = 2;
    cell.y = 0;
    bioGridLayout->addLayout(superBioCoordinateLayout, cell);
    cell.x = 1;
    bioGridLayout->addLayout(superBioBorderLayout, cell);
    connections.push_back(ocean->subscribeToCreditFish("John Miner", 
        boost::bind(&CreditGameScene::showBio, this, _1)));

    //end bios

    std::vector<boost::shared_ptr<Layout> > creditFishLayouts = 
        ocean->layoutsToAttach();
    Point tmpOrigin(0.0, 0.0);
    std::vector<boost::shared_ptr<Layout> > creditFishLayoutsCopy = 
        creditFishLayouts;
    for( std::vector<boost::shared_ptr<Layout> >::iterator it = 
        creditFishLayoutsCopy.begin(); it != creditFishLayoutsCopy.end(); ++it )
        oceanLayout->addLayout(*it, tmpOrigin);

    layeredLayout->addLayout(superOceanLayout, 0);
    layeredLayout->addLayout(superBorderLayout, 1);
    layeredLayout->addLayout(superBioGridLayout, 2);
    borderLayout->addLayout(superGridLayout, BorderCell::Top());
    cell.x = 1;
    gridLayout->addLayout(superStatusLayout, cell);
    renderer->addLayout(superLayeredLayout);
    displayReady();
    boost::shared_ptr<KeyboardSubscriber> sharedThisSubscriber(
        shared_from_this());
    keyboardPublisher->subscribe(sharedThisSubscriber);
}

void CreditGameScene::run()
{
    masterInputPublisher->pollInput();
    masterClockPublisher->pollClock();
    player1->draw(superOceanLayout, *renderer);
    ocean->draw(superOceanLayout, *renderer);
    oceanLayout->drawWhenReady(background);
    oceanLayout->drawWhenReady(mowhawkFisher);
    oceanLayout->drawWhenReady(dockSupports);
    boost::shared_ptr<Layout> superStatusLayout(statusLayout);

    std::vector<boost::shared_ptr<Biography> > biographiesCopy = biographies;
    for( std::vector<boost::shared_ptr<Biography> >::iterator it = biographiesCopy.
        begin(); it != biographiesCopy.end(); ++it )
        (*it)->draw(superPictureCenterLayout, *renderer);

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
void CreditGameScene::exit()
{
    Point cell(0, 0);
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
    cell.x = 1;
    gridLayout->removeLayout(superStatusLayout, cell);
    renderer->removeLayout(superLayeredLayout);
    ocean->gameLive(false);
    boost::shared_ptr<KeyboardSubscriber> sharedThisSubscriber(
        shared_from_this());
    keyboardPublisher->unsubscribe(sharedThisSubscriber);
    
    std::vector<boost::shared_ptr<boost::signals2::connection> > connectionsCopy = connections;
    for( std::vector<boost::shared_ptr<boost::signals2::connection> >::iterator it = 
        connectionsCopy.begin(); it != connectionsCopy.end(); ++it )
    {
        if( *it )
            (*it)->disconnect();
    }
}

void CreditGameScene::transitionTo(boost::shared_ptr<Scene> &scene)
{
    transition = true;
    toScene = scene;
}

void CreditGameScene::displayReady()
{
    Point origin(0.0, 0.0);
    Dimension textSize(150.0, 50.0);
    boost::shared_ptr<TextRendererElement> readyElement(new TextRendererElement(
        "Ready", 0, origin, textSize, FontSize::Big()));
    statusElement = readyElement;
    boost::shared_ptr<Timer<CreditGameScene> > tmpTimer(new Timer<CreditGameScene>
        (3000));
    readyTimer = tmpTimer;
    boost::function<void (CreditGameScene *)> f = &CreditGameScene::displayGo;
    boost::weak_ptr<CreditGameScene> sharedThis(shared_from_this());
    std::pair<boost::function<void (CreditGameScene *)>, boost::weak_ptr<
        CreditGameScene> > action(f, sharedThis);
    readyTimer->addAction(action);
    boost::shared_ptr<MasterClockSubscriber> timerSubscriber(readyTimer);
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    masterClockPublisher->subscribe(timerSubscriber);
}

void CreditGameScene::displayGo()
{
    ocean->gameLive(true);
    player1->gameLive(true);
    Point origin(0.0, 0.0);
    Dimension textSize(150.0, 50.0);
    boost::shared_ptr<TextRendererElement> goElement(new TextRendererElement(
        "Go", 0, origin, textSize, FontSize::Huge()));
    statusElement = goElement;
    boost::shared_ptr<Timer<CreditGameScene> > tmpTimer(new Timer<CreditGameScene>
        (3000));
    goTimer = tmpTimer;
    boost::function<void (CreditGameScene *)> f = 
        &CreditGameScene::displayGoComplete;
    boost::weak_ptr<CreditGameScene> sharedThis(shared_from_this());
    std::pair<boost::function<void (CreditGameScene *)>, boost::weak_ptr<
        CreditGameScene> > action(f, sharedThis);
    goTimer->addAction(action);
    boost::shared_ptr<MasterClockSubscriber> timerSubscriber(goTimer);
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    masterClockPublisher->subscribe(timerSubscriber);
}

void CreditGameScene::displayGoComplete()
{
    statusElement.reset();
}

bool CreditGameScene::shouldExit()
{
    return quit;
}

void CreditGameScene::keyPressed(const SDL_Keycode &key)
{
}

void CreditGameScene::keyReleased(const SDL_Keycode &key)
{
    if( key == SDLK_ESCAPE )
    {
        boost::shared_ptr<Scene> sharedTitleScene = titleScene.lock();

        if( sharedTitleScene )
            transitionTo(sharedTitleScene);
    }
}

void CreditGameScene::registerParentScene(boost::weak_ptr<Scene> parentScene)
{
    titleScene = parentScene;
}

void CreditGameScene::showBio(const std::string &name)
{
    if( name == "John Miner" )
        johnBio->show(true);
}

