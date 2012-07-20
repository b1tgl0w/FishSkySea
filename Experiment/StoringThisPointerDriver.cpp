//File: StoringThisPointerDriver.cpp
//Author:   John Miner
//Created:  11/17/11
//Modified: 11/17/11
//Purpose:  Experiment storing this pointer. What to do when it goes out of
//          scope?
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <cstdlib>
#include <iostream>
#include "boost/shared_ptr.hpp"
#include "StoringThisPointerFoo.hpp"
#include "StoringThisPointerBar.hpp"

void fooUsesBarInScope();
void barGoesOutOfScope(Foo &foo);

int main(int argc, char **argv)
{
    fooUsesBarInScope();
    Foo foo;
    barGoesOutOfScope(foo);
    foo.useBarThisCopy();

    return EXIT_SUCCESS;
}


void fooUsesBarInScope()
{
    Foo foo;
    boost::shared_ptr<Bar> bar(new Bar);

    bar->giveFooThisPointer(foo);
    foo.useBarThisCopy();
}

void barGoesOutOfScope(Foo &foo)
{
    boost::shared_ptr<Bar> bar(new Bar);
    bar->giveFooThisPointer(foo);
}

