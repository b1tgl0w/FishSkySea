//File: GraphicEffect.cpp
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
/*

#include <iostream> //delete
#include <cmath>
#include "../Header/Math.hpp"
#include "../Header/GraphicEffect.hpp"
#include "../Header/MasterClockPublisher.hpp"

const bool GraphicEffect::ALPHAD = true;
const bool GraphicEffect::COLOR_KEYED = false;
const int GraphicEffect::ALPHA_MIN = 0x11;
const int GraphicEffect::ALPHA_MAX = 0x99;

GraphicEffect::GraphicEffect(SDL_Texture *sprite) : inverseSprite(NULL),
    inverseGlowRectangle(NULL), alpha(syncAlpha()), alphaDirection(.15)
{
    clipGlowRectangle(sprite);
}

//Deep copy since not using shared_ptrs
//A better way?
GraphicEffect::GraphicEffect(const GraphicEffect &rhs) : 
    inverseSprite(rhs.inverseSprite), 
    inverseGlowRectangle(rhs.inverseGlowRectangle),
    alpha(rhs.alpha), alphaDirection(rhs.alphaDirection)
{ }

//Deep copy since not using shared_ptrs
//A better way?
GraphicEffect GraphicEffect::operator=(const GraphicEffect &rhs)
{
    if( &rhs == this )
        return *this;

    inverseSprite = rhs.inverseSprite;
    inverseGlowRectangle = rhs.inverseGlowRectangle;
    alpha = rhs.alpha;
    alphaDirection = rhs.alphaDirection;
    

    return *this;
}

GraphicEffect::~GraphicEffect()
{
    SDL_DestroyTexture(inverseSprite);
    SDL_DestroyTexture(inverseGlowRectangle);
}

void GraphicEffect::glow(SDL_Texture *originalSprite, SDL_Texture 
    *glowingSprite)
{
    applySurface(originalSprite, glowingSprite);
    SDL_SetAlpha(inverseGlowRectangle, SDL_SRCALPHA, (Uint32) alpha);
    applySurface(inverseGlowRectangle, glowingSprite);
}

void GraphicEffect::clipGlowRectangle(SDL_Renderer *sdlRenderer, 
    SDL_Texture *sprite)
{
    Uint32 format = 0;
    int access = 0;
    int w = 0;
    int h = 0;

    SDL_QueryTexture(texture, &format, &access, &w, &h);

    if( !inverseSprite )
        inverseSprite = SDL_CreateTexture(sdlRenderer, format, access, w, h);
            
    if( !inverseGlowRectangle )
        inverseGlowRectangle = SDL_CreateTexture(sdlRenderer, format, access, w, h);

    const Uint32 COLOR_KEY = 0xFF00FF);
    Uint32 yellow = 0xFCE697;
    SDL_Rect rect = { 0, 0, w, h };
    SDL_FillRect(inverseSprite, &rect, yellow);
    inverseClipShape(sprite, inverseSprite, ALPHAD);
    SDL_FillRect(inverseGlowRectangle, &rect, yellow);
    inverseClipShape(inverseSprite, inverseGlowRectangle, COLOR_KEYED);
}

void GraphicEffect::clockTick(Uint32 elapsedTime)
{
    if( alpha < ALPHA_MIN )
        alphaDirection = .15;
    if( alpha > ALPHA_MAX )
        alphaDirection = -.15;

    alpha += alphaDirection * elapsedTime;
}

void GraphicEffect::applySurface(SDL_Renderer *sdlRenderer, SDL_Texture *toDraw,
    const Point &position, const Dimension &size)
{
    SDL_Rect destinationRectangle = { position.x, position.y, Math::ceil(size.width), 
        Math::ceil(size.height) };

    SDL_RenderCopy(sdlRenderer, toDraw, NULL, &destinationRectangle);
}

void GraphicEffect::inverseClipShape(SDL_Texture *source, 
    SDL_Texture *destination, bool alphaOrKey)
{
    Uint8 sourceRed;
    Uint8 sourceGreen;
    Uint8 sourceBlue;
    Uint8 sourceAlpha;
    Uint8 destRed;
    Uint8 destGreen;
    Uint8 destBlue;
    Uint8 destAlpha;
    Uint32 sourceFormat;
    int sourceAccess;
    int sourceW;
    int sourceH;
    Uint32 destFormat;
    int destAccess;
    int destW;
    int destH;

    SDL_QueryTexture(source, &sourceFormat, &sourceAccess, &sourceW, &sourceH);
    SDL_QueryTexture(dest, &destFormat, &destAccess, &destW, &destH);

    int x = destW / 2 - sourceW / 2;
    int y = destH/ 2 - sourceH / 2;

    void *sourcePixels;
    void *destPixels;
    int sourcePitch;
    int destPitch;
    SDL_LockTexture(source, NULL, &sourcePixels, &sourcePitch);
    SDL_LockTexture(destination, NULL &destPixels, &destPitch);

    for( int i = 0; i < sourceH; ++i )
    {
        for(int j = 0; j < sourceW; ++j)
        {
            Uint32 sourcePixel = ((Uint32 *)sourcePixels)[ i * sourceW + j];
            Uint32 destPixel = ((Uint32 *) destinationPixels)[ (i + y) * destW + j + x];
            //ASSUME FORMAT ARGB
            sourceAlpha = (sourcePixel >> 24) 0xFF;
            sourceRed = (sourcePixel >> 16) & 0xFF;
            sourceGreen = (sourcePixel >> 8) & 0xFF;
            sourceBlue = sourcePixel & 0xFF;
            destAlpha = (destPixel >> 24) & 0xFF;
            desteRed = (destPixel >> 16) & 0xFF;
            destGreen = (destPixel >> 8) & 0xFF;
            destBlue = destPixel & 0xFF;

            //destAlpha ^= sourceAlpha; 
            if( sourceRed == 0xFF && sourceGreen == 0x00 && sourceBlue == 0xFF)
            {
            }
            else if( alphaOrKey == COLOR_KEYED )
            {
                destRed = 0xFF;
                destGreen = 0x00;
                destBlue = 0xFF;
            }
                
            if( sourceAlpha > 0x00 && alphaOrKey == ALPHAD )
            {
                destRed = 0xFF;
                destGreen = 0x00;
                destBlue = 0xFF;
            }

            ((Uint32 *) destinationPixels)[ (i + y) * destW + j + x]
                = destAlpha & 0xFF000000 + destRed & 0x00FF0000 + destGreen
                    & 0x0000FF00 + destBlue & 0x000000FF;
        }
    }
    
    SDL_UnlockTexture(source);
    SDL_UnlockTexture(destination);
}

double GraphicEffect::syncAlpha()
{
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    Uint32 age = masterClockPublisher->age();
    return ((int) Math::round(age * alphaDirection)) % (ALPHA_MAX - ALPHA_MIN) + 
        ALPHA_MIN;
}
*/

