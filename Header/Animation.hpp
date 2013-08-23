//File: Animation.hpp
//Author:   John Miner
//Created 06/14/13
//Purpose: Store animation as a collection of images and timings
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

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "RendererElement.hpp"
#include "Renderer.hpp"
#include "MasterClockPublisher.hpp"
#include "MasterClockSubscriber.hpp"
#include "Dimension.hpp"
#include "Point.hpp"
#include "Layer.hpp"
#include "Graphic.hpp"

class Renderer;

class Animation : public MasterClockSubscriber, public Graphic,
    public boost::enable_shared_from_this<Animation>
{
public:
    Animation(const Point &newPosition, const Dimension &newSize,
        const Layer &newLayer);
    Animation(const Animation &rhs);
    Animation &operator=(const Animation &rhs);
    void addFrame(std::pair<std::string, Uint32> frame);
    void clockTick(Uint32 elapsedTime);
    void loadImage(Renderer &renderer);
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void updateFrameIndex();
    void reposition(const Point &newPosition);
    void pause(bool shouldPause);
private:
    Animation();
    //Each frame of the animation has a path (image name) and a timing
    std::vector<std::pair<std::string, Uint32> > frames;
    Point position;
    Dimension size;
    Layer layer;
    Uint32 currentTicks;
    Uint32 totalTicks;
    int frameIndex;
    bool paused;
};

#endif

