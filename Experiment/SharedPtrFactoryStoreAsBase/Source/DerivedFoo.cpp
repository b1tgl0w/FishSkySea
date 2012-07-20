//File: DerivedFoo.cpp
//Author:   John Miner
//Created:  03/21/12
//Modified: 03/21/12
//Purpose:  Determine how to return a shared_ptr to a Base class using Abstract
//          Factory and how to store the ptrs.

#include <iostream>
#include "../Header/DerivedFoo.hpp"

void DerivedFoo::print()
{
    std::cout << "I'm foo" << std::endl;
}

boost::shared_ptr<Base> DerivedFoo::manufacture()
{
    if( !sharedDerivedFoo )
    {
        boost::shared_ptr<DerivedFoo> sharedTmp(new DerivedFoo);
        sharedDerivedFoo = sharedTmp;
    }

    return sharedDerivedFoo;
}

