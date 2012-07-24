//File: BorderCorner.cpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  A value constraining class used for communicating between 
//          user and a BorderLayout in regard to which corners are used
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/BorderCorner.hpp"

void BorderCorner::initialize(int value)
{
    this->value = value;
}


void BorderCorner::dispose()
{
    //No-op
}

BorderCorner::BorderCorner(int value)
{
    initialize(value);
}

BorderCorner::BorderCorner(const BorderCorner &rhs)
{
    initialize(rhs.value);
}

BorderCorner &BorderCorner::operator=(const BorderCorner &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.value);
    
    return *this;
}

BorderCorner::~BorderCorner()
{
    dispose();
}

BorderCorner BorderCorner::None()
{
    return BorderCorner(0);
}

BorderCorner BorderCorner::TopBottom()
{
    return BorderCorner(1);
}

BorderCorner BorderCorner::Sides()
{
    return BorderCorner(2);
}

bool BorderCorner::operator<(const BorderCorner &rhs) const
{
    return value < rhs.value;
}

bool BorderCorner::operator!=(const BorderCorner &rhs) const
{
    return value != rhs.value;
}

bool BorderCorner::operator==(const BorderCorner &rhs) const
{
    return value == rhs.value;
}

