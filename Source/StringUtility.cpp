//File: StringUtility.cpp
//Author:   John Miner
//Created:  08/25/11
//Modified: 08/25/11
//Purpose:  An everything-is-static singleton that provides string manipulation
//          methods.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <sstream>
#include "../Header/StringUtility.hpp"

std::string StringUtility::toString(int number)
{
    std::stringstream ss;

    ss << number;

    return ss.str();
}

