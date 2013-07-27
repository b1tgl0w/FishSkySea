//File: Clip.cpp
//Author:   John Miner
//Created:  03/01/12
//Modified: 03/01/12
//Purpose:  Keep track of what needs to be clipped and by how much
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream> //delete
#include <cmath>
#include "../Header/Clip.hpp"
#include "../Header/Math.hpp"

Clip::Clip() : position(0.0, 0.0), size(0.0, 0.0), hasBoundary(false)
{ }

Clip::Clip(const Clip &rhs) : position(rhs.position), size(rhs.size),
    hasBoundary(rhs.hasBoundary)
{
}

Clip &Clip::operator=(const Clip &rhs)
{   
    if( &rhs == this )
        return *this;

    position = rhs.position;
    size = rhs.size;
    hasBoundary = rhs.hasBoundary;

    return *this;
}

Clip::~Clip()
{   
    dispose();
}

//Method:   generateClipRectangle(...)
//Purpose:  Given a position and size as well as a clipPosition and clipSize,
//          determine if any portion of the image needs to be clipped off,
//          so the resulting image would only be a portion of the original
//          image.
SDL_Rect Clip::generateClipRectangle(const Point &clipPosition, const Dimension &clipSize)
{
    SDL_Rect clipRectangle = { 0, 0, Math::ceil(clipSize.width), Math::ceil(clipSize.height) };
    int tmpWidth = Math::ceil(clipSize.width); //Need a signed int
    int tmpHeight = Math::ceil(clipSize.height); 

    if( hasBoundary == false )
    {
        SDL_Rect noClip = { 0, 0, Math::ceil(clipSize.width), Math::ceil(clipSize.height) };
        return noClip;
    }

    //Casts to int make the "animation" smoother
    if( Math::ceil(clipPosition.x) < Math::ceil(position.x) )
        clipRectangle.x = Math::ceil(position.x - Math::abs(clipPosition.x));

    if( Math::ceil(clipPosition.y) < Math::ceil(position.y) )
        clipRectangle.y = Math::ceil(position.y - Math::abs(clipPosition.y));

    //adjust for zero-based coordinate system?
    if( Math::ceil(clipPosition.x + clipSize.width) > Math::ceil(size.width) )
        tmpWidth = Math::ceil(size.width + position.x - Math::abs(clipPosition.x));

    //adjust for zero-based coordinate system?
    if( Math::ceil(clipPosition.y + clipSize.height) > Math::ceil(size.height) )
        tmpHeight = Math::ceil(size.height + position.y - Math::abs(clipPosition.y));

    if( clipRectangle.x < 0 )
        clipRectangle.x = 0;
    else if( clipRectangle.x > Math::ceil(clipSize.width) )
        clipRectangle.x = Math::ceil(clipSize.width);

    if( clipRectangle.y < 0 )
        clipRectangle.y = 0;
    else if( clipRectangle.y > Math::ceil(clipSize.height) )
        clipRectangle.y = Math::ceil(clipSize.height);

    if( tmpWidth > Math::ceil(clipSize.width) )
        tmpWidth = Math::ceil(clipSize.width);
    else if( tmpWidth < 0 )
        tmpWidth = 0;

    if( tmpHeight > Math::ceil(clipSize.height))
        tmpHeight = Math::ceil(clipSize.height);
    else if( tmpHeight < 0 )
        tmpHeight = 0;
    clipRectangle.w = Math::ceil(tmpWidth);
    clipRectangle.h = Math::ceil(tmpHeight);

    return clipRectangle;
}

//Method:   onlyBoundary(...)
//Purpose:  Set or reset the position and size of this Clip object and
//          indicate the boundary has been set
void Clip::onlyBoundary(const Point &position, const Dimension &size)
{
    this->position = position;
    this->size = size;
    hasBoundary = true;
}

//Method:   merge(...)
//Purpose:  Take the original boundary and check if any side of the new
//          clip rectangle is more restrictive. If so, restrict the original
//          boundary further
void Clip::merge(const Clip &mergeWith)
{
    if( hasBoundary == false )
    {
        position = mergeWith.position;
        size = mergeWith.size;
        hasBoundary = true;
    }
    else
    {
        if( mergeWith.position.x > position.x )
            position.x = mergeWith.position.x;
        if( mergeWith.position.y > position.y )
            position.y = mergeWith.position.y;
        if( mergeWith.size.width < size.width )
            size.width = mergeWith.size.width;
        if( mergeWith.size.height < size.height )
            size.height = mergeWith.size.height;
    }
}

void Clip::initialize()
{
    hasBoundary = false;
}

void Clip::dispose()
{
    //No-op
}

