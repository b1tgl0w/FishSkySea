//File: StoringThisPointerBar.cpp
//Author:   John Miner
//Created:  11/17/11
//Modified: 11/17/11
//Purpose:  Experiment storing this pointer. What to do when it goes out of
//          scope?
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include "StoringThisPointerBar.hpp"
#include "StoringThisPointerFoo.hpp"

Bar::Bar()
{
    heapData = new int;
    *heapData = 1337;
}

Bar::~Bar()
{
    delete heapData;
}

void Bar::barMethod()
{
    std::cout << "Bar::barMethod()" << std::endl;
    std::cout << "heapData = " << *heapData << std::endl;
}

void Bar::giveFooThisPointer(Foo &foo)
{
    foo.giveMeBar(shared_from_this());
}

