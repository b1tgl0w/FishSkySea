//File: OverloadBitOrFoo.h
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Have a constraint class that can bitwise | values together.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef OVERLOAD_BIT_OR_FOO_HPP_
#define OVERLOAD_BIT_OR_FOO_HPP_

class Foo
{
public:
    static Foo BarValue();
    static Foo BazValue();
    static Foo QuxValue();
    Foo operator|(const Foo &rhs) const;
    bool has(const Foo &rhs) const;
private:
    Foo();
    Foo(const Foo &rhs);
    Foo operator=(const Foo &rhs);
    explicit Foo(int initialValue);
    bool operator==(const Foo &rhs) const;
    Foo operator&(const Foo &rhs) const;
    int value;
};

#endif

