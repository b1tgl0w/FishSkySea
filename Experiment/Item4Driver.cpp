//File: Item4Driver.cpp
//Author:   John Miner
//Created:  09/25/11
//Modified: 09/25/11
//Purpose:  Test out Scott Meyers' advice in Effective C++ for non-local
//static objects of different translation units, specifically for class-wide
//static constants
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include <cstdlib>
#include "Item4Bar.hpp"
#include "Item4Foo.hpp"

int main(int argc, char **argv)
{
    Foo foo;
    Bar bar;
    std::cout << foo.MY_VAR() << std::endl;
    std::cout << bar.MY_VAR() << std::endl;

    return EXIT_SUCCESS;
}

