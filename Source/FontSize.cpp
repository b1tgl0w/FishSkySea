//File: FontSize.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Make a FontSize type so that clients are limited to what they can
//          pass as an argument (opposed to int)
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

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

FontSize::FontSize(const FontSize &rhs)
{
    initialize(rhs.value);
}

FontSize &FontSize::operator=(const FontSize &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.value);
    
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

FontSize::FontSize(int initialValue)
{
    initialize(initialValue);
}

FontSize::FontSize() : value(0)
{
}

