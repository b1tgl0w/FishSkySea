//File: StringUtility.h
//Author:   John Miner
//Created:  08/25/11
//Modified: 09/28/11
//Purpose:  An everything-is-static singleton that provides string manipulation
//          methods.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef STRING_UTILITY_HPP_
#define STRING_UTILITY_HPP_

#include <string>
#include "boost/noncopyable.hpp"

class StringUtility : private boost::noncopyable
{
public:
    static std::string toString(int number);
protected:
    StringUtility();
};

#endif

