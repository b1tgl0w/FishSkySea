//File: Sandbox/BoostWeakPointersFoo.cpp
//Author: John Miner
//Created:  09/21/11
//Modified: 09/22/11
//Purpose:  Experiment with boost weak pointers
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include "BoostWeakPointersFoo.hpp"
#include "BoostWeakPointersBaz.hpp"

std::string Foo::operateOnBaz()
{
    boost::shared_ptr<Baz> sharedBaz = foosBaz.lock();

    if(sharedBaz)
    {
        return sharedBaz->method("called from class Foo");
    }

    return "foosBaz had already been released";
}

Foo::Foo(boost::shared_ptr<Baz> sharedBaz)
{
    std::cout << "sharedBaz.use_count():" <<  sharedBaz.use_count() << std::endl;
    foosBaz = sharedBaz;
    std::cout << "foosBaz.use_count():" <<  foosBaz.use_count() << std::endl;
}

