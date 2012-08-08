//File: GlowRectangle.hpp
//Author:   John Miner
//Created:  08/07/12
//Purpose:  A yellow rectangle that grows as big as a glowing sprite.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef GLOW_RECTANGLE_HPP_
#define GLOW_RECTANGLE_HPP_

#include <SDL/SDL.h>
#include "Dimension.hpp"

class GraphicEffect;

class GlowRectangle
{
public:
    GlowRectangle(SDL_Surface *baseOffOf, const Dimension &size);
    GlowRectangle(const GlowRectangle &rhs);
    GlowRectangle operator=(const GlowRectangle &rhs);
    void grow(const Dimension &size);
    void clip(GraphicEffect &graphicEffect, SDL_Surface *sprite);
    ~GlowRectangle(); //MUST Free Surface
private:
    GlowRectangle();
    createRectangle();
    SDL_Surface *rectangle;
    Uint32 flags; //From some image, not screen
    Dimension size;
    int bitsPerPixel;
    Uint32 RMask; //From some image, not screen
    Uint32 GMask; //From some image, not screen
    Uint32 BMask; //From some image, not screen
    //Uint32 Amask; 0x00
};

#endif

