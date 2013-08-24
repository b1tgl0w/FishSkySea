//File: Transformation.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  A constraint class pertaining to graphical transformations. Allows
//          |ing of values.
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


#include "../Header/Transformation.hpp"
#include "../Header/StringUtility.hpp"

Transformation::Transformation() : value(Transformation::None().value)
{ }

Transformation::Transformation(const Transformation &rhs) : value(rhs.value)
{ }

Transformation &Transformation::operator=(const Transformation &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;

    return *this;
}

Transformation Transformation::None()
{
    return Transformation(0);
}

Transformation Transformation::FlipVertical()
{
    return Transformation(1 << 0);
}

Transformation Transformation::FlipHorizontal()
{
    return Transformation(1 << 1);
}

Transformation Transformation::Glow()
{
    return Transformation(1 << 2);
}

Transformation Transformation::HighlightText()
{
    return Transformation(1 << 3);
}

Transformation Transformation::operator|(const Transformation &rhs) const
{
    return Transformation(value | rhs.value);
}

Transformation Transformation::operator^(const Transformation &rhs) const
{
    return Transformation(value ^ rhs.value);
}

Transformation Transformation::operator&(const Transformation &rhs) const
{
    return Transformation(value & rhs.value);
}

bool Transformation::has(const Transformation &rhs) const
{
    return ((*this) & rhs) == rhs;
}

std::string Transformation::tellTransformations() const
{
    //SDL2.0 broke this. Quick fix
    //Old code: //return StringUtility::toString(value);

    std::string ret;

    if( has(Transformation::HighlightText()) )
        ret += "HighlightText";

    return ret;
}

Transformation::Transformation(int initialValue) : value(initialValue)
{ }

bool Transformation::operator==(const Transformation &rhs) const
{
    return value == rhs.value;
}

bool Transformation::operator!=(const Transformation &rhs) const
{
    return value != rhs.value;
}

