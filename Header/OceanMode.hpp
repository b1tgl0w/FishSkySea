//File: OceanMode.hpp
//Author:   John Miner
//Created:  12/17/12
//Purpose:  Prevents bad values, anything other than CreditMode or GameMode,
//          referring to ocean states
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef OCEAN_MODE_HPP_
#define OCEAN_MODE_HPP_

class OceanMode
{
public:
    static const OceanMode GAME_MODE();
    static const OceanMode CREDIT_MODE();
    bool operator==(const OceanMode &rhs) const;
    bool operator!=(const OceanMode &rhs) const;
    OceanMode();
    OceanMode(const OceanMode &rhs);
    OceanMode &operator=(const OceanMode &rhs);
private:
    explicit OceanMode(int initialValue);
    int value;
};

#endif

