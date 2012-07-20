//File: Container.cpp
//Author:   John Miner
//Created:  03/21/12
//Modified: 03/21/12
//Purpose:  Determine how to return a shared_ptr to a Base class using Abstract
//          Factory and how to store the ptrs.

#include "../Header/Container.hpp"
#include "../Header/Base.hpp"

void Container::store(Base &base)
{
    boost::shared_ptr<Base> sharedBase(base.manufacture());
    l.push_back(sharedBase);
}

void Container::printAll()
{
    for(std::list<boost::shared_ptr<Base> >::iterator it = 
        l.begin(); it != l.end(); ++it)
        (*it)->print();
}

