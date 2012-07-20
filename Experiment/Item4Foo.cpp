//File: Item4Foo.cpp
//Author:   John Miner
//Created:  09/25/11
//Modified: 09/25/11
//Purpose:  Test out Scott Meyers' advice in Effective C++ for non-local
//static objects of different translation units, specifically for class-wide
//static constants
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "Item4Foo.hpp"

const int &Foo::MY_VAR()
{
    static const int TMP_MY_VAR = 41;
    return TMP_MY_VAR;
}

