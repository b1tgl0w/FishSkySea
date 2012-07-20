//File: Sandbox/BoostWeakPointersDriver.cpp
//Author: John Miner
//Created:  09/21/11
//Modified: 09/22/11
//Purpose:  Experiment with boost weak pointers
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include "BoostWeakPointersBar.hpp"
#include "BoostWeakPointersFoo.hpp"
#include "BoostWeakPointersBaz.hpp"
#include "boost/shared_ptr.hpp"

int main(int argc, char **argv)
{
    boost::shared_ptr<Baz> sharedBaz(new Baz);

    std::cout << sharedBaz->method("called from main") << std::endl;

    Foo foo(sharedBaz);
    Bar bar(sharedBaz);

    std::cout << foo.operateOnBaz() << std::endl;
    std::cout << bar.operateOnBaz() << std::endl;
    sharedBaz.reset();
    std::cout << foo.operateOnBaz() << std::endl;
    std::cout << bar.operateOnBaz() << std::endl;

    return EXIT_SUCCESS;
}

