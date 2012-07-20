//File: SlicingQux.cpp
//Author:   John Miner
//Created:  03/07/12
//Modified: 03/07/12
//Purpose:  Determine a way to overcome slicing
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "SlicingQux.hpp"
#include "SlicingFoo.hpp"

Qux::Qux(boost::shared_ptr<Foo> foo) : foo(foo)
{
}

Qux::Qux(const Qux &rhs) : foo(rhs.foo)
{
}

Qux &Qux::operator=(const Qux &rhs)
{
    if( &rhs == this )
        return *this;

    this->foo = rhs.foo;
    
    return *this;
}

void Qux::useFoo()
{
    foo->saySomething();
}

