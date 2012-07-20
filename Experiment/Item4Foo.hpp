//File: Item4Foo.h
//Author:   John Miner
//Created:  09/25/11
//Modified: 09/25/11
//Purpose:  Test out Scott Meyers' advice in Effective C++ for non-local
//static objects of different translation units, specifically for class-wide
//static constants
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef ITEM_4_FOO_HPP_
#define ITEM_4_FOO_HPP_

class Foo
{
public:
    static const int &MY_VAR();
};

#endif

