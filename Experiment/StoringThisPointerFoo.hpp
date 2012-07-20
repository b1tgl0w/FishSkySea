//File: StoringThisPointerFoo.hpp
//Author:   John Miner
//Created:  11/17/11
//Modified: 11/17/11
//Purpose:  Experiment storing this pointer. What to do when it goes out of
//          scope?
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef STORING_THIS_POINTER_FOO_HPP_
#define STORING_THIS_POINTER_FOO_HPP_

#include "boost/weak_ptr.hpp"
#include "boost/shared_ptr.hpp"

class Bar;

class Foo
{
public:
    void giveMeBar(boost::shared_ptr<Bar> bar);
    void useBarThisCopy();
private:
    boost::weak_ptr<Bar> barThisCopy;
};

#endif

