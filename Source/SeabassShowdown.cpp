//File: SeabassShowdown.cpp
//Author:   John Miner
//Created:  03/05/12
//Modified: 03/05/12
//Purpose:  Test layout subsystem. main() here.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <cstdlib>
#include <vector>
#include <SDL/SDL.h>
#include "boost/shared_ptr.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/Layer.hpp"
#include "../Header/HumanPlayer.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Fish.hpp"
#include "../Header/Collidable.hpp"
#include "../Header/MasterInputPublisher.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"
#include "../Header/KeyboardPublisher.hpp"
#include "../Header/PlayerKeyTranslater.hpp"
#include "../Header/Game.hpp"
#include "../Header/CenterLayout.hpp"
#include "../Header/CoordinateLayout.hpp"
#include "../Header/ClipFit.hpp"
#include "../Header/FillClipFit.hpp"
#include "../Header/ScaleClipFit.hpp"
#include "../Header/SpilloverFit.hpp"
#include "../Header/LayeredLayout.hpp"
#include "../Header/GridLayout.hpp"
#include "../Header/ImageRendererElement.hpp"
#include "../Header/FrameCleanupPublisher.hpp"
#include "../Header/FrameCleanupSubscriber.hpp"
#include "../Header/BorderLayout.hpp"
#include "../Header/BorderSize.hpp"
#include "../Header/BorderCell.hpp"
#include "../Header/BorderCorner.hpp"

void handleQuit( bool &quit );



