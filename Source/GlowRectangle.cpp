//File: GlowRectangle.hpp
//Author:   John Miner
//Created:  08/07/12
//Purpose:  A yellow rectangle that grows as big as a glowing sprite.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/GlowRectangle.hpp"
#include "../Header/GraphicEffect.hpp"
#include "../Header/Renderer.hpp"

//Note: baseOffOf should not be screen
GlowRectangle::GlowRectangle(SDL_Surface *baseOffOf, const Dimension &size,
    const Renderer &renderer) : 
    flags(baseOffOf->flags), bitsPerPixel(baseOffOf->format->BitsPerPixel),
    size(size), RMask(baseOffOf->format->Rmask), 
    GMask(baseOffOf->format->Gmask), BMask(baseOffOf->format->Bmask)
{
    glowColor = renderer.makeColor(0xFC, 0xE6, 0x97, 0xFF);
    createRectangle();
}

//Does a deep copy
GlowRectangle::GlowRectangle(const GlowRectangle &rhs) : 
    rectangle(SDL_DisplayFormatAlpha(rhs.rectangle)), flags(rhs.flags), 
    bitsPerPixel(rhs.bitsPerPixel), size(rhs.size), RMask(rhs.RMask), 
    GMask(rhs.GMask), BMask(rhs.BMask), glowColor(rhs.glowColor)
{
}

//Does a deep copy
GlowRectangle GlowRectangle::operator=(const GlowRectangle &rhs)
{
    if( &rhs == this )
        return *this;

    rectangle = SDL_DisplayFormatAlpha(rhs.rectangle);
    flags = rhs.flags;
    bitsPerPixel = rhs.bitsPerPixel;
    size = rhs.size;
    RMask = rhs.RMask;
    GMask = rhs.GMask;
    BMask = rhs.BMask;
    glowColor = rhs.glowColor;

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
    SDL_Rect surfaceRect = { 0, 0, size.width, size.height };
    rectangle = SDL_CreateRGBSurface(flags | SDL_SRCALPHA, size.width, 
    size.height, bitsPerPixel, RMask, GMask, BMask, 0x00);
    SDL_SetAlpha(rectangle, SDL_SRCALPHA, 0xFF);
    SDL_FillRect(rectangle, &surfaceRect, glowColor);
}

