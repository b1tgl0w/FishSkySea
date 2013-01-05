//File: Driver.cpp
//Author:   John Miner
//Created:  01/03/13
//Purpose:  Drive and test the experiment. Will not be merged with SBS
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../Header/MessageBox.hpp"
#include "../Header/MessageBoxLine.hpp"
#include "../../../Header/FrameCleanupPublisher.hpp"
#include "../../../Header/Renderer.hpp"
#include "../../../Header/Dimension.hpp"
#include "../../../Header/Point.hpp"
#include "../../../Header/FitStrategy.hpp"
#include "../../../Header/ClipFit.hpp"
#include "../../../Header/CoordinateLayout.hpp"
#include "../../../Header/Layout.hpp"
#include "../../../Header/Layer.hpp"

int main(int argc, char **argv)
{
    Dimension screenResolution = { 640, 480 };
    boost::shared_ptr<FrameCleanupPublisher> frameCleanupPublisher(new
        FrameCleanupPublisher);
    boost::shared_ptr<Renderer> renderer(
        new Renderer(screenResolution, 32, SDL_HWSURFACE | SDL_DOUBLEBUF,
        "../Media/Fonts/gentium/Gentium-R.ttf", frameCleanupPublisher));
    TTF_Font *testFont = TTF_OpenFont("../Media/Fonts/gentium/Gentium-R.ttf", 88);

    if( !testFont )
        std::cout << TTF_GetError() << std::endl;

    Dimension messageBoxSize = { 640, 120 };
    Dimension lineSize = { 640, 40 };
    Uint32 BLACK = 0x00000000;
    Point origin = { 0.0, 0.0 };
    Layer layer = Layer::FOREGROUND();
    MessageBox messageBox(testFont, "The tears I cry are only fragments of the suffering I endure. They soak my soul.", 
        messageBoxSize, lineSize, BLACK, false, layer);
    boost::shared_ptr<FitStrategy> clipFit(new ClipFit);
    boost::shared_ptr<GridLayout> gridLayout(new GridLayout(4, 1));
    boost::shared_ptr<Layout> superGridLayout(gridLayout);
    boost::shared_ptr<CoordinateLayout> coordinateLayout(new CoordinateLayout(clipFit));
    boost::shared_ptr<Layout> superCoordinateLayout(coordinateLayout);
    boost::shared_ptr<Layout> superMessageBox(messageBox.layoutToAttach());
    Point gridCell = { 0, 3 };
    boost::shared_ptr<Layout> superMbLayout(messageBox.layoutToAttach());
    coordinateLayout->addLayout(superMbLayout, origin);
    gridLayout->addLayout(superCoordinateLayout, gridCell);
    renderer->addLayout(superGridLayout);
    for( int i = 0; i < 1000; ++i )
    {
        messageBox.draw(superGridLayout, *renderer);
        renderer->render();
        SDL_Delay(1);
    }

    messageBox.advance();

    for( int i = 0; i < 1000; ++i )
    {
        messageBox.draw(superGridLayout, *renderer);
        renderer->render();
        SDL_Delay(1);
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}

