//File: OceanMode.cpp
//Author:   John Miner
//Created:  12/17/12
//Purpose:  Prevents bad values, anything other than CreditMode or GameMode,
//          referring to ocean states
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/OceanMode.hpp"

const OceanMode OceanMode::GAME_MODE()
{
    return OceanMode(1 << 0);
}

const OceanMode OceanMode::CREDIT_MODE()
{
    return OceanMode(1 << 1);
}

OceanMode::OceanMode(int initialValue) : value(initialValue)
{ }

bool OceanMode::operator==(const OceanMode &rhs) const
{
    return value == rhs.value;
}

bool OceanMode::operator!=(const OceanMode &rhs) const
{
    return value != rhs.value;
}

OceanMode::OceanMode() : value(0)
{ }

OceanMode::OceanMode(const OceanMode &rhs) : value(rhs.value)
{ }

OceanMode &OceanMode::operator=(const OceanMode &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;

    return *this;
}

