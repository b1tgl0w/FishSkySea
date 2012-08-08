//File: GlowRectangle.hpp
//Author:   John Miner
//Created:  08/07/12
//Purpose:  A yellow rectangle that grows as big as a glowing sprite.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/GlowRectangle.hpp"
#include "../Header/GraphicEffect.hpp"

//Note: baseOffOf should not be screen
GlowRectangle::GlowRectangle(SDL_Surface *baseOffOf, const Dimension &size) : 
    flags(baseOffOf->flags), bitsPerPixel(baseOffOf->format->BitsPerPixel),
    size(size), RMask(baseOffOf->RMask), GMask(baseOffOf->GMask), BMask(
    baseOffOf->BMask)
{
    createRectangle();
}

GlowRectangle::GlowRectangle(const GlowRectangle &rhs) : 
    rectangle(rhs.rectangle), flags(rhs.flags), bitsPerPixel(rhs.bitsPerPixel), 
    size(rhs.size), RMask(rhs.RMask), GMask(rhs.GMask), BMask(rhs.BMask)
{
}

GlowRectangle::GlowRectangle operator=(const GlowRectangle &rhs)
{
    if( &rhs == this )
        return *this;

    rectangle = rhs.rectangle;
    flags = rhs.flags;
    bitsPerPixel = rhs.bitsPerPixel;
    size = rhs.size;
    RMask = rhs.RMask;
    GMask = rhs.GMask;
    BMask = rhs.BMask;

    return *this;
}

void GlowRectangle::grow(const Dimension &size)
{
    bool updateSurface = false;

    if( size.width > this->size.width )
    {
        this->size.width = size.width;
        updateSurface = true;
    }
    if( size.height > this->size.height )
    {
        this->size.height = size.height;
        updateSurface = true;
    }

    if( updateSurface )
    {
        SDL_FreeSurface(rectangle);
        createRectangle();
    }
}

void GlowRectangle::clip(GraphicEffect &graphicEffect, SDL_Surface *
    sprite)
{
    graphicEffect.clipGlowRectangle(rectangle, sprite);
}

GlowRectangle::~GlowRectangle()
{
    SDL_FreeSurface(rectangle);
}

//Note: Does NOT free surface first
void GlowRectangle::createRectangle()
{
    const Uint32 GLOW_COLOR = SDL_MapRGBA(0xFC, 0xE6, 0x97, 0xFF);
    SDL_Rect surfaceRect = { 0, 0, size.width, size.height };
    rectangle = SDL_CreateRGBSurface(flags | SDL_SRC_ALPHA, size.width, 
    size.height, bitsPerPixel, RMask, GMask, BMask, 0x00);
    SDL_SetAlpha(SDL_SRC_ALPHA, rectangle, 0xFF);
    SDL_FillRect(rectangle, &surfaceRect, GLOW_COLOR);
}

