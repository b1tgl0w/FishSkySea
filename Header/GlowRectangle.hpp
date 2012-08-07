//File: GlowRectangle.hpp
//Author:   John Miner
//Created:  08/07/12
//Purpose:  A yellow rectangle that grows as big as a glowing sprite.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef GLOW_RECTANGLE_HPP_
#define GLOW_RECTANGLE_HPP_

class GlowRectangle
{
public:
    GlowRectangle();
    GlowRectangle(const GlowRectangle &rhs);
    GlowRectangle operator=(const GlowRectangle &rhs);
    void grow(const Dimension &size);
    void glow(const GraphicEffect &graphicEffect);
    ~GlowRectangle(); //MUST Free Surface
private:
    SDL_Surface *rectangle;
    Uint32 flags; //From some image, not screen
    Dimension size;
    int bitsPerPixel;
    Uint32 Rmask; //From some image, not screen
    Uint32 Gmask; //From some image, not screen
    Uint32 Bmask; //From some image, not screen
    //Uint32 Amask; 0x00
};

#endif

