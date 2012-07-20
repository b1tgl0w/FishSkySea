//File: Base.hpp
//Author:   John Miner
//Created:  03/21/12
//Modified: 03/21/12
//Purpose:  Determine how to return shared ptrs from an Abstract Factory and
//          store those ptrs as base class ptrs
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef BASE_H_
#define BASE_H_

#include "boost/shared_ptr.hpp"

class Base
{
public:
    virtual void print() = 0;
    virtual boost::shared_ptr<Base> manufacture() = 0;
};

#endif

