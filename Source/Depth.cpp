//File: Depth.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Make a Depth type so that clients are limited to what they can
//          pass as an argument (opposed to int)
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Depth.hpp"

const Depth Depth::SURFACE()
{
    static const Depth TMP_SURFACE(1);
    return TMP_SURFACE;
}

const Depth Depth::ROW1()
{
    static const Depth TMP_ROW_1(2);
    return TMP_ROW_1;
}

const Depth Depth::ROW2()
{
    static const Depth TMP_ROW2(3);
    return TMP_ROW2;
}

const Depth Depth::ROW3()
{
    static const Depth TMP_ROW3(4);
    return TMP_ROW3;
}

const Depth Depth::ROW4()
{
    static const Depth TMP_ROW4(5);
    return TMP_ROW4;
}

const Depth Depth::ROW5()
{
    static const Depth TMP_ROW5(6);
    return TMP_ROW5;
}

const Depth Depth::ROW6()
{
    static const Depth TMP_ROW6(7);
    return TMP_ROW6;
}

const Depth Depth::SEA_FLOOR()
{
    static const Depth TMP_SEA_FLOOR(8);
    return TMP_SEA_FLOOR;
}

Depth::Depth()
{
    initialize(0); //Surface
}
    
Depth::Depth(const Depth &rhs)
{
    initialize(rhs.value);
}

Depth &Depth::operator=(const Depth &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.value);
    
    return *this;
}

Depth::~Depth()
{
    dispose();
}

void Depth::initialize(int value)
{
    this->value = value;
}

void Depth::dispose()
{
}

bool Depth::operator==(const Depth &rhs)
{
    return value == rhs.value;
}

bool Depth::operator<(const Depth &rhs) const
{
    return value < rhs.value;
}

Depth::Depth(int initialValue)
{
    initialize(initialValue);
}



