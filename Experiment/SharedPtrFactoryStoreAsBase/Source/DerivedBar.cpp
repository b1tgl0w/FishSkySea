//File: DerivedBar.cpp
//Author:   John Miner
//Created:  03/21/12
//Modified: 03/21/12
//Purpose:  Determine how to return a shared_ptr to a Base class using Abstract
//          Factory and how to store the ptrs.

#include <iostream>
#include "../Header/DerivedBar.hpp"

void DerivedBar::print()
{
    std::cout << "I'm bar" << std::endl;
}

boost::shared_ptr<Base> DerivedBar::manufacture()
{
    if( !sharedDerivedBar )
    {
        boost::shared_ptr<DerivedBar> sharedTmp(new DerivedBar);
        sharedDerivedBar = sharedTmp;
    }

    return sharedDerivedBar;
}

