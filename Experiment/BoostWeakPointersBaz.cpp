//File: Sandbox/BoostWeakPointersBaz.cpp
//Author:   John Miner
//Created:  09/21/11
//Modified: 09/22/11
//Purpose:  Experiment with boost weak pointers.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "BoostWeakPointersBaz.hpp"

const std::string Baz::BAZ_OUTPUT = "Baz.method(...): ";

std::string Baz::method(std::string output)
{
    return BAZ_OUTPUT + output;
}

