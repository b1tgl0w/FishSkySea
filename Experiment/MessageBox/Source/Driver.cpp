//File: Driver.cpp
//Author:   John Miner
//Created:  01/03/13
//Purpose:  Drive and test the experiment. Will not be merged with SBS

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
    Dimension screenResolution = { 800, 600 };
    boost::shared_ptr<FrameCleanupPublisher> frameCleanupPublisher(new
        FrameCleanupPublisher);
    boost::shared_ptr<Renderer> renderer(
        new Renderer(screenResolution, 32, SDL_HWSURFACE | SDL_DOUBLEBUF,
        "../../Media/Fonts/monof55.ttf", frameCleanupPublisher));
    TTF_Font *testFont = TTF_OpenFont("../../../Media/Fonts/monof55.ttf", 88);
    Dimension messageBoxSize = { 640, 120 };
    Dimension lineSize = { 640, 60 };
    Uint32 WHITE = 0xFFFFFFFF; 
    Point origin = { 0.0, 0.0 };
    Layer layer = Layer::FOREGROUND();
    MessageBox messageBox(testFont, "Test", messageBoxSize, lineSize, WHITE, 
        false, layer);
    boost::shared_ptr<FitStrategy> clipFit(new ClipFit);
    boost::shared_ptr<CoordinateLayout> testLayout(new CoordinateLayout(clipFit));
    boost::shared_ptr<Layout> superTestLayout(testLayout);
    boost::shared_ptr<Layout> superMessageBox(messageBox.layoutToAttach());
    testLayout->addLayout(superMessageBox, origin);
    renderer->addLayout(superTestLayout);
    messageBox.draw(superTestLayout, *renderer);
    renderer->render();
    SDL_Delay(3000);

    SDL_Quit();
    return EXIT_SUCCESS;
}

