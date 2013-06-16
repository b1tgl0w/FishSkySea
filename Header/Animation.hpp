//File: Animation.hpp
//Author:   John Miner
//Created 06/14/13
//Purpose: Store animation as a collection of images and timings
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <vector>
#include <string>
#include <SDL/SDL.h>
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
    void addFrame(const std::pair<std::string, Uint32> &frame);
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

