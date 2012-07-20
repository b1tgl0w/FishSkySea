//File: OverloadBitOrDriver.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Have a constraint class that can bitwise | values together.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include "OverloadBitOrFoo.hpp"

void printFoos(const Foo &foos);
int main(int argc, char **argv)
{
    std::cout << "printFoos(Foo::BarValue())" << std::endl;
    printFoos(Foo::BarValue());
    //std::cout << "printFoos(Foo::BarValue() | Foo::BazValue() | Foo::QuxValue())" <<
    //    std::endl;
    //printFoos(Foo::BarValue() | Foo::BazValue() | Foo::QuxValue());
}

void printFoos(const Foo &foos)
{
    if(foos.has(Foo::BarValue()))
        std::cout << "BarValue" << std::endl;
    if(foos.has(Foo::BazValue()))
        std::cout << "BazValue" << std::endl;
    if(foos.has(Foo::QuxValue()))
        std::cout << "QuxValue" << std::endl;
}

