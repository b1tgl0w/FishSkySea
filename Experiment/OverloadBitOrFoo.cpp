//File: OverloadBitOrFoo.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Have a constraint class that can bitwise | values together.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "OverloadBitOrFoo.hpp"

Foo Foo::BarValue()
{
    return Foo(1 << 0);
}

Foo Foo::BazValue()
{
    return Foo(1 << 1);
}

Foo Foo::QuxValue()
{
    return Foo(1 << 2);
}

Foo::Foo(int initialValue)
{
    value = initialValue;
}

Foo Foo::operator|(const Foo &rhs) const
{
    return Foo(value | rhs.value);
}

Foo Foo::operator&(const Foo &rhs) const
{
    return Foo(value & rhs.value);
}

bool Foo::has(const Foo &rhs) const 
{
    return ((*this) & rhs) == rhs;
}

bool Foo::operator==(const Foo &rhs) const
{
    if( value == rhs.value )
        return true;

    return false;
}

