//File: Animation.cpp
//Author:   John Miner
//Created 06/14/13
//Purpose: Store animation as a collection of images and timings
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Animation.hpp"
#include "../Header/Renderer.hpp"

Animation::Animation() : currentTicks(0)
{
}

Animation::Animation(const Animation &rhs) : frames(rhs.frames), currentTicks(
    rhs.currentTicks)
{
}

Animation &Animation::operation=(const Animation &rhs)
{
    if( &rhs == this )
        return *this;

    frames = rhs.frames;
    currentTicks = rhs.currentTicks;

    return * this;
}

void Animation::loadImage(Renderer &renderer)
{
}

void Animation::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
}

//Assumes image has been loaded
void Animation::addFrame(const std::pair<std::string, Uint32> &frame)
{
    frames.push_back(frame);
    
}


void Animation::clockTick(Uint32 elapsedTime)
{
}

void Animation::pause(bool shouldPause)
{
}

