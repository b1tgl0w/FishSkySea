//File: Container.hpp
//Author:   John Miner
//Created:  03/21/12
//Modified: 03/21/12
//Purpose:  Determine how to return shared ptrs from an Abstract Factory and
//          store those ptrs as base class ptrs
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <list>
#include "boost/shared_ptr.hpp"

class Base;

class Container
{
public:
    void store(Base &base);
    void printAll();
private:
    std::list<boost::shared_ptr<Base> > l;
};

#endif

