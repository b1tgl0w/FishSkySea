//File: GraphicEffect.hpp
//Author:   John Miner
//Created:  08/08/12
//Purpose:  Perform per image effects, clipping the inverse of their shape.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/

#ifndef GRAPHIC_EFFECT_HPP_
#define GRAPHIC_EFFECT_HPP_

#include <SDL2/SDL.h> 
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