//Regular game
//Throw-away code
int main(int argc, char **argv)
{
    srand((unsigned) time(0)); //Move to class Game, Ocean, or Renderer
    boost::shared_ptr<Game> game(new Game);
    Dimension screenResolution = { 800, 600 };
    boost::shared_ptr<FrameCleanupPublisher> frameCleanupPublisher(new
        FrameCleanupPublisher);
    boost::shared_ptr<Renderer> renderer(
        new Renderer(screenResolution, 32, SDL_HWSURFACE | SDL_DOUBLEBUF,
        "../Media/Fonts/monof55.ttf", frameCleanupPublisher));
    Point polePoint = { 150.0, 250.0 };
    Point hookPoint = { 150.0, 500.0 };
    Point sharkPoint = { 290.0, 271.0 };
    Point backgroundPoint = { 0.0, 0.0 };
    boost::shared_ptr<Ocean> ocean(new Ocean(screenResolution));
    ocean->initializeSharedFromThis();
    ocean->loadImage(*(renderer));
    boost::shared_ptr<HumanPlayer> player1(new HumanPlayer(polePoint,
        hookPoint, ocean));
    player1->initializeLine(); //Shall be called once after ctor
    player1->initializePlayerKeyTranslater();
    Dimension backgroundSize = { 800.0, 600.0 };
    boost::shared_ptr<Shark> shark(new Shark(ocean, sharkPoint));
    shark->initializeStates();
    renderer->loadImage("../Media/Scene3.png");
    renderer->loadImage("../Media/Fish.png");
    player1->loadImage(*renderer);
    shark->loadImage(*renderer);
    bool quit = false;
    ocean->addCollidable(ocean);
    ocean->addCollidable(shark);
    player1->sendCollidable(ocean);

    MasterInputPublisher *masterInputPublisher =
        MasterInputPublisher::getInstance();
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> sharkSubscriber(shark);
    masterClockPublisher->subscribe(sharkSubscriber);
    boost::shared_ptr<KeyboardPublisher> keyboardPublisher(new
        KeyboardPublisher);
    boost::shared_ptr<MasterInputSubscriber> MiSubscriber(keyboardPublisher);
    masterInputPublisher->subscribe(MiSubscriber);
    boost::shared_ptr<KeyboardSubscriber> playerSubscriber(player1);
    keyboardPublisher->subscribe(playerSubscriber);
    boost::shared_ptr<KeyboardSubscriber> gameSubscriber(game);
    keyboardPublisher->subscribe(gameSubscriber);
    boost::shared_ptr<FitStrategy> clipFit(new ClipFit);
    boost::shared_ptr<Layout> regularGame(new CoordinateLayout(clipFit));
    renderer->addLayout(regularGame);

    ImageRendererElement background("../Media/Scene3.png", 0,
        backgroundPoint, screenResolution);

    for( int i = 0; quit == false; ++i)
    {
        masterInputPublisher->pollInput();
        masterClockPublisher->pollClock();
        player1->draw(regularGame, *renderer);
        ocean->draw(regularGame, *renderer);
        shark->draw(regularGame, *renderer);
        regularGame->drawWhenReady(background);
        renderer->render();

        if( game->shouldQuit() )
            quit = true;
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}

/*
//Layered layout (three layered)
//Throw-away code
int main(int argc, char **argv)
{
    srand((unsigned) time(0)); //Move to class Game, Ocean, or Renderer
    boost::shared_ptr<Game> game(new Game);
    Dimension screenResolution = { 800, 600 };
    boost::shared_ptr<FrameCleanupPublisher> frameCleanupPublisher(new
        FrameCleanupPublisher);
    boost::shared_ptr<Renderer> renderer(
        new Renderer(screenResolution, 32, SDL_HWSURFACE | SDL_DOUBLEBUF,
        "../Media/Fonts/monof55.ttf", frameCleanupPublisher));
    Point polePoint = { 150.0, 250.0 };
    Point hookPoint = { 150.0, 500.0 };
    Point backgroundPoint = { 0.0, 0.0 };
    Point sharkPoint = { 290.0, 271.0 };
    Point fishPoint = { 0.0, 0.0 };
    Point fishPoint2 = { 80.0, 0.0 };
    Dimension fishSize = { 70, 26 };
    Dimension sharkSize = { 253, 52 };
    boost::shared_ptr<Ocean> ocean(new Ocean(screenResolution));
    ocean->initializeSharedFromThis();
    ocean->loadImage(*(renderer));
    boost::shared_ptr<HumanPlayer> player1(new HumanPlayer(polePoint,
        hookPoint, ocean));
    player1->initializeLine(); //Shall be called once after ctor
    player1->initializePlayerKeyTranslater();
    Dimension backgroundSize = { 800.0, 600.0 };
    boost::shared_ptr<Shark> shark(new Shark(ocean, sharkPoint));
    shark->initializeStates();
    renderer->loadImage("../Media/Scene.png");
    renderer->loadImage("../Media/Fish.png");
    player1->loadImage(*renderer);
    shark->loadImage(*renderer);
    bool quit = false;
    ocean->addCollidable(ocean);
    ocean->addCollidable(shark);
    player1->sendCollidable(ocean);

    MasterInputPublisher *masterInputPublisher =
        MasterInputPublisher::getInstance();
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> sharkSubscriber(shark);
    masterClockPublisher->subscribe(sharkSubscriber);
    boost::shared_ptr<KeyboardPublisher> keyboardPublisher(new
        KeyboardPublisher);
    boost::shared_ptr<MasterInputSubscriber> MiSubscriber(keyboardPublisher);
    masterInputPublisher->subscribe(MiSubscriber);
    boost::shared_ptr<KeyboardSubscriber> playerSubscriber(player1);
    keyboardPublisher->subscribe(playerSubscriber);
    boost::shared_ptr<KeyboardSubscriber> gameSubscriber(game);
    keyboardPublisher->subscribe(gameSubscriber);
    boost::shared_ptr<FitStrategy> clipFitStrategy(new ClipFit);
    boost::shared_ptr<FitStrategy> fillClipFit(new ScaleClipFit);
    boost::shared_ptr<LayeredLayout> layeredLayout(new LayeredLayout(
        3, clipFitStrategy));
    boost::shared_ptr<Layout> superLayeredLayout(layeredLayout);
    renderer->addLayout(superLayeredLayout);
    boost::shared_ptr<Layout> center3(new CenterLayout(
        clipFitStrategy));
    layeredLayout->addLayout(center3, 0);
    boost::shared_ptr<Layout> center4(new CenterLayout(
        clipFitStrategy));
    layeredLayout->addLayout(center4, 1);
    boost::shared_ptr<Layout> center5(new CenterLayout(
        clipFitStrategy));
    layeredLayout->addLayout(center5, 2);
    ImageRendererElement background("../Media/Scene.png", 3, backgroundPoint,
        backgroundSize);
    ImageRendererElement sharkPlaceHolder("../Media/SharkPlaceHolder.png", 2, fishPoint,
        sharkSize);
    ImageRendererElement fish("../Media/Fish.png", 1, fishPoint,
        fishSize);

    for( int i = 0; quit == false; ++i)
    {
        handleQuit(quit);
        center3->drawWhenReady(background);
        center4->drawWhenReady(sharkPlaceHolder);
        center5->drawWhenReady(fish);
        renderer->render();
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}*/

/*
//Border Layout Test
//Throw-away code
int main(int argc, char **argv)
{
    srand((unsigned) time(0)); //Move to class Game, Ocean, or Renderer
    boost::shared_ptr<Game> game(new Game);
    Dimension screenResolution = { 800, 600 };
    boost::shared_ptr<FrameCleanupPublisher> frameCleanupPublisher(new
        FrameCleanupPublisher);
    boost::shared_ptr<Renderer> renderer(
        new Renderer(screenResolution, 32, SDL_HWSURFACE | SDL_DOUBLEBUF,
        "../Media/Fonts/monof55.ttf", frameCleanupPublisher));
    Point polePoint = { 150.0, 250.0 };
    Point hookPoint = { 150.0, 500.0 };
    Point backgroundPoint = { 0.0, 0.0 };
    Point sharkPoint = { 290.0, 271.0 };
    Point fishPoint = { 0.0, 0.0 };
    Point fishPoint2 = { 80.0, 0.0 };
    Dimension fishSize = { 70, 26 };
    Dimension sharkSize = { 253, 52 };
    boost::shared_ptr<Ocean> ocean(new Ocean(screenResolution));
    ocean->initializeSharedFromThis();
    ocean->loadImage(*(renderer));
    boost::shared_ptr<HumanPlayer> player1(new HumanPlayer(polePoint,
        hookPoint, ocean));
    player1->initializeLine(); //Shall be called once after ctor
    player1->initializePlayerKeyTranslater();
    Dimension backgroundSize = { 800.0, 600.0 };
    boost::shared_ptr<Shark> shark(new Shark(ocean, sharkPoint));
    shark->initializeStates();
    renderer->loadImage("../Media/Scene.png");
    renderer->loadImage("../Media/Fish.png");
    player1->loadImage(*renderer);
    shark->loadImage(*renderer);
    bool quit = false;
    ocean->addCollidable(ocean);
    ocean->addCollidable(shark);
    player1->sendCollidable(ocean);

    MasterInputPublisher *masterInputPublisher =
        MasterInputPublisher::getInstance();
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> sharkSubscriber(shark);
    masterClockPublisher->subscribe(sharkSubscriber);
    boost::shared_ptr<KeyboardPublisher> keyboardPublisher(new
        KeyboardPublisher);
    boost::shared_ptr<MasterInputSubscriber> MiSubscriber(keyboardPublisher);
    masterInputPublisher->subscribe(MiSubscriber);
    boost::shared_ptr<KeyboardSubscriber> playerSubscriber(player1);
    keyboardPublisher->subscribe(playerSubscriber);
    boost::shared_ptr<KeyboardSubscriber> gameSubscriber(game);
    keyboardPublisher->subscribe(gameSubscriber);
    boost::shared_ptr<FitStrategy> clipFitStrategy(new ClipFit);
    boost::shared_ptr<FitStrategy> fillClipFit(new ScaleClipFit);
    boost::shared_ptr<LayeredLayout> layeredLayout(new LayeredLayout(
        2, clipFitStrategy));
    boost::shared_ptr<Layout> superLayeredLayout(layeredLayout);
    renderer->addLayout(superLayeredLayout);
    boost::shared_ptr<Layout> center3(new CenterLayout(
        fillClipFit));
    boost::shared_ptr<BorderLayout> borderLayout(new BorderLayout(
        BorderSize::Thick()));
    boost::shared_ptr<Layout> superBorderLayout(borderLayout);
    layeredLayout->addLayout(center3, 0);
    layeredLayout->addLayout(superBorderLayout, 1);
    int gridRows = 1;
    int gridCols = 2;
    boost::shared_ptr<GridLayout> gridLayout(new GridLayout(gridRows, gridCols));
    boost::shared_ptr<Layout> grid(gridLayout);
    borderLayout->addLayout(grid, BorderCell::Top());
    Point where = { 0, 0 };
    boost::shared_ptr<Layout> center1(new CenterLayout(
        fillClipFit));
    gridLayout->addLayout(center1, where);
    where.x = 1;
    boost::shared_ptr<Layout> center2(new CenterLayout(
        fillClipFit));
    gridLayout->addLayout(center2, where);
    boost::shared_ptr<Layout> center4(new CenterLayout(
        fillClipFit));
    borderLayout->addLayout(center4, BorderCell::Left());
    boost::shared_ptr<Layout> center5(new CenterLayout(
        fillClipFit));
    borderLayout->addLayout(center5, BorderCell::Right());
    boost::shared_ptr<Layout> center6(new CenterLayout(
        fillClipFit));
    borderLayout->addLayout(center6, BorderCell::Bottom());
    boost::shared_ptr<Layout> center7(new CenterLayout(
        fillClipFit));
    borderLayout->addLayout(center7, BorderCell::Center());
    borderLayout->useCorners(BorderCorner::TopBottom());
    ImageRendererElement background("../Media/Scene.png", 3, backgroundPoint,
        backgroundSize);
    ImageRendererElement fish("../Media/SharkPlaceHolder.png", 2, fishPoint,
        sharkSize);
    ImageRendererElement fish2("../Media/Fish.png", 1, fishPoint,
        sharkSize);

    for( int i = 0; quit == false; ++i)
    {
        handleQuit(quit);
        center1->drawWhenReady(fish);
        center2->drawWhenReady(fish);
        center3->drawWhenReady(background);
        center4->drawWhenReady(fish);
        center5->drawWhenReady(fish);
        center6->drawWhenReady(fish);
        center7->drawWhenReady(fish2);
        renderer->render();
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}*/


/*
//Grid Layout Test
//Throw-away code
int main(int argc, char **argv)
{
    srand((unsigned) time(0)); //Move to class Game, Ocean, or Renderer
    boost::shared_ptr<Game> game(new Game);
    Dimension screenResolution = { 800, 600 };
    boost::shared_ptr<FrameCleanupPublisher> frameCleanupPublisher(new
        FrameCleanupPublisher);
    boost::shared_ptr<Renderer> renderer(
        new Renderer(screenResolution, 32, SDL_HWSURFACE | SDL_DOUBLEBUF,
        "../Media/Fonts/monof55.ttf", frameCleanupPublisher));
    Point polePoint = { 150.0, 250.0 };
    Point hookPoint = { 150.0, 500.0 };
    Point backgroundPoint = { 0.0, 0.0 };
    Point sharkPoint = { 290.0, 271.0 };
    Dimension fishSize = { 70, 26 };
    boost::shared_ptr<Ocean> ocean(new Ocean(screenResolution));
    ocean->initializeSharedFromThis();
    ocean->loadImage(*(renderer));
    boost::shared_ptr<HumanPlayer> player1(new HumanPlayer(polePoint,
        hookPoint, ocean));
    player1->initializeLine(); //Shall be called once after ctor
    player1->initializePlayerKeyTranslater();
    Dimension backgroundSize = { 800.0, 600.0 };
    boost::shared_ptr<Shark> shark(new Shark(ocean, sharkPoint));
    shark->initializeStates();
    renderer->loadImage("../Media/Scene.png");
    renderer->loadImage("../Media/Fish.png");
    player1->loadImage(*renderer);
    shark->loadImage(*renderer);
    bool quit = false;
    ocean->addCollidable(ocean);
    ocean->addCollidable(shark);
    player1->sendCollidable(ocean);

    MasterInputPublisher *masterInputPublisher =
        MasterInputPublisher::getInstance();
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> sharkSubscriber(shark);
    masterClockPublisher->subscribe(sharkSubscriber);
    boost::shared_ptr<KeyboardPublisher> keyboardPublisher(new
        KeyboardPublisher);
    boost::shared_ptr<MasterInputSubscriber> MiSubscriber(keyboardPublisher);
    masterInputPublisher->subscribe(MiSubscriber);
    boost::shared_ptr<KeyboardSubscriber> playerSubscriber(player1);
    keyboardPublisher->subscribe(playerSubscriber);
    boost::shared_ptr<KeyboardSubscriber> gameSubscriber(game);
    keyboardPublisher->subscribe(gameSubscriber);
    boost::shared_ptr<FitStrategy> clipFitStrategy(new ClipFit);
    boost::shared_ptr<FitStrategy> fillClipFit(new ScaleClipFit);
    int gridRows = 3;
    int gridCols = 3;
    boost::shared_ptr<GridLayout> gridLayout(new GridLayout(gridRows, gridCols));
    boost::shared_ptr<Layout> grid(gridLayout);
    renderer->addLayout(grid);
    Point where = { 0, 0 };
    boost::shared_ptr<Layout> coord1(new CoordinateLayout(
        fillClipFit));
    gridLayout->addLayout(coord1, where);
    where.x = 1;
    boost::shared_ptr<Layout> coord2(new CoordinateLayout(
        fillClipFit));
    gridLayout->addLayout(coord2, where);
    where.x = 2;
    boost::shared_ptr<Layout> coord3(new CoordinateLayout(
        fillClipFit));
    gridLayout->addLayout(coord3, where);
    where.x = 0;
    where.y = 1;
    boost::shared_ptr<Layout> coord4(new CoordinateLayout(
        fillClipFit));
    gridLayout->addLayout(coord4, where);
    where.x = 1;
    boost::shared_ptr<Layout> coord5(new CoordinateLayout(
        fillClipFit));
    gridLayout->addLayout(coord5, where);
    where.x = 2;
    boost::shared_ptr<Layout> coord6(new CoordinateLayout(
        fillClipFit));
    gridLayout->addLayout(coord6, where);
    where.x = 0;
    where.y = 2;
    boost::shared_ptr<Layout> coord7(new CoordinateLayout(
        fillClipFit));
    gridLayout->addLayout(coord7, where);
    where.x = 1;
    boost::shared_ptr<Layout> coord8(new CoordinateLayout(
        fillClipFit));
    gridLayout->addLayout(coord8, where);
    where.x = 2;
    boost::shared_ptr<Layout> coord9(new CoordinateLayout(
        fillClipFit));
    gridLayout->addLayout(coord9, where);
    Point p = { 1, 0 };
    std::list<Point> mergeCells;
    mergeCells.push_back(p);
    p.x = 2;
    mergeCells.push_back(p);
    p.y = 1;
    mergeCells.push_back(p);
    p.x = 1;
    mergeCells.push_back(p);
    gridLayout->merge(mergeCells);

    ImageRendererElement background("../Media/Scene.png", 0, backgroundPoint,
        backgroundSize);
    for( int i = 0; quit == false; ++i)
    {
        masterInputPublisher->pollInput();
        masterClockPublisher->pollClock();
        player1->draw(coord1, *renderer);
        ocean->draw(coord1, *renderer);
        shark->draw(coord1, *renderer);
        coord1->drawWhenReady(background);
        player1->draw(coord2, *renderer);
        ocean->draw(coord2, *renderer);
        shark->draw(coord2, *renderer);
        coord2->drawWhenReady(background);
        player1->draw(coord3, *renderer);
        ocean->draw(coord3, *renderer);
        shark->draw(coord3, *renderer);
        coord3->drawWhenReady(background);
        player1->draw(coord4, *renderer);
        ocean->draw(coord4, *renderer);
        shark->draw(coord4, *renderer);
        coord4->drawWhenReady(background);
        player1->draw(coord5, *renderer);
        ocean->draw(coord5, *renderer);
        shark->draw(coord5, *renderer);
        coord5->drawWhenReady(background);
        player1->draw(coord6, *renderer);
        ocean->draw(coord6, *renderer);
        shark->draw(coord6, *renderer);
        coord6->drawWhenReady(background);
        player1->draw(coord7, *renderer);
        ocean->draw(coord7, *renderer);
        shark->draw(coord7, *renderer);
        coord7->drawWhenReady(background);
        player1->draw(coord8, *renderer);
        ocean->draw(coord8, *renderer);
        shark->draw(coord8, *renderer);
        coord8->drawWhenReady(background);
        player1->draw(coord9, *renderer);
        ocean->draw(coord9, *renderer);
        shark->draw(coord9, *renderer);
        coord9->drawWhenReady(background);
        renderer->render();

        if( game->shouldQuit() )
            quit = true;
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}*/

void handleQuit( bool &quit )
{
    SDL_Event event;
    while( SDL_PollEvent(&event) )
    {
        switch(event.type)
        {
        case SDL_KEYUP:
            if( event.key.keysym.sym == SDLK_ESCAPE )
                quit = true;
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
}

