//File: StoringThisPointerFoo.cpp
//Author:   John Miner
//Created:  11/17/11
//Modified: 11/17/11
//Purpose:  Experiment storing this pointer. What to do when it goes out of
//          scope?
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include "StoringThisPointerFoo.hpp"
#include "StoringThisPointerBar.hpp"

void Foo::giveMeBar(boost::shared_ptr<Bar> bar)
{
    barThisCopy = bar; 
}

void Foo::useBarThisCopy()
{
    boost::shared_ptr<Bar> sharedBar = barThisCopy.lock();

    if( !sharedBar )
    {
        std::cout << "sharedBar had no references" << std::endl;
        return;
    }

    sharedBar->barMethod();
}

