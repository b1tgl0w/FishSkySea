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

Clip::Clip()
{
    initialize();
}

Clip::Clip(const Clip &rhs)
{
    initialize();
}

Clip &Clip::operator=(const Clip &rhs)
{   
    if( &rhs == this )
        return *this;

    dispose();
    initialize();

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
    SDL_Rect clipRectangle = { 0, 0, ceil(clipSize.width), ceil(clipSize.height) };
    int tmpWidth = ceil(clipSize.width); //Need a signed int
    int tmpHeight = ceil(clipSize.height); 

    if( hasBoundary == false )
    {
        SDL_Rect noClip = { 0, 0, ceil(clipSize.width), ceil(clipSize.height) };
        return noClip;
    }

    //Casts to int make the "animation" smoother
    if( ceil(clipPosition.x) < ceil(position.x) )
        clipRectangle.x = ceil(position.x - abs(clipPosition.x));

    if( ceil(clipPosition.y) < ceil(position.y) )
        clipRectangle.y = ceil(position.y - abs(clipPosition.y));

    //adjust for zero-based coordinate system?
    if( ceil(clipPosition.x + clipSize.width) > ceil(size.width) )
        tmpWidth = ceil(size.width + position.x - abs(clipPosition.x));

    //adjust for zero-based coordinate system?
    if( ceil(clipPosition.y + clipSize.height) > ceil(size.height) )
        tmpHeight = ceil(size.height + position.y - abs(clipPosition.y));

    if( clipRectangle.x < 0 )
        clipRectangle.x = 0;
    else if( clipRectangle.x > ceil(clipSize.width) )
        clipRectangle.x = ceil(clipSize.width);

    if( clipRectangle.y < 0 )
        clipRectangle.y = 0;
    else if( clipRectangle.y > ceil(clipSize.height) )
        clipRectangle.y = ceil(clipSize.height);

    if( tmpWidth > ceil(clipSize.width) )
        tmpWidth = ceil(clipSize.width);
    else if( tmpWidth < 0 )
        tmpWidth = 0;

    if( tmpHeight > ceil(clipSize.height))
        tmpHeight = ceil(clipSize.height);
    else if( tmpHeight < 0 )
        tmpHeight = 0;
	/*
    clipRectangle.w = ceil(tmpWidth);
    clipRectangle.h = ceil(tmpHeight);
	*/
	clipRectangle.w = tmpWidth;
    clipRectangle.h = tmpHeight;

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

