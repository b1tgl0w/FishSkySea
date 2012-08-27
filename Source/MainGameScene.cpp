//File: MainGameScene.cpp
//Author:   John Miner
//Created:  08/27/12
//Purpose:  Coordinate the main game, load media, and connect objects.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include "../Header/MainGameScene.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/KeyboardPublisher.hpp"

/*
const Point 

MainGameScene::MainGameScene(boost::shared_ptr<Renderer> &renderer, 
    boost::shared_ptr<KeyboardPublisher> &keyboardPublisher) : 
    renderer(renderer), keyboardPublisher(keyboardPublisher),
    masterInputPublisher(MasterInputPublisher::getInstance()),
    masterClockPublisher(MasterClockPublisher::getInstance()),
    ocean(new Ocean(screenResolution), score(new Score(0)),
    player1(new HumanPlayer(POLE_POINT(), HOOK_POINT(), ocean, score, 
    hookPoint)), background(BACKGROUND_PATH(), BACKGROUND_POINT(), 
    screenResolution), clipFit(new ClipFit()), quit(false), 
    oceanLayout(new CoordinateLayout(clipFit), score1CenterLayout(new 
    CenterLayout(clipFit))
{
    ocean->initializeSharedFromThis();
    player1->initializeLine();
    player1->initializePlayerKeyTranslater();
    boost::shared_ptr<Layout> tmpSuperOceanLayout(oceanLayout);
    boost::shared_ptr<Layout> tmpSuperScoreLayout(score1CenterLayout);
    superOceanLayout = tmpSuperOceanLayout;
    superScoreLayout = tmpSuperScoreLayout;
}

MainGameScene::MainGameScene(const MainGameScene &rhs) : renderer(rhs.renderer),
    keyboardPublisher(rhs.keyboardPublisher), masterInputPublisher(
    rhs.masterInputPublisher), masterClockPublisher(rhs.masterClockPublisher),
    ocean(rhs.ocean), score(rhs.score), player1(rhs.player1), background(
    rhs.background), quit(rhs.quit), oceanLayout(rhs.oceanLayout), 
    score1CenterLayout(rhs.score1CenterLayout), 
    superOceanLayout(rhs.superOceanLayout), 
    superScoreLayout(rhs.superScoreLayout)
{
}

MainGameScene &MainGameScene::operator=(const MainGameScene &rhs);
{
    if( &rhs == this )
        return *this;

    renderer = rhs.renderer;
    keyboardPublisher = rhs.keyboardPublisher;
    masterInputPublisher = rhs.masterInputPublisher;
    masterClockPublisher(rhs.masterClockPublisher;
    ocean = rhs.ocean;
    score = rhs.score;
    player1 = rhs.player1;
    background = rhs.background;
    quit = rhs.quit;
    oceanLayout = rhs.oceanLayout;
    score1CenterLayout = rhs.score1CenterLayout,
    superOceanLayout = rhs.superOceanLayout;
    superScoreLayout = rhs.superScoreLayout;

    return *this;
}

//NOTE: BEWARE OF SUBSCRIBING TWICE! SCENE MUST BE IN A VALID STATE TO BE
//      ENTERED(...) INTO AGAIN!
void MainGameScene::enter()
{
    Point sharkPoint = { 290.0, 271.0 };
    Dimension backgroundSize = { 800.0, 600.0 };
    boost::shared_ptr<Shark> shark(new Shark(ocean, sharkPoint));
    shark->initializeStates();
    boost::shared_ptr<MasterClockSubscriber> sharkSubscriber(shark);
    boost::shared_ptr<KeyboardSubscriber> clockSubscriber(masterClockPublisher,
        MasterClockPublisher::customDeleter);
    boost::shared_ptr<MasterInputSubscriber> MiSubscriber(keyboardPublisher);
    boost::shared_ptr<KeyboardSubscriber> playerSubscriber(player1);
    boost::shared_ptr<KeyboardSubscriber> gameSubscriber(game);
    boost::shared_ptr<LayeredLayout> layeredLayout(new LayeredLayout(2, 
        clipFit));
    boost::shared_ptr<BorderLayout> borderLayout(new BorderLayout(
        BorderSize::Thick()));
    boost::shared_ptr<Layout> superBorderLayout(borderLayout);
    boost::shared_ptr<GridLayout> gridLayout(new GridLayout(1, 3));
    boost::shared_ptr<Layout> superGridLayout(gridLayout);
    Point cell = { 0, 0 };
    boost::shared_ptr<Layout> superLayeredLayout(layeredLayout);

    ocean->loadImage(*(renderer));
    shark->loadImage(*renderer);
    player1->loadImage(*renderer);
    renderer->loadImage("../Media/Scene3.png");
    ocean->addCollidable(ocean);
    ocean->addCollidable(shark);
    player1->sendCollidable(ocean);
    masterClockPublisher->subscribe(sharkSubscriber);
    keyboardPublisher->subscribe(clockSubscriber);
    masterInputPublisher->subscribe(MiSubscriber);
    keyboardPublisher->subscribe(playerSubscriber);
    keyboardPublisher->subscribe(gameSubscriber);
    layeredLayout->addLayout(superOceanLayout, 0);
    layeredLayout->addLayout(superBorderLayout, 1);
    borderLayout->addLayout(superGridLayout, BorderCell::Top());
    gridLayout->addLayout(superScore1Layout, cell);
    renderer->addLayout(superLayeredLayout);
}

void MainGameScene::run()
{
    masterInputPublisher->pollInput();
    masterClockPublisher->pollClock();
    player1->draw(superOceanLayout, *renderer);
    ocean->draw(superOceanLayout, *renderer);
    shark->draw(superOceanLayout, *renderer);
    oceanLayout->drawWhenReady(background);
    score->draw(superScore1Layout, *renderer);
    renderer->render();

    if( game->shouldQuit() )
        quit = true;
}

//NOTE: THIS METHOD MUST PUT SCENE IN A VALID STATE THAT CAN BE ENTERED(...)
//AGAIN
void MainGameScene::exit()
{
}
*/
