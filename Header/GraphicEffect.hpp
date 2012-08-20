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

class GraphicEffect : public MasterClockSubscriber
{
public:
    GraphicEffect(SDL_Surface *sprite);
    GraphicEffect(const GraphicEffect &rhs);
    GraphicEffect operator=(const GraphicEffect &rhs);
    ~GraphicEffect();
    void glow(SDL_Surface *originalSprite, SDL_Surface *glowingSprite);
    void clipGlowRectangle(SDL_Surface *sprite);
    void clockTick(Uint32 elapsedTime);
private:
    GraphicEffect();
    void applySurface(SDL_Surface *source, SDL_Surface *destination);
    void inverseClipShape(SDL_Surface *source, SDL_Surface *destination,
        bool alphaOrKey);
    double syncAlpha();
    SDL_Surface *inverseSprite;
    SDL_Surface *inverseGlowRectangle;
    double alpha;
    double alphaDirection;
    static const bool ALPHAD;
    static const bool COLOR_KEYED;
    static const int ALPHA_MIN;
    static const int ALPHA_MAX;
};

#endif

