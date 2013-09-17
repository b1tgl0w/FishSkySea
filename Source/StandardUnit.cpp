//File: StandardUnit.hpp
//Author:   John Miner
//Created 06/14/13
//Purpose: Store animation as a collection of images and timings
//Copyright 2013 John Miner
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

#include "../Header/StandardUnit.hpp"

const double StandardUnit::DIMENSION()
{
    static const double TMP = 8.0;
    return TMP;
}

const double StandardUnit::SPEED()
{
    static const double TMP = 0.015625;
    return TMP;
}

const Uint32 StandardUnit::DURATION()
{
    static const Uint32 TMP = 16;
    return TMP;
}

const Uint32 StandardUnit::BLACK()
{
    //FIX to match art
    static const Uint32 TMP = 0x170024FF;
    return TMP;
}

const SDL_Color StandardUnit::SDL_BLACK()
{
    //FIX to match art
    static const SDL_Color TMP = { 0x17, 0x00, 0x24, 0xFF };
    return TMP;
}

const Uint32 StandardUnit::WHITE()
{
    //FIX to match art
    static const Uint32 TMP = 0xFCE3FCFF;
    return TMP;
}

const SDL_Color StandardUnit::SDL_WHITE()
{
    //FIX to match art
    static const SDL_Color TMP = { 0xFF, 0xE3, 0xFC, 0xFC };
    return TMP;
}


