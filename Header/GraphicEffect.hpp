//File: GraphicEffect.hpp
//Author:   John Miner
//Created:  08/08/12
//Purpose:  Perform per image effects, clipping the inverse of their shape.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef GRAPHIC_EFFECT_HPP_
#define GRAPHIC_EFFECT_HPP_

#include <SDL/SDL.h>
#include "boost/shared_ptr.hpp"
#include "MasterClockSubscriber.hpp"

class GlowRectangle;

class GraphicEffect : MasterClockSubscriber
{
public:
    GraphicEffect(boost::shared_ptr<GlowRectangle> &glowRectangle,
        SDL_Surface *sprite);
    GraphicEffect(const GraphicEffect &rhs);
    GraphicEffect operator=(const GraphicEffect &rhs);
    ~GraphicEffect();
    void glow(SDL_Surface *originalSprite, SDL_Surface *glowingSprite);
    void clipGlowRectangle(SDL_Surface *glowRectangle, SDL_Surface *sprite);
    void clockTick(Uint32 elapsedTime);
    static Uint32 &COLOR_KEY();
private:
    GraphicEffect();
    void applySurface(SDL_Surface *source, SDL_Surface *destination);
    void inverseClipShape(SDL_Surface *source, SDL_Surface *destination,
        bool alphaOrKey);
    clipShape(SDL_Surface *toClip);
    boost::shared_ptr<GlowRectangle> glowRectangle;
    SDL_Surface *inverseSprite;
    SDL_Surface *inverseGlowRectangle;
    Uint32 alpha;
    int alphaDirection;
    const bool ALPHA = true;
    const bool COLOR_KEY = false;
    static short ALPHA_MIN = 0x11;
    static short ALPHA_MAX = 0x99;
};

#endif

