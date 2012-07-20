//File: SharedPtrFactoryStoreAsBase.cpp
//Author:   John Miner
//Created:  03/21/12
//Modified: 03/21/12
//Purpose:  Determine how to return a shared_ptr to a Base class using Abstract
//          Factory and how to store the ptrs.

#include "../Header/Container.hpp"
#include "../Header/Base.hpp"
#include "../Header/DerivedFoo.hpp"
#include "../Header/DerivedBar.hpp"

int main(int argc, char **argv)
{
    Container c;
    DerivedFoo df;
    DerivedBar db;

    c.store(df);
    c.store(db);
    c.printAll();

    return EXIT_SUCCESS;
}

