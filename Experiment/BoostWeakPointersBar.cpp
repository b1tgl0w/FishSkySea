//File: Sandbox/BoostWeakPointersBar.cpp
//Author: John Miner
//Created:  09/21/11
//Modified: 09/22/11
//Purpose:  Experiment with boost weak pointers
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "BoostWeakPointersBar.hpp"
#include "BoostWeakPointersBaz.hpp"

std::string Bar::operateOnBaz()
{
    boost::shared_ptr<Baz> sharedBaz = barsBaz.lock();

    if(sharedBaz)
    {
        return sharedBaz->method("called from class Bar");
    }

    return "barsBaz had already been released";
}

Bar::Bar(boost::shared_ptr<Baz> sharedBaz)
{
    barsBaz = sharedBaz;
}

