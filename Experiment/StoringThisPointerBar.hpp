//File: StoringThisPointerBar.hpp
//Author:   John Miner
//Created:  11/17/11
//Modified: 11/17/11
//Purpose:  Experiment storing this pointer. What to do when it goes out of
//          scope?
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef STORING_THIS_POINTER_BAR_HPP_
#define STORING_THIS_POINTER_BAR_HPP_

#include "boost/enable_shared_from_this.hpp"

class Foo;

class Bar : public boost::enable_shared_from_this<Bar>
{
public:
    Bar();
    ~Bar();
    void barMethod();
    void giveFooThisPointer(Foo &foo);
private:
    int *heapData;
};

#endif

