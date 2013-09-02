//This file is distributed under the terms of the zlib license 
/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
//The software in this file originated from Sam Lantinga and the SDL library,
//  www.libsdl.org , and has been altered by John Miner.
//Copyright 2013 John Miner
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
//File: SdlUtility.cpp
//Purpose:  Modifications of SDL2 Methods

#include <iostream>
#include "../Header/SdlUtility.hpp"

SDL_Texture * SdlUtility::CreateTextureFromSurface(SDL_Renderer * renderer, 
    SDL_Surface * surface, SDL_TextureAccess access, bool alpha)
{
    const SDL_PixelFormat *fmt;
    SDL_bool needAlpha;
    Uint32 i;
    Uint32 format;
    SDL_Texture *texture;

    //CHECK_RENDERER_MAGIC(renderer, NULL);

    if( !surface ) {
        SDL_SetError("SDL_CreateTextureFromSurface() passed NULL surface");
        return NULL;
    }

    fmt = surface->format;
    if (fmt->Amask || SDL_GetColorKey(surface, NULL) == 0 || alpha ) {
        needAlpha = SDL_TRUE;
    } else {
        needAlpha = SDL_FALSE;
    }
    /*
    SDL_RendererInfo *info;
    SDL_GetRendererInfo(renderer, info);
    format = info->texture_formats[0];
    for (i = 0; i < info->num_texture_formats; ++i) {
        if (!SDL_ISPIXELFORMAT_FOURCC(info->texture_formats[i]) &&
            SDL_ISPIXELFORMAT_ALPHA(info->texture_formats[i]) == needAlpha) {
            format = info->texture_formats[i];
            break;
        }
    }*/
    format = SDL_PIXELFORMAT_ARGB8888;
    texture = SDL_CreateTexture(renderer, format, access,
                                surface->w, surface->h);
    if (!texture) {
        return NULL;
    }

    if (format == surface->format->format) {
        if (SDL_MUSTLOCK(surface)) {
            SDL_LockSurface(surface);
            SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
            SDL_UnlockSurface(surface);
        } else {
            SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
        }

    } else {
        SDL_PixelFormat *dst_fmt;
        SDL_Surface *temp = NULL;

        dst_fmt = SDL_AllocFormat(format);
        temp = SDL_ConvertSurface(surface, dst_fmt, 0);
        SDL_FreeFormat(dst_fmt);
        if (temp) {
            SDL_UpdateTexture(texture, NULL, temp->pixels, temp->pitch);
            SDL_FreeSurface(temp);
        } else {
            SDL_DestroyTexture(texture);
            return NULL;
        }
    }

    {
        Uint8 r, g, b, a;
        SDL_BlendMode blendMode;

        SDL_GetSurfaceColorMod(surface, &r, &g, &b);
        SDL_SetTextureColorMod(texture, r, g, b);

        SDL_GetSurfaceAlphaMod(surface, &a);
        SDL_SetTextureAlphaMod(texture, a);

        if (SDL_GetColorKey(surface, NULL) == 0) {
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        } else {
            SDL_GetSurfaceBlendMode(surface, &blendMode);
            SDL_SetTextureBlendMode(texture, blendMode);
        }
    }
    return texture;
}
