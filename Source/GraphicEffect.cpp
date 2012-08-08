//File: GraphicEffect.cpp
//Author:   John Miner
//Created:  08/08/12
//Purpose:  Perform per image effects, clipping the inverse of their shape.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/GraphicEffect.hpp"
#include "../Header/GlowRectangle.hpp"

static Uint32 &GraphicEffect::COLOR_KEY()
{
    static Uint32 TMP_COLOR_KEY = SDL_MapRGB(0xFF, 0x00, 0xFF);
    return TMP_COLOR_KEY;
}

GraphicEffect::GraphicEffect(boost::shared_ptr<GlowRectangle> &glowRectangle,
    SDL_Surface *sprite) : glowRectangle(glowRectangle), alphaDirection(1)
{
    glowRectangle->glow(*this, sprite); //inits inverseSprite and inverseGlowRct
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
    SDL_SetAlpha(inverseGlowRectangle, SDL_SRCALPHA, alpha);
    applySurface(inverseGlowRectangle, glowingSprite);
}

void GraphicEffect::clipGlowRectangle(SDL_Surface *glowRectangle,
    SDL_Surface *sprite)
{
    inverseClipShape(sprite, glowRectangle, ALPHA());
    inverseGlowRectangle = SDL_DisplayFormatAlpha(glowRectangle);
    SDL_SetColorKey(inverseGlowRectangle, SDL_SRCCOLORKEY, COlOR_KEY());
    inverseClipShape(inverseSprite, inverseGlowRectangle);
}

void GraphicEffect::clockTick(Uint32 elapsedTime)
{
    alphaDirection = 1; 

    if( alpha < ALPHA_MIN )
        alphaDirection = 1;
    if( alpha > ALPHA_MAX )
        alphaDirection = -1;

    alpha += alphaDirection * elapsedTime;
}

void GraphicEffect::applySurface(SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect sourceRectangle = { 0, 0, source->w, source->h };
    SDL_Rect destinationRectangle = { 0, 0, destination->w, destination->h };

    SDL_BlitSurface(source, &sourceRectangle, destination,
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
            if( sourceRed == 0xFF && sourceBlue == 0xFF && sourceGreen == 0x00 )
            {
            }
            else if( alphaOrKey == COLOR_KEY )
            {
                destinationRed = 0xFF;
                destinationBlue = 0xFF;
                destinationGreen = 0x00;
            }
                
            if( sourceAlpha > 0x00 && alphaOrKey == ALPHA )
            {
                destinationRed = 0xFF;
                destinationBlue = 0xFF;
                destinationGreen = 0x00;
            }

            ((Uint32 *) destination->pixels)[ (i + y) * destination->w + j + x]
                = SDL_MapRGBA(destination->format, destinationRed,
                destinationGreen, destinationBlue, destinationAlpha);
        }
    }
    :
    SDL_UnlockSurface(source);
    SDL_UnlockSurface(destination);
}

