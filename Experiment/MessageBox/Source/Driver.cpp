//File: Driver.cpp
//Author:   John Miner
//Created:  01/03/13
//Purpose:  Drive and test the experiment. Will not be merged with SBS
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License
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

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../../../Header/MessageBox.hpp"
#include "../../../Header/MessageBoxLine.hpp"
#include "../../../Header/FrameCleanupPublisher.hpp"
#include "../../../Header/Renderer.hpp"
#include "../../../Header/Dimension.hpp"
#include "../../../Header/Point.hpp"
#include "../../../Header/FitStrategy.hpp"
#include "../../../Header/ClipFit.hpp"
#include "../../../Header/ScaleClipFit.hpp"
#include "../../../Header/CoordinateLayout.hpp"
#include "../../../Header/Layout.hpp"
#include "../../../Header/Layer.hpp"
#include "../../../Header/FontSize.hpp"

int main(int argc, char **argv)
{
    Dimension screenResolution(800, 600);
    boost::shared_ptr<FrameCleanupPublisher> frameCleanupPublisher(new
        FrameCleanupPublisher);
    boost::shared_ptr<Renderer> renderer(
        new Renderer(screenResolution, 32, SDL_HWSURFACE | SDL_DOUBLEBUF,
        "../Media/Fonts/gentium/Gentium-R.ttf", frameCleanupPublisher));

    Dimension messageBoxSize(800, 40);
    Dimension lineSize(800, 40);
    Uint32 BLACK = 0x00000000;
    Point origin(0.0, 1.0);
    Layer layer = Layer::FOREGROUND();
    MessageBox messageBox("The tears I cry are only fragments of the suffering I endure. They soak my soul. I call out to the ocean and drift away... I'm going to put some filler text in here... kinda ruins the moment, doesn't it? I neeeeed more filler. I'm not sure how much. Maybe this is enough",
        lineSize, BLACK, false, layer, renderer, FontSize::Medium(), 1);
    boost::shared_ptr<FitStrategy> clipFit(new ClipFit);
    boost::shared_ptr<FitStrategy> scaleClipFit(new ScaleClipFit);
    boost::shared_ptr<Layout> superMbLayout(messageBox.layoutToAttach());
    boost::shared_ptr<CoordinateLayout> coordLayout(new CoordinateLayout(scaleClipFit));
    Point coordPoint(0, 0);
    coordLayout->addLayout(superMbLayout, coordPoint);
    boost::shared_ptr<Layout>  superCLayout(coordLayout);
    boost::shared_ptr<GridLayout> gridLayout(new GridLayout(3, 1));
    boost::shared_ptr<Layout> superGridLayout(gridLayout);
    gridLayout->addLayout(superCLayout, origin);
    renderer->addLayout(superGridLayout);
    while( true )
    {
        for( int i = 0; i < 500; ++i )
        {
            messageBox.draw(superGridLayout, *renderer);
            renderer->render();
            SDL_Delay(1);
        }

        if( !messageBox.advance() )
            break;
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}

