//File: FontSize.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Make a FontSize type so that clients are limited to what they can
//          pass as an argument (opposed to int)
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

#include "../Header/FontSize.hpp"
#include "../Header/Math.hpp"

const FontSize FontSize::Huge()
{
    static const FontSize TMP1(1);
    return TMP1;
}

const FontSize FontSize::Big()
{
    static const FontSize TMP2(2);
    return TMP2;
}

const FontSize FontSize::Medium()
{
    static const FontSize TMP3(3);
    return TMP3;
}

const FontSize FontSize::Small()
{
    static const FontSize TMP4(4);
    return TMP4;
}

FontSize::FontSize(const FontSize &rhs) : value(rhs.value)
{
}

FontSize &FontSize::operator=(const FontSize &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;

    return *this;
}

FontSize::~FontSize()
{
    dispose();
}

void FontSize::initialize(int value)
{
    this->value = value;
}

void FontSize::dispose()
{
}

bool FontSize::operator==(const FontSize &rhs) const
{
    return value == rhs.value;
}

bool FontSize::operator<(const FontSize &rhs) const
{
    return value < rhs.value;
}

FontSize::FontSize(int initialValue) : value(initialValue)
{
}

FontSize::FontSize() : value(0)
{
}

