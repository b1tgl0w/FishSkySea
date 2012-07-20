//File: Sandbox/BoostWeakPointersBaz.h
//Author:   John Miner
//Created:  09/21/11
//Modified: 09/21/11
//Purpose:  Experiment with boost weak pointers.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef BOOST_WEAK_POINTERS_BAZ_HPP_
#define BOOST_WEAK_POINTERS_BAZ_HPP_

#include <string>

class Baz
{
public:
    std::string method(std::string output);
private:
    static const std::string BAZ_OUTPUT;
};

#endif

