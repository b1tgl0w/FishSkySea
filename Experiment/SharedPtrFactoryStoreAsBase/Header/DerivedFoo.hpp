//File: DerivedFoo.hpp
//Author:   John Miner
//Created:  03/21/12
//Modified: 03/21/12
//Purpose:  Determine how to return shared ptrs from an Abstract Factory and
//          store those ptrs as base class ptrs
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef DERIVED_FOO_H_
#define DERIVED_FOO_H_

#include "boost/shared_ptr.hpp"
#include "Base.hpp"

class DerivedFoo : public Base
{
public:
    void print();
    boost::shared_ptr<Base> manufacture();
private:
    boost::shared_ptr<DerivedFoo> sharedDerivedFoo;
};

#endif

