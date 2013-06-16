//File: Animation.cpp
//Author:   John Miner
//Created 06/14/13
//Purpose: Store animation as a collection of images and timings
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Animation.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/ImageRendererElement.hpp"

Animation::Animation(const Point &newPosition, const Dimension &newSize,
    const Layer &newLayer) : position(newPosition), size(newSize),
    layer(newLayer), currentTicks(0), totalTicks(0), frameIndex(0),
    paused(false)
{
}

Animation::Animation(const Animation &rhs) : frames(rhs.frames), 
    position(rhs.position), size(rhs.size), layer(rhs.layer), currentTicks(
    rhs.currentTicks), totalTicks(rhs.totalTicks), frameIndex(rhs.frameIndex),
    paused(rhs.paused)
{
}

Animation &Animation::operator=(const Animation &rhs)
{
    if( &rhs == this )
        return *this;

    frames = rhs.frames;
    position = rhs.position;
    size = rhs.size;
    layer = rhs.layer;
    currentTicks = rhs.currentTicks;
    totalTicks = rhs.totalTicks;
    frameIndex = rhs.frameIndex;
    paused = rhs.paused;

    return * this;
}

//Animation is not responsible for loading images. This method does nothing
void Animation::loadImage(Renderer &renderer)
{
    //Throw exception?
}

void Animation::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    updateFrameIndex();
    ImageRendererElement re(frames[frameIndex].first,
        layer.integer(), position, size);
    layout->drawWhenReady(re);
}

void Animation::updateFrameIndex()
{
    Uint32 currentTotal = 0;
    frameIndex = 0;
    int i = 0;

    for( std::vector<std::pair<std::string, Uint32> >::iterator it = 
        frames.begin(); it != frames.end(); ++it, ++i)
    {
        currentTotal += it->second;

        if( currentTicks <= currentTotal )
            frameIndex = i;
    }
}

void Animation::reposition(const Point &newPosition)
{
    position.x = newPosition.x;
    position.y = newPosition.y;
}

//Assumes image has been loaded
void Animation::addFrame(const std::pair<std::string, Uint32> &frame)
{
    frames.push_back(frame);
    totalTicks += frame.second;
}


void Animation::clockTick(Uint32 elapsedTime)
{
    if( !paused )
    {
        currentTicks += elapsedTime;
        currentTicks = Math::cycle(currentTicks, 0, totalTicks);
    }
}

void Animation::pause(bool shouldPause)
{
    paused = shouldPause;
}

