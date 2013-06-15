//File: Animation.hpp
//Author:   John Miner
//Created 06/14/13
//Purpose: Store animation as a collection of images and timings
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <vector>
#include <SDL/SDL.h>
#include "RendererElement.hpp"
#include "Renderer.hpp"
#include "MasterClockPublisher.hpp"
#include "MasterClockSubscriber.hpp"

class Renderer;

class Animation : public MasterClockSubscriber, public Graphic,
    public boost::enable_shared_from_this<Animation>
{
public:
    Animation();
    Animation(const Animation &rhs);
    Animation &operation=(const Animation &rhs);
    void addFrame(std::string &imagePath, Uint32 duration);
    void clockTick(Uint32 elapsedTime);
    void loadImage(Renderer &renderer);
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
private:
    //Each frame of the animation has a path (image name) and a timing
    std::vector<std::pair<std::string, Uint32 duration> > frames;
    Uint32 currentTicks;
};

#endif

