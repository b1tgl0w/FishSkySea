//File: Transformation.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  A constraint class pertaining to graphical transformations. Allows
//          |ing of values.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Transformation.hpp"
#include "../Header/StringUtility.hpp"

Transformation::Transformation()
{
    value = None().value;
}

Transformation::Transformation(const Transformation &rhs)
{
    value = rhs.value;
}

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

Transformation Transformation::operator|(const Transformation &rhs) const
{
    return Transformation(value | rhs.value);
}

Transformation Transformation::operator^(const Transformation &rhs) const
{
    return Transformation(value ^ rhs.value);
}

bool Transformation::has(const Transformation &rhs) const
{
    return ((*this) & rhs) == rhs;
}

std::string Transformation::tellTransformations() const
{
    return StringUtility::toString(value);
}

Transformation::Transformation(int initialValue)
{
    value = initialValue;
}

bool Transformation::operator==(const Transformation &rhs) const
{
    return value == rhs.value;
}

bool Transformation::operator!=(const Transformation &rhs) const
{
    return value != rhs.value;
}

Transformation Transformation::operator&(const Transformation &rhs) const
{
    return Transformation(value & rhs.value);
}

