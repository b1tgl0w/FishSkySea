//File: Clip.hpp
//Author:   John Miner
//Created:  03/01/12
//Modified: 03/01/12
//Purpose:  Keep track of what needs to be clipped and by how much
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef CLIP_HPP_
#define CLIP_HPP_

#include <vector>
#include <SDL/SDL.h> // changed back to <SDL/SDL.h>
#include <ctime>
#include "boost/shared_ptr.hpp"
#include "Layout.hpp"
#include "Dimension.hpp"
#include "Point.hpp"
#include "FrameCleanupSubscriber.hpp"

class Clip 
{
public:
    Clip();
    Clip(const Clip &rhs);
    Clip &operator=(const Clip &rhs);
    ~Clip();
    SDL_Rect generateClipRectangle(const Point &clipPosition,
        const Dimension &clipSize);
    void onlyBoundary(const Point &position, const Dimension &size);
    void merge(const Clip &mergeWith);
protected:
    void initialize();
    void dispose();
private:
   Point position;
   Dimension size;
   bool hasBoundary;
};

#endif

