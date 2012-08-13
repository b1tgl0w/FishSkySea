//File: GraphicEffect.cpp
//Author:   John Miner
//Created:  08/08/12
//Purpose:  Perform per image effects, clipping the inverse of their shape.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream> //delete
#include <cmath>
#include "../Header/GraphicEffect.hpp"
#include "../Header/GlowRectangle.hpp"
#include "../Header/MasterClockPublisher.hpp"

const bool GraphicEffect::ALPHAD = true;
const bool GraphicEffect::COLOR_KEYED = false;
const int GraphicEffect::ALPHA_MIN = 0x11;
const int GraphicEffect::ALPHA_MAX = 0x99;

GraphicEffect::GraphicEffect(boost::shared_ptr<GlowRectangle> &glowRectangle,
    SDL_Surface *sprite) : glowRectangle(glowRectangle), alpha(syncAlpha()),
    alphaDirection(.15)
{
    inverseGlowRectangle = 0x00;
    inverseSprite = 0x00;
    glowRectangle->clip(*this, sprite); //inits inverseSprite and inverseGlowRct
}

//Deep copy since not using shared_ptrs
//A better way?
GraphicEffect::GraphicEffect(const GraphicEffect &rhs) : glowRectangle(
    rhs.glowRectangle), inverseSprite(SDL_DisplayFormatAlpha(rhs.inverseSprite)), 
    inverseGlowRectangle(SDL_DisplayFormatAlpha(rhs.inverseGlowRectangle)),
    alpha(rhs.alpha), alphaDirection(rhs.alphaDirection)
{
}

//Deep copy since not using shared_ptrs
//A better way?
GraphicEffect GraphicEffect::operator=(const GraphicEffect &rhs)
{
    if( &rhs == this )
        return *this;

    glowRectangle = rhs.glowRectangle;
    inverseSprite = SDL_DisplayFormatAlpha(rhs.inverseSprite);
    inverseGlowRectangle = SDL_DisplayFormatAlpha(rhs.inverseGlowRectangle);
    alpha = rhs.alpha;
    alphaDirection = rhs.alphaDirection;

    return *this;
}

GraphicEffect::~GraphicEffect()
{
    SDL_FreeSurface(inverseSprite);
    SDL_FreeSurface(inverseGlowRectangle);
}

void GraphicEffect::glow(SDL_Surface *originalSprite, SDL_Surface 
    *glowingSprite)
{
    applySurface(originalSprite, glowingSprite);
    SDL_SetAlpha(inverseGlowRectangle, SDL_SRCALPHA, (Uint32) alpha);
    applySurface(inverseGlowRectangle, glowingSprite);
}

void GraphicEffect::clipGlowRectangle(SDL_Surface *glowRectangle,
    SDL_Surface *sprite)
{
    if( !inverseSprite )
        inverseSprite = SDL_CreateRGBSurface(sprite->flags | SDL_SRCALPHA,
        glowRectangle->w, glowRectangle->h, sprite->format->BitsPerPixel,
        sprite->format->Rmask, sprite->format->Gmask, sprite->format->Bmask,
        0x00);
    if( !inverseGlowRectangle )
        inverseGlowRectangle = SDL_CreateRGBSurface(sprite->flags | SDL_SRCALPHA,
        glowRectangle->w, glowRectangle->h, sprite->format->BitsPerPixel,
        sprite->format->Rmask, sprite->format->Gmask, sprite->format->Bmask,
        0x00);
    const Uint32 COLOR_KEY = SDL_MapRGB(inverseSprite->format, 0xFF, 0x00, 0xFF);
    Uint32 yellow = SDL_MapRGB(inverseSprite->format, 0xFC, 0xE6, 0x97);
    SDL_SetColorKey(inverseSprite, SDL_SRCCOLORKEY, COLOR_KEY);
    SDL_SetColorKey(inverseGlowRectangle, SDL_SRCCOLORKEY, COLOR_KEY);
    SDL_Rect rect = { 0, 0, glowRectangle->w, glowRectangle->h };
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

void GraphicEffect::applySurface(SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect destinationRectangle = { 0, 0, destination->w, destination->h };

    SDL_BlitSurface(source, NULL, destination,
        &destinationRectangle);
}

void GraphicEffect::inverseClipShape(SDL_Surface *source, 
    SDL_Surface *destination, bool alphaOrKey)
{
    int x = destination->w / 2 - source->w / 2;
    int y = destination->h / 2 - source->h / 2;
    Uint8 sourceRed;
    Uint8 sourceGreen;
    Uint8 sourceBlue;
    Uint8 sourceAlpha;
    Uint8 destinationRed;
    Uint8 destinationGreen;
    Uint8 destinationBlue;
    Uint8 destinationAlpha;

    SDL_LockSurface(source);
    SDL_LockSurface(destination);

    for( int i = 0; i < source->h; ++i )
    {
        for(int j = 0; j < source->w; ++j)
        {
            SDL_GetRGBA(((Uint32 *) source->pixels)[ i * source->w + j],
                source->format, &sourceRed, &sourceGreen, &sourceBlue,
                &sourceAlpha);
            SDL_GetRGBA(((Uint32 *) destination->pixels)[ (i + y) *
                destination->w + j + x],
                destination->format, &destinationRed, &destinationGreen, 
                &destinationBlue, &destinationAlpha);

            //destinationAlpha ^= sourceAlpha; 
            if( sourceRed == 0xFF && sourceGreen == 0x00 && sourceBlue == 0xFF)
            {
            }
            else if( alphaOrKey == COLOR_KEYED )
            {
                destinationRed = 0xFF;
                destinationGreen = 0x00;
                destinationBlue = 0xFF;
            }
                
            if( sourceAlpha > 0x00 && alphaOrKey == ALPHAD )
            {
                destinationRed = 0xFF;
                destinationGreen = 0x00;
                destinationBlue = 0xFF;
            }

            ((Uint32 *) destination->pixels)[ (i + y) * destination->w + j + x]
                = SDL_MapRGBA(destination->format, destinationRed,
                destinationGreen, destinationBlue, destinationAlpha);
        }
    }
    
    SDL_UnlockSurface(source);
    SDL_UnlockSurface(destination);
}

double GraphicEffect::syncAlpha()
{
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    Uint32 age = masterClockPublisher->age();
    return ((int) round(age * alphaDirection)) % (ALPHA_MAX - ALPHA_MIN) + 
        ALPHA_MIN;
}

